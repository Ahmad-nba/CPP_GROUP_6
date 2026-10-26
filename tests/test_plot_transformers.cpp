#include "heatmap_plot.hpp"
#include "point_plot.hpp"
#include "swarm_plot.hpp"

#include <cmath>
#include <iostream>
#include <limits>
#include <string>

using namespace cpp_group_6;

namespace {

int failures = 0;

void check(const std::string& name, bool condition) {
    if (condition) {
        std::cout << "[PASS] " << name << '\n';
    } else {
        std::cout << "[FAIL] " << name << '\n';
        ++failures;
    }
}

} // namespace

int main() {
    const Dataset data = {
        {"B", 2.0},
        {"A", -2.0},
        {"B", 4.0},
        {"A", 0.0}
    };

    const auto point = transformPointPlot(data);
    check("Point transform succeeds", point.has_value());
    check("Point transform creates one result per category",
          point.has_value() && point->points.size() == 2);
    check("Point transform uses deterministic category ordering",
          point.has_value() &&
          point->points[0].category == "A" &&
          point->points[1].category == "B");
    check("Point transform calculates category means",
          point.has_value() &&
          point->points[0].value == -1.0 &&
          point->points[1].value == 3.0);

    const auto swarm = transformSwarmPlot(data);
    check("Swarm transform succeeds", swarm.has_value());
    check("Swarm transform preserves every observation",
          swarm.has_value() && swarm->points.size() == data.size());
    check("Swarm transform preserves values and repeated categories",
          swarm.has_value() &&
          swarm->points[0].category == "B" &&
          swarm->points[0].value == 2.0 &&
          swarm->points[2].category == "B" &&
          swarm->points[2].value == 4.0);
    check("Swarm transform maps categories by first appearance",
          swarm.has_value() &&
          swarm->points[0].category_position == 0.0 &&
          swarm->points[1].category_position == 1.0);
    check("Swarm transform preserves numerical coordinates",
          swarm.has_value() &&
          swarm->points[1].numerical_position == -2.0 &&
          swarm->points[3].numerical_position == 0.0);
    check("Swarm transform keeps non-colliding values centered",
          swarm.has_value() &&
          swarm->points[0].offset == 0.0 &&
          swarm->points[2].offset == 0.0);

    const HeatmapData matrix{
        {"R1", "R2"},
        {"C1", "C2", "C3"},
        {{-2.0, 0.0, 3.0}, {4.0, 5.0, 6.0}}
    };
    const auto heatmap = transformHeatmap(matrix);
    check("Heatmap transform succeeds", heatmap.has_value());
    check("Heatmap transform preserves labels and dimensions",
          heatmap.has_value() &&
          heatmap->matrix.rowLabels == matrix.rowLabels &&
          heatmap->matrix.columnLabels == matrix.columnLabels &&
          heatmap->matrix.values == matrix.values);
    check("Heatmap transform calculates observed range",
          heatmap.has_value() &&
          heatmap->observed_range.min_observed == -2.0 &&
          heatmap->observed_range.max_observed == 6.0);

    const Dataset empty;
    check("Point transform rejects empty input",
          !transformPointPlot(empty).has_value());
    check("Swarm transform rejects empty input",
          !transformSwarmPlot(empty).has_value());
    check("Heatmap transform rejects empty matrix",
          !transformHeatmap(HeatmapData{{}, {}, {}}).has_value());
    check("Point transform rejects non-finite input",
          !transformPointPlot(
              Dataset{{"A", std::numeric_limits<double>::quiet_NaN()}}
          ).has_value());
    check("Heatmap transform rejects ragged input",
          !transformHeatmap(HeatmapData{{}, {}, {{1.0}, {2.0, 3.0}}})
              .has_value());

    std::cout << "\nFailures: " << failures << '\n';
    return failures == 0 ? 0 : 1;
}
