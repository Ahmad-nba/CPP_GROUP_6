#include <QApplication>
#include <QDir>
#include <QImage>
#include <QPainter>

#include "heatmap_plot_widget.hpp"
#include "input_data.hpp"

#include <filesystem>
#include <iostream>
#include <system_error>

namespace {

bool saveHeatmapImage(QWidget& widget) {
    if (widget.width() <= 0 || widget.height() <= 0) {
        std::cerr << "Unable to save heatmap: widget has invalid dimensions.\n";
        return false;
    }

    const std::filesystem::path outputDirectory(
        HEATMAP_OUTPUT_DIRECTORY
    );
    std::error_code error;
    std::filesystem::create_directories(outputDirectory, error);
    if (error) {
        std::cerr
            << "Unable to create heatmap output directory: "
            << error.message() << '\n';
        return false;
    }

    const std::filesystem::path outputFile =
        outputDirectory / "heatmap.png";
    QImage image(widget.size(), QImage::Format_ARGB32);
    if (image.isNull()) {
        std::cerr << "Unable to save heatmap: image allocation failed.\n";
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
            << "Unable to save heatmap image to "
            << outputFile.string() << '\n';
        return false;
    }

    std::cout << "Saved heatmap image to "
              << outputFile.string() << '\n';
    return true;
}

} // namespace

int main(int argc, char* argv[]) {
    QApplication application(argc, argv);

    const auto& data = cpp_group_6::input::heatmapData();

    HeatmapPlotWidget window;
    window.setWindowTitle("CPP Group 6 - Correlation Heatmap");
    window.resize(900, 700);

    const auto heatmap = cpp_group_6::transformHeatmap(data);
    if (heatmap.has_value()) {
        window.setPlotData(*heatmap);
    } else {
        window.setErrorMessage(
            "Unable to prepare correlation heatmap data."
        );
    }

    window.show();
    application.processEvents();

    if (heatmap.has_value()) {
        saveHeatmapImage(window);
    }

    return application.exec();
}
