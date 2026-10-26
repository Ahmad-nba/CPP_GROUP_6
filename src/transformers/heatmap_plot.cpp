#include "heatmap_plot.hpp"

#include "dataset_view.hpp"
#include "value_analysis.hpp"

#include <cmath>
#include <optional>
#include <utility>

namespace cpp_group_6 {

std::optional<HeatmapPlotData> transformHeatmap(const HeatmapData& data) {
    HeatmapValidator validator(data);
    if (!validator.validate().valid) {
        return std::nullopt;
    }

    DatasetView values;
    for (const auto& row : data.values) {
        values.values.insert(values.values.end(), row.begin(), row.end());
    }

    const auto range = analyzeValues(values);
    if (!range.has_value()) {
        return std::nullopt;
    }

    return HeatmapPlotData{data, *range};
}

std::optional<HeatmapPlotData> transformHeatmap(
    const NumericalDataset& data
) {
    HeatmapValidator validator(data);
    if (!validator.validate().valid) {
        return std::nullopt;
    }

    const std::size_t featureCount = data.feature_names.size();
    std::vector<std::vector<std::optional<double>>> correlations(
        featureCount,
        std::vector<std::optional<double>>(featureCount)
    );
    std::vector<std::vector<double>> matrix(
        featureCount,
        std::vector<double>(featureCount)
    );

    for (std::size_t first = 0; first < featureCount; ++first) {
        for (std::size_t second = 0; second < featureCount; ++second) {
            double firstMean = 0.0;
            double secondMean = 0.0;
            for (const auto& row : data.values) {
                firstMean += row[first];
                secondMean += row[second];
            }
            firstMean /= static_cast<double>(data.values.size());
            secondMean /= static_cast<double>(data.values.size());

            double numerator = 0.0;
            double firstVariance = 0.0;
            double secondVariance = 0.0;
            for (const auto& row : data.values) {
                const double firstDelta = row[first] - firstMean;
                const double secondDelta = row[second] - secondMean;
                numerator += firstDelta * secondDelta;
                firstVariance += firstDelta * firstDelta;
                secondVariance += secondDelta * secondDelta;
            }

            const double denominator = std::sqrt(
                firstVariance * secondVariance
            );
            if (denominator == 0.0 ||
                !std::isfinite(denominator)) {
                return std::nullopt;
            }

            const double correlation = numerator / denominator;
            if (!std::isfinite(correlation)) {
                return std::nullopt;
            }

            correlations[first][second] = correlation;
            matrix[first][second] = correlation;
        }
    }

    DatasetView values;
    for (const auto& row : matrix) {
        values.values.insert(values.values.end(), row.begin(), row.end());
    }
    const auto range = analyzeValues(values);
    if (!range.has_value()) {
        return std::nullopt;
    }

    return HeatmapPlotData{
        HeatmapData{data.feature_names, data.feature_names, matrix},
        *range,
        data.feature_names,
        std::move(correlations)
    };
}

} // namespace cpp_group_6
