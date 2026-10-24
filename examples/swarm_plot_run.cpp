#include <QApplication>
#include <QDir>
#include <QImage>
#include <QPainter>

#include "swarm_plot_widget.hpp"

#include <filesystem>
#include <iostream>
#include <system_error>

namespace {

bool saveSwarmPlotImage(QWidget& widget) {
    if (widget.width() <= 0 || widget.height() <= 0) {
        std::cerr << "Unable to save swarm plot: widget has invalid dimensions.\n";
        return false;
    }

    const std::filesystem::path outputDirectory(
        SWARM_PLOT_OUTPUT_DIRECTORY
    );
    std::error_code error;
    std::filesystem::create_directories(outputDirectory, error);
    if (error) {
        std::cerr
            << "Unable to create swarm-plot output directory: "
            << error.message() << '\n';
        return false;
    }

    const std::filesystem::path outputFile =
        outputDirectory / "swarm_plot.png";
    QImage image(widget.size(), QImage::Format_ARGB32);
    if (image.isNull()) {
        std::cerr << "Unable to save swarm plot: image allocation failed.\n";
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
            << "Unable to save swarm plot image to "
            << outputFile.string() << '\n';
        return false;
    }

    std::cout << "Saved swarm plot image to "
              << outputFile.string() << '\n';
    return true;
}

} // namespace

int main(int argc, char* argv[]) {
    QApplication application(argc, argv);

    const cpp_group_6::Dataset data = {
        {"A", 12.0}, {"A", 15.0}, {"A", 15.0}, {"A", 15.0}, {"A", 15.0}, {"A", 18.0}, {"A", 21.0},
        {"B", 10.0}, {"B", 14.0}, {"B", 17.0}, {"B", 17.0}, {"B", 17.0}, {"B", 17.0},{"B", 17.0}, {"B", 17.0}, {"B", 22.0},
        {"C", 13.0}, {"C", 16.0}, {"C", 19.0},{"C", 13.0}, {"C", 19.0},{"C", 13.0}, {"C", 16.0}, {"C", 19.0}, {"C", 20.0}, {"C", 24.0}
    };

    SwarmPlotWidget window;
    window.setWindowTitle("CPP Group 6 - Qt Swarm Plot");
    window.setTitle("Swarm Plot");
    window.resize(760, 520);

    const auto plotData = cpp_group_6::transformSwarmPlot(data);
    if (plotData.has_value()) {
        window.setPlotData(*plotData);
    } else {
        window.setErrorMessage("Unable to prepare swarm-plot data.");
    }

    window.show();
    application.processEvents();

    if (plotData.has_value()) {
        saveSwarmPlotImage(window);
    }

    return application.exec();
}
