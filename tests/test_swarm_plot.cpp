#include "swarm_plot.hpp"

#include <cmath>
#include <algorithm>
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
        {"B", 10.0}, {"A", 15.0}, {"B", 10.0},
        {"A", 15.0}, {"C", 20.0}
    };
    const auto original = data;
    const auto result = transformSwarmPlot(data);

    check("Swarm transformation succeeds", result.has_value());
    check(
        "Every observation is preserved",
        result.has_value() && result->points.size() == data.size()
    );
    check(
        "Category order follows first appearance",
        result.has_value() &&
        result->points[0].category_position == 0.0 &&
        result->points[1].category_position == 1.0 &&
        result->points[4].category_position == 2.0
    );
    check(
        "Values and categories are preserved",
        result.has_value() &&
        result->points[0].category == data[0].category &&
        result->points[0].value == data[0].value &&
        result->points[3].category == data[3].category &&
        result->points[3].value == data[3].value
    );
    check(
        "Duplicate values receive separate positions",
        result.has_value() &&
        result->points[0].offset != result->points[2].offset &&
        result->points[1].offset != result->points[3].offset
    );

    const auto repeatedResult = transformSwarmPlot(data);
    check(
        "Transformation is deterministic",
        result.has_value() && repeatedResult.has_value() &&
        result->points.size() == repeatedResult->points.size() &&
        std::equal(
            result->points.begin(),
            result->points.end(),
            repeatedResult->points.begin(),
            [](const SwarmPlotPoint& left, const SwarmPlotPoint& right) {
                return left.offset == right.offset;
            }
        )
    );
    check(
        "Input remains unchanged",
        data.size() == original.size() &&
        data[0].category == original[0].category &&
        data[0].value == original[0].value
    );

    Dataset dense;
    for (int index = 0; index < 100; ++index) {
        dense.push_back({"Dense", 5.0});
    }
    const auto denseResult = transformSwarmPlot(dense);
    check(
        "Dense categories preserve every observation",
        denseResult.has_value() && denseResult->points.size() == dense.size()
    );
    check(
        "Empty input is rejected",
        !transformSwarmPlot(Dataset{}).has_value()
    );
    check(
        "Non-finite input is rejected",
        !transformSwarmPlot(
            Dataset{{"A", std::numeric_limits<double>::quiet_NaN()}}
        ).has_value()
    );

    std::cout << "\nFailures: " << failures << '\n';
    return failures == 0 ? 0 : 1;
}
