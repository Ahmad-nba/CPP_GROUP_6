#ifndef CPP_GROUP_6_POINT_PLOT_HPP
#define CPP_GROUP_6_POINT_PLOT_HPP

#include "module1.hpp"

#include <optional>
#include <string>
#include <vector>

namespace cpp_group_6 {

struct PointPlotPoint {
    std::string category;
    double value;
};

struct PointPlotData {
    std::vector<PointPlotPoint> points;
};

std::optional<PointPlotData> transformPointPlot(const Dataset& data);

} // namespace cpp_group_6

#endif
