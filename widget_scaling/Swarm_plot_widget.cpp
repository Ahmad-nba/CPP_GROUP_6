#include "swarm_plot-widget.hpp"

#include <QFontMetrics>
#include <QPainter>
#include <QPaintEvent>

#include <algorithm>
#include <cmath>
#include <map>

SwarmPlotWidget::SwarmPlotWidget(QWidget* parent)
    : QWidget(parent),
      title_("Swarm Plot") {
    setMinimumSize(640, 420);
}

void SwarmPlotWidget::setPlotData(
    const cpp_group_6::SwarmPlotData& data
) {
    plotData_ = data;
    errorMessage_.clear();

    for (const auto& point : plotData_.points) {
        if (point.category.empty() ||
            !std::isfinite(point.value) ||
            !std::isfinite(point.category_position) ||
            !std::isfinite(point.offset)) {
            errorMessage_ = "The plot data contains an invalid point.";
            break;
        }
    }

    update();
}

void SwarmPlotWidget::setTitle(const QString& title) {
    title_ = title;
    update();
}

void SwarmPlotWidget::setErrorMessage(const QString& message) {
    errorMessage_ = message;
    update();
}

SwarmPlotWidget::AxisRange SwarmPlotWidget::calculateAxisRange(
    const cpp_group_6::SwarmPlotData& data
) {
    double minimum = data.points.front().value;
    double maximum = minimum;
    for (const auto& point : data.points) {
        minimum = std::min(minimum, point.value);
        maximum = std::max(maximum, point.value);
    }

    const double span = maximum - minimum;
    if (!std::isfinite(span) || span <= 0.0) {
        return {minimum - 1.0, maximum + 1.0};
    }

    const double padding = span * 0.1;
    return {minimum - padding, maximum + padding};
}

double SwarmPlotWidget::mapValueToY(
    double value,
    const AxisRange& range,
    const QRectF& plotRect
) {
    const double normalized =
        (value - range.minimum) / (range.maximum - range.minimum);
    return plotRect.bottom() - normalized * plotRect.height();
}

void SwarmPlotWidget::paintEvent(QPaintEvent* event) {
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

    if (plotData_.points.empty()) {
        painter.setPen(QColor("#555555"));
        painter.drawText(rect(), Qt::AlignCenter, "No swarm-plot data available.");
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

    double categoryCount = 0.0;
    for (const auto& point : plotData_.points) {
        categoryCount = std::max(categoryCount, point.category_position + 1.0);
    }
    const double slotWidth = plotRect.width() / categoryCount;
    const QFontMetrics metrics(painter.font());
    std::map<double, std::string> categoryLabels;

    for (const auto& point : plotData_.points) {
        categoryLabels.emplace(point.category_position, point.category);
        const double categoryCenter =
            plotRect.left() + (point.category_position + 0.5) * slotWidth;
        const double x = categoryCenter + point.offset * slotWidth;
        const double y = mapValueToY(point.value, range, plotRect);

        painter.setPen(QPen(QColor("#1769aa"), 1));
        painter.setBrush(QColor("#42a5f5"));
        painter.drawEllipse(QPointF(x, y), 6.0, 6.0);
    }

    painter.setPen(QColor("#444444"));
    for (const auto& [position, category] : categoryLabels) {
        const double x =
            plotRect.left() + (position + 0.5) * slotWidth;
        painter.drawText(
            QRectF(
                x - slotWidth / 2.0,
                plotRect.bottom() + 12,
                slotWidth,
                bottomMargin - 16
            ),
            Qt::AlignHCenter | Qt::AlignTop | Qt::TextWordWrap,
            metrics.elidedText(
                QString::fromStdString(category),
                Qt::ElideRight,
                static_cast<int>(slotWidth) - 4
            )
        );
    }
}
