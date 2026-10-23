#include <QApplication>

#include "point_plot_widget.hpp"

int main(int argc, char* argv[]) {
    QApplication application(argc, argv);

    const cpp_group_6::Dataset data = {
        {"A", 2.0},
        {"A", -2.0},
        {"B", 4.0},
        {"A", 0.0},
        {"C", 5.0},
        {"C", 7.0},
        {"A", 3.0},
        {"D", 3.0},
        {"D", 1.0},
        {"B", 3.0},
        {"C", 2.0},
        {"A", 1.0},
        {"B", 5.0},
        {"C", 4.0},
        {"D", 2.0}
    };

    PointPlotWidget window;
    window.setWindowTitle("CPP Group 6 - Qt Point Plot");
    window.setTitle("Point Plot");
    window.resize(760, 520);

    const auto plotData = cpp_group_6::transformPointPlot(data);
    if (plotData.has_value()) {
        window.setPlotData(*plotData);
    } else {
        window.setErrorMessage(
            "Unable to prepare point-plot data."
        );
    }

    window.show();

    return application.exec();
}
