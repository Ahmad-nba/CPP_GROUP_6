#include "heatmap_plot_widget.hpp"

#include <QColor>
#include <QFont>
#include <QPainter>
#include <QPaintEvent>

#include <algorithm>
#include <cmath>

namespace {

// Linear interpolation between two channel values.
inline int lerpChannel(int from, int to, double t) {
    return static_cast<int>(std::lround(from + (to - from) * t));
}

inline QColor lerpColor(const QColor& a, const QColor& b, double t) {
    t = std::clamp(t, 0.0, 1.0);
    return QColor(
        lerpChannel(a.red(),   b.red(),   t),
        lerpChannel(a.green(), b.green(), t),
        lerpChannel(a.blue(),  b.blue(),  t)
    );
}

// Perceived luminance (Rec. 601) -> readable label color for a given fill.
inline QColor labelColorFor(const QColor& background) {
    const double luminance =
        0.299 * background.red() +
        0.587 * background.green() +
        0.114 * background.blue();
    return luminance < 140.0 ? QColor(Qt::white) : QColor("#303030");
}

// Maps a correlation to a diverging blue-white-red color.
//
// isSelf == true (diagonal) is the ONLY case that returns full-saturation
// red. Every other cell, even a perfect 1.0 between two different features,
// ends at a deeper brick red so the diagonal always stands out.
QColor correlationColor(double value, bool isSelf = false) {
    if (isSelf) {
        return QColor(255, 0, 0);
    }

    const double clamped = std::clamp(value, -1.0, 1.0);

    // Neutral midpoint.
    static const QColor kWhite(255, 255, 255);

    // Off-diagonal endpoints, intentionally not pure red/blue.
    static const QColor kStrongPos(200, 30, 30);
    static const QColor kStrongNeg(30, 60, 200);

    // Cap magnitude so 0.99 still reads as "strong" and not as "self".
    constexpr double kMaxMagnitude = 0.98;

    // gamma > 1 spreads the strong range (0.7 - 1.0) instead of crushing it.
    // 1.0 = linear, ~1.4 = good separation, 1.6-2.0 = more contrast at top.
    constexpr double kGamma = 1.4;

    const double magnitude = std::min(std::abs(clamped), kMaxMagnitude);
    const double t = std::pow(magnitude / kMaxMagnitude, kGamma);

    return lerpColor(kWhite, clamped >= 0.0 ? kStrongPos : kStrongNeg, t);
}

} // namespace

HeatmapPlotWidget::HeatmapPlotWidget(QWidget* parent)
    : QWidget(parent) {
    setMinimumSize(720, 560);
}

void HeatmapPlotWidget::setPlotData(
    const cpp_group_6::HeatmapPlotData& data
) {
    plotData_ = data;
    errorMessage_.clear();
    update();
}

void HeatmapPlotWidget::setErrorMessage(const QString& message) {
    errorMessage_ = message;
    update();
}

void HeatmapPlotWidget::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(rect(), Qt::white);

    if (!errorMessage_.isEmpty()) {
        painter.setPen(QColor("#a00000"));
        painter.drawText(
            rect(),
            Qt::AlignCenter | Qt::TextWordWrap,
            errorMessage_
        );
        return;
    }

    const auto& labels = plotData_.feature_names;
    const auto& correlations = plotData_.correlation_matrix;
    const int featureCount = static_cast<int>(labels.size());
    if (featureCount == 0 ||
        static_cast<int>(correlations.size()) != featureCount) {
        painter.setPen(QColor("#555555"));
        painter.drawText(rect(), Qt::AlignCenter, "No heatmap data available.");
        return;
    }

    constexpr int leftMargin = 120;
    constexpr int topMargin = 110;
    constexpr int rightMargin = 120;
    constexpr int bottomMargin = 120;
    const int cellSize = std::max(
        1,
        std::min(
            (width() - leftMargin - rightMargin) / featureCount,
            (height() - topMargin - bottomMargin) / featureCount
        )
    );
    const QRectF grid(
        leftMargin,
        topMargin,
        cellSize * featureCount,
        cellSize * featureCount
    );

    painter.setPen(QColor("#202020"));
    painter.setFont(QFont("Segoe UI", 15, QFont::DemiBold));
    painter.drawText(
        QRectF(0, 20, width(), 32),
        Qt::AlignCenter,
        "Feature Correlation Heatmap"
    );

    painter.setFont(QFont("Segoe UI", 9));
    for (int row = 0; row < featureCount; ++row) {
        for (int column = 0; column < featureCount; ++column) {
            const QRectF cell(
                grid.left() + column * cellSize,
                grid.top() + row * cellSize,
                cellSize,
                cellSize
            );
            const auto& value = correlations[row][column];
            const bool isSelf = (row == column);

            const QColor fill = value.has_value()
                ? correlationColor(*value, isSelf)
                : QColor("#dddddd");

            painter.fillRect(cell, fill);
            painter.setPen(QColor("#ffffff"));
            painter.drawRect(cell);

            if (cellSize >= 36) {
                // Label color is derived from the actual fill, so text stays
                // readable regardless of how the color scale is tuned.
                painter.setPen(labelColorFor(fill));
                painter.drawText(
                    cell,
                    Qt::AlignCenter,
                    value.has_value()
                        ? QString::number(*value, 'f', 2)
                        : QString("N/A")
                );
            }
        }
    }

    painter.setPen(QColor("#303030"));
    for (int index = 0; index < featureCount; ++index) {
        const QRectF columnLabel(
            grid.left() + index * cellSize,
            grid.top() - 52,
            cellSize,
            48
        );
        painter.drawText(
            columnLabel,
            Qt::AlignCenter | Qt::TextWordWrap,
            QString::fromStdString(labels[index])
        );

        const QRectF rowLabel(
            8,
            grid.top() + index * cellSize,
            leftMargin - 16,
            cellSize
        );
        painter.drawText(
            rowLabel,
            Qt::AlignRight | Qt::AlignVCenter | Qt::TextWordWrap,
            QString::fromStdString(labels[index])
        );
    }

    // Legend shows the off-diagonal scale (the diagonal's pure red is
    // reserved for self-correlation and is intentionally not on the scale).
    const QRectF legend(
        grid.right() + 28,
        grid.top(),
        22,
        grid.height()
    );
    for (int step = 0; step < static_cast<int>(legend.height()); ++step) {
        const double value =
            1.0 - static_cast<double>(step) / legend.height() * 2.0;
        painter.fillRect(
            QRectF(legend.left(), legend.top() + step, legend.width(), 1),
            correlationColor(value)
        );
    }

    painter.setPen(QColor("#303030"));
    painter.drawText(
        QRectF(legend.right() + 8, legend.top() - 8, 48, 20),
        Qt::AlignLeft | Qt::AlignVCenter,
        "+1"
    );
    painter.drawText(
        QRectF(legend.right() + 8, legend.center().y() - 10, 48, 20),
        Qt::AlignLeft | Qt::AlignVCenter,
        "0"
    );
    painter.drawText(
        QRectF(legend.right() + 8, legend.bottom() - 12, 48, 20),
        Qt::AlignLeft | Qt::AlignVCenter,
        "-1"
    );
}
