#include "heatmap_plot.hpp"

#include "dataset_view.hpp"
#include "value_analysis.hpp"

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

    return HeatmapPlotData{data, *range};
}

} // namespace cpp_group_6
