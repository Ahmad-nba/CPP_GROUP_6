#include <QApplication>
#include <QDir>
#include <QImage>
#include <QPainter>

#include "point_plot_widget.hpp"
#include "input_data.hpp"

#include <filesystem>
#include <iostream>
#include <system_error>

namespace {

bool savePlotImage(QWidget& widget) {
    if (widget.width() <= 0 || widget.height() <= 0) {
        std::cerr << "Unable to save point plot: widget has invalid dimensions.\n";
        return false;
    }

    const std::filesystem::path outputDirectory(
        POINT_PLOT_OUTPUT_DIRECTORY
    );
    std::error_code error;
    std::filesystem::create_directories(outputDirectory, error);
    if (error) {
        std::cerr
            << "Unable to create point-plot output directory: "
            << error.message() << '\n';
        return false;
    }

    const std::filesystem::path outputFile =
        outputDirectory / "point_plot.png";
    QImage image(widget.size(), QImage::Format_ARGB32);
    if (image.isNull()) {
        std::cerr << "Unable to save point plot: image allocation failed.\n";
        return false;
    }

    image.fill(Qt::white);
    QPainter painter(&image);
    widget.render(&painter);
    painter.end();

    const QString outputPath = QDir::toNativeSeparators(
        QString::fromStdWString(outputFile.wstring())
    );
    if (!image.save(outputPath, "PNG")) {
        std::cerr
            << "Unable to save point plot image to "
            << outputFile.string() << '\n';
        return false;
    }

    std::cout << "Saved point plot image to "
              << outputFile.string() << '\n';
    return true;
}

} // namespace

int main(int argc, char* argv[]) {
    QApplication application(argc, argv);

    const auto& data = cpp_group_6::input::pointPlotData();

    PointPlotWidget window;
    window.setWindowTitle("CPP Group 6 - Qt Point Plot");
    window.setTitle("Point Plot");
    window.resize(760, 520);

    const auto plotData = cpp_group_6::transformPointPlot(data);
    const bool plotReady = plotData.has_value();
    if (plotData.has_value()) {
        window.setPlotData(*plotData);
    } else {
        window.setErrorMessage(
            "Unable to prepare point-plot data."
        );
    }

    window.show();
    application.processEvents();

    if (plotReady) {
        savePlotImage(window);
    }

    return application.exec();
}
