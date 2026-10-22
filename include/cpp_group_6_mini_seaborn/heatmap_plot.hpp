#ifndef CPP_GROUP_6_HEATMAP_PLOT_HPP
#define CPP_GROUP_6_HEATMAP_PLOT_HPP

#include "validator.hpp"
#include "observed_range.hpp"

#include <optional>

namespace cpp_group_6 {

struct HeatmapPlotData {
    HeatmapData matrix;
    ObservedRange observed_range;
};

std::optional<HeatmapPlotData> transformHeatmap(const HeatmapData& data);

} // namespace cpp_group_6

#endif
