#include "point_plot_widget.hpp"

#include <QFontMetrics>
#include <QPainter>
#include <QPaintEvent>

#include <algorithm>
#include <cmath>
#include <vector>

PointPlotWidget::PointPlotWidget(QWidget* parent)
    : QWidget(parent),
      title_("Point Plot") {
    setMinimumSize(640, 420);
}

void PointPlotWidget::setPlotData(
    const cpp_group_6::PointPlotData& data
) {
    plotData_ = data;
    errorMessage_.clear();

    for (const auto& point : plotData_.points) {
        if (point.category.empty() || !std::isfinite(point.value)) {
            errorMessage_ = "The plot data contains an invalid point.";
            break;
        }
    }

    update();
}

void PointPlotWidget::setTitle(const QString& title) {
    title_ = title;
    update();
}

void PointPlotWidget::setErrorMessage(const QString& message) {
    errorMessage_ = message;
    update();
}

PointPlotWidget::AxisRange PointPlotWidget::calculateAxisRange(
    const cpp_group_6::PointPlotData& data
) {
    double minimum = 0.0;
    double maximum = 0.0;

    // here we do the scaling of canvas of widget wrt data we have
    for (const auto& point : data.points) {
        minimum = std::min(minimum, point.value);
        maximum = std::max(maximum, point.value);
    }

    const double span = maximum - minimum;
    if (!std::isfinite(span) || span <= 0.0) {
        return {-1.0, 1.0};
    }

    const double padding = span * 0.1;
    return {minimum - padding, maximum + padding};
}

// this is now qt specific of drawing the canvas and putting points in there.
double PointPlotWidget::mapValueToY(
    double value,
    const AxisRange& range,
    const QRectF& plotRect
) {
    const double normalized =
        (value - range.minimum) / (range.maximum - range.minimum);
    return plotRect.bottom() - normalized * plotRect.height();
}

void PointPlotWidget::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(rect(), QColor("#ffffff"));

    if (!errorMessage_.isEmpty()) {
        painter.setPen(QColor("#a00000"));
        painter.drawText(
            rect(),
            Qt::AlignCenter | Qt::TextWordWrap,
            errorMessage_
        );
        return;
    }

    if (plotData_.points.empty()) {
        painter.setPen(QColor("#555555"));
        painter.drawText(
            rect(),
            Qt::AlignCenter,
            "No point-plot data available."
        );
        return;
    }

    constexpr int leftMargin = 76;
    constexpr int rightMargin = 24;
    constexpr int topMargin = 56;
    constexpr int bottomMargin = 72;
    const QRectF plotRect(
        leftMargin,
        topMargin,
        std::max(1, width() - leftMargin - rightMargin),
        std::max(1, height() - topMargin - bottomMargin)
    );

    painter.setPen(QColor("#202020"));
    painter.setFont(QFont("Segoe UI", 14, QFont::DemiBold));
    painter.drawText(
        QRectF(0, 12, width(), 28),
        Qt::AlignCenter,
        title_
    );

    const AxisRange range = calculateAxisRange(plotData_);
    constexpr int tickCount = 5;

    painter.fillRect(plotRect, QColor("#fbfbfb"));
    painter.setFont(QFont("Segoe UI", 9));

    for (int tick = 0; tick <= tickCount; ++tick) {
        const double fraction =
            static_cast<double>(tick) / tickCount;
        const double value =
            range.minimum + fraction * (range.maximum - range.minimum);
        const double y = plotRect.bottom() - fraction * plotRect.height();

        painter.setPen(QColor("#dddddd"));
        painter.drawLine(
            QPointF(plotRect.left(), y),
            QPointF(plotRect.right(), y)
        );

        painter.setPen(QColor("#444444"));
        painter.drawText(
            QRectF(4, y - 10, leftMargin - 12, 20),
            Qt::AlignRight | Qt::AlignVCenter,
            QString::number(value, 'g', 4)
        );
    }

    painter.setPen(QPen(QColor("#333333"), 1.5));
    painter.drawLine(plotRect.bottomLeft(), plotRect.topLeft());
    painter.drawLine(plotRect.bottomLeft(), plotRect.bottomRight());

    const int pointCount =
        static_cast<int>(plotData_.points.size());
    const double slotWidth = plotRect.width() / pointCount;
    const QFontMetrics metrics(painter.font());
    std::vector<QPointF> pointCenters;
    pointCenters.reserve(plotData_.points.size());

    for (int index = 0; index < pointCount; ++index) {
        const auto& point = plotData_.points[static_cast<std::size_t>(index)];
        const double x =
            plotRect.left() + (index + 0.5) * slotWidth;
        const double y = mapValueToY(point.value, range, plotRect);
        pointCenters.emplace_back(x, y);

        painter.setPen(QColor("#444444"));
        painter.drawText(
            QRectF(
                x - slotWidth / 2.0,
                plotRect.bottom() + 12,
                slotWidth,
                bottomMargin - 16
            ),
            Qt::AlignHCenter | Qt::AlignTop | Qt::TextWordWrap,
            metrics.elidedText(
                QString::fromStdString(point.category),
                Qt::ElideRight,
                static_cast<int>(slotWidth) - 4
            )
        );
    }

    constexpr double verticalGuideHalfLength = 28.0;
    painter.setPen(QPen(QColor("#e8a53a"), 2.0));
    for (const auto& center : pointCenters) {
        painter.drawLine(
            QPointF(center.x(), center.y() - verticalGuideHalfLength),
            QPointF(center.x(), center.y() + verticalGuideHalfLength)
        );
    }

    painter.setBrush(Qt::NoBrush);
    for (std::size_t index = 1; index < pointCenters.size(); ++index) {
        painter.drawLine(pointCenters[index - 1], pointCenters[index]);
    }

    for (const auto& center : pointCenters) {
        painter.setPen(QPen(QColor("#1769aa"), 1));
        painter.setBrush(QColor("#42a5f5"));
        painter.drawEllipse(center, 6.0, 6.0);
    }
}
