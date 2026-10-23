#ifndef CPP_GROUP_6_POINT_PLOT_WIDGET_HPP
#define CPP_GROUP_6_POINT_PLOT_WIDGET_HPP

#include "point_plot.hpp"

#include <QWidget>

class PointPlotWidget final : public QWidget {
public:
    explicit PointPlotWidget(QWidget* parent = nullptr);

    void setPlotData(const cpp_group_6::PointPlotData& data);
    void setTitle(const QString& title);
    void setErrorMessage(const QString& message);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    struct AxisRange {
        double minimum;
        double maximum;
    };

    static AxisRange calculateAxisRange(
        const cpp_group_6::PointPlotData& data
    );
    static double mapValueToY(
        double value,
        const AxisRange& range,
        const QRectF& plotRect
    );

    cpp_group_6::PointPlotData plotData_;
    QString title_;
    QString errorMessage_;
};

#endif
