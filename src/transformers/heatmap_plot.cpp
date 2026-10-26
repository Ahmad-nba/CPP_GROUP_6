#include "heatmap_plot.hpp"

#include "dataset_view.hpp"
#include "value_analysis.hpp"

#include <cmath>
#include <optional>

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

    return HeatmapPlotData{data, *range, {}, {}};
}

std::optional<HeatmapPlotData> transformHeatmap(
    const NumericalDataset& data
) {
    HeatmapValidator validator(data);
    if (!validator.validate().valid) {
        return std::nullopt;
    }

    const std::size_t feature_count = data.feature_names.size();
    std::vector<double> means(feature_count, 0.0);
    for (const auto& row : data.values) {
        for (std::size_t feature = 0; feature < feature_count; ++feature) {
            means[feature] += row[feature];
        }
    }

    for (double& mean : means) {
        mean /= static_cast<double>(data.values.size());
    }

    std::vector<std::vector<std::optional<double>>> correlations(
        feature_count,
        std::vector<std::optional<double>>(feature_count)
    );
    std::vector<std::vector<double>> matrix(
        feature_count,
        std::vector<double>(feature_count, 0.0)
    );

    for (std::size_t row = 0; row < feature_count; ++row) {
        for (std::size_t column = row; column < feature_count; ++column) {
            double numerator = 0.0;
            double row_sum = 0.0;
            double column_sum = 0.0;

            for (const auto& observation : data.values) {
                const double row_delta = observation[row] - means[row];
                const double column_delta =
                    observation[column] - means[column];
                numerator += row_delta * column_delta;
                row_sum += row_delta * row_delta;
                column_sum += column_delta * column_delta;
            }

            const double denominator = std::sqrt(row_sum * column_sum);
            if (!std::isfinite(denominator) || denominator == 0.0) {
                continue;
            }

            const double correlation = numerator / denominator;
            correlations[row][column] = correlation;
            correlations[column][row] = correlation;
            matrix[row][column] = correlation;
            matrix[column][row] = correlation;
        }
    }

    HeatmapData display_matrix{
        data.feature_names,
        data.feature_names,
        matrix
    };
    return HeatmapPlotData{
        display_matrix,
        ObservedRange{-1.0, 1.0},
        data.feature_names,
        correlations
    };
}

} // namespace cpp_group_6
