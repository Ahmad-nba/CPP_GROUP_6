#ifndef CPP_GROUP_6_HEATMAP_PLOT_WIDGET_HPP
#define CPP_GROUP_6_HEATMAP_PLOT_WIDGET_HPP

#include "heatmap_plot.hpp"

#include <QWidget>

class HeatmapPlotWidget final : public QWidget {
public:
    explicit HeatmapPlotWidget(QWidget* parent = nullptr);

    void setPlotData(const cpp_group_6::HeatmapPlotData& data);
    void setErrorMessage(const QString& message);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    cpp_group_6::HeatmapPlotData plotData_;
    QString errorMessage_;
};

#endif
