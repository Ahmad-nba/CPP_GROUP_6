#include "swarm_plot.hpp"

#include "validator.hpp"

#include <algorithm>
#include <cmath>
#include <limits>
#include <map>
#include <optional>
#include <string>
#include <vector>

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

    double minimumValue = data.front().value;
    double maximumValue = minimumValue;
    for (const auto& point : data) {
        minimumValue = std::min(minimumValue, point.value);
        maximumValue = std::max(maximumValue, point.value);
    }

    const double valueRange = maximumValue - minimumValue;
    const double minimumVerticalSeparation =
        std::max(valueRange * 0.02, std::numeric_limits<double>::epsilon());

    struct PlacedPoint {
        double value;
        double offset;
    };

    std::map<std::string, std::vector<PlacedPoint>> placedPoints;
    SwarmPlotData result;
    result.points.reserve(data.size());

    for (const auto& point : data) {
        auto& categoryPoints = placedPoints[point.category];
        double offset = 0.0;
        std::size_t distance = 0;

        while (true) {
            const double candidate =
                distance == 0
                    ? 0.0
                    : ((distance + 1) / 2) * 0.1 *
                          (distance % 2 == 1 ? 1.0 : -1.0);
            const bool collides = std::any_of(
                categoryPoints.begin(),
                categoryPoints.end(),
                [&](const PlacedPoint& placed) {
                    return std::abs(point.value - placed.value) <
                               minimumVerticalSeparation &&
                           std::abs(candidate - placed.offset) < 0.2;
                }
            );

            if (!collides) {
                offset = candidate;
                break;
            }

            ++distance;
        }

        categoryPoints.push_back({point.value, offset});

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
