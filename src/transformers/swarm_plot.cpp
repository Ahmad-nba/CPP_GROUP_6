#include "swarm_plot.hpp"

#include "validator.hpp"

#include <map>
#include <optional>
#include <string>

namespace cpp_group_6 {

std::optional<SwarmPlotData> transformSwarmPlot(const Dataset& data) {
    SwarmPlotValidator validator(data);
    if (!validator.validate().valid) {
        return std::nullopt;
    }

    std::map<std::string, double> categoryPositions;
    for (const auto& point : data) {
        if (categoryPositions.find(point.category) == categoryPositions.end()) {
            categoryPositions.emplace(
                point.category,
                static_cast<double>(categoryPositions.size())
            );
        }
    }

    std::map<std::string, std::size_t> categoryCounts;
    SwarmPlotData result;
    result.points.reserve(data.size());

    for (const auto& point : data) {
        const std::size_t occurrence = categoryCounts[point.category]++;
        const double distance = static_cast<double>((occurrence + 1) / 2) * 0.1;
        const double offset =
            occurrence == 0
                ? 0.0
                : (occurrence % 2 == 1 ? distance : -distance);

        result.points.push_back(SwarmPlotPoint{
            point.category,
            point.value,
            categoryPositions.at(point.category),
            point.value,
            offset
        });
    }

    return result;
}

} // namespace cpp_group_6
