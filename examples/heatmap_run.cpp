#include <QApplication>
#include <QDir>
#include <QImage>
#include <QPainter>

#include "heatmap_plot_widget.hpp"

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

    const cpp_group_6::NumericalDataset data{
    {"Bill", "Tip", "Salary", "Children"},
    {
        {45.0,  6.0,  2.0, 0.0},
        {80.0, 12.0,  5.0, 2.0},
        {35.0,  5.0,  3.0, 1.0},
        {120.0, 18.0, 8.0, 3.0},
        {65.0,  8.0,  4.0, 2.0},
        {150.0, 16.0,  7.0, 1.0},
        {95.0, 15.0,  6.0, 0.0},
        {55.0,  9.0,  3.0, 4.0},
        {200.0, 30.0, 10.0, 2.0},
        {75.0,  7.0,  5.0, 3.0},
        {110.0, 20.0,  4.0, 1.0},
        {40.0,  4.0,  2.0, 2.0},
        {180.0, 25.0,  9.0, 0.0},
        {90.0,  11.0,  7.0, 4.0},
        {130.0, 22.0,  6.0, 2.0},
        {60.0,  5.0,  3.0, 1.0},
        {220.0, 28.0, 11.0, 3.0},
        {85.0,  14.0,  4.0, 0.0},
        {160.0, 12.0,  8.0, 4.0},
        {50.0,  8.0,  5.0, 2.0},
        {140.0, 24.0,  7.0, 1.0},
        {100.0, 10.0,  3.0, 3.0},
        {190.0, 27.0,  9.0, 2.0},
        {70.0,  13.0,  6.0, 0.0}
    }
};



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
