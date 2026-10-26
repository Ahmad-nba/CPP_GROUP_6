#ifndef CPP_GROUP_6_HEATMAP_PLOT_HPP
#define CPP_GROUP_6_HEATMAP_PLOT_HPP

#include "validator.hpp"
#include "observed_range.hpp"

#include <optional>
#include <vector>

namespace cpp_group_6 {

struct HeatmapPlotData {
    HeatmapData matrix;
    ObservedRange observed_range;
    std::vector<std::string> feature_names;
    std::vector<std::vector<std::optional<double>>> correlation_matrix;
};

std::optional<HeatmapPlotData> transformHeatmap(const HeatmapData& data);
std::optional<HeatmapPlotData> transformHeatmap(
    const NumericalDataset& data
);

} // namespace cpp_group_6

#endif
