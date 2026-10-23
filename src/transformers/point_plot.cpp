#include "point_plot.hpp"

#include "validator.hpp"

#include <map>
#include <optional>
 
namespace cpp_group_6 {

std::optional<PointPlotData> transformPointPlot(const Dataset& data) {
    PointPlotValidator validator(data);
    if (!validator.validate().valid) {
        return std::nullopt;
    }

    std::map<std::string, std::pair<double, std::size_t>> grouped;
    for (const auto& point : data) {
        auto& group = grouped[point.category];
        group.first += point.value;
        ++group.second;
    }

    PointPlotData result;
    result.points.reserve(grouped.size());
    for (const auto& [category, group] : grouped) {
        result.points.push_back(
            PointPlotPoint{category, group.first / group.second}
        );
    }

    return result;
}

} // namespace cpp_group_6
