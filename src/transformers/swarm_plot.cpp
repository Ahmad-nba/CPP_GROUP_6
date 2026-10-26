#include "swarm_plot.hpp"

#include "validator.hpp"

#include <algorithm>
#include <cmath>
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

    double minimum = data.front().value;
    double maximum = data.front().value;
    for (const auto& point : data) {
        minimum = std::min(minimum, point.value);
        maximum = std::max(maximum, point.value);
    }

    const double span = maximum - minimum;
    const double normalizedSpan = span > 0.0 ? span : 1.0;
    constexpr double verticalCollisionDistance = 0.06;
    constexpr double horizontalCollisionDistance = 0.08;
    constexpr double offsetStep = 0.08;
    constexpr double maximumOffset = 0.36;

    struct PlacedPoint {
        double normalized_value;
        double offset;
    };
    std::map<std::string, std::vector<PlacedPoint>> placedPoints;

    SwarmPlotData result;
    result.points.reserve(data.size());

    for (const auto& point : data) {
        const double normalizedValue =
            (point.value - minimum) / normalizedSpan;
        auto& categoryPoints = placedPoints[point.category];
        double offset = 0.0;
        double bestOffset = 0.0;
        std::size_t bestCollisionCount = categoryPoints.size() + 1;

        for (int candidateIndex = 0; candidateIndex <= 9; ++candidateIndex) {
            const int side = candidateIndex == 0
                ? 0
                : (candidateIndex % 2 == 1 ? 1 : -1);
            const int distanceIndex =
                candidateIndex == 0 ? 0 : (candidateIndex + 1) / 2;
            const double candidateOffset =
                side * distanceIndex * offsetStep;

            if (std::abs(candidateOffset) > maximumOffset) {
                continue;
            }

            const std::size_t collisionCount = static_cast<std::size_t>(
                std::count_if(
                categoryPoints.begin(),
                categoryPoints.end(),
                [&](const PlacedPoint& placed) {
                    return std::abs(normalizedValue - placed.normalized_value) <
                               verticalCollisionDistance &&
                           std::abs(candidateOffset - placed.offset) <
                               horizontalCollisionDistance;
                }
                )
            );
            if (collisionCount < bestCollisionCount) {
                bestCollisionCount = collisionCount;
                bestOffset = candidateOffset;
            }
            if (collisionCount == 0) {
                offset = candidateOffset;
                break;
            }
        }
        if (bestCollisionCount != 0) {
            offset = bestOffset;
        }

        categoryPoints.push_back({normalizedValue, offset});

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
