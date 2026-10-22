#ifndef CPP_GROUP_6_SWARM_PLOT_HPP
#define CPP_GROUP_6_SWARM_PLOT_HPP

#include "module1.hpp"

#include <optional>
#include <string>
#include <vector>

namespace cpp_group_6 {

struct SwarmPlotPoint {
    std::string category;
    double value;
    double category_position;
    double numerical_position;
    double offset;
};

struct SwarmPlotData {
    std::vector<SwarmPlotPoint> points;
};

std::optional<SwarmPlotData> transformSwarmPlot(const Dataset& data);

} // namespace cpp_group_6

#endif
