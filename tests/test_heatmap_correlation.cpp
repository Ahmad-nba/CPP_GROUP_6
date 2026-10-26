#include "heatmap_plot.hpp"

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

bool closeTo(double left, double right) {
    return std::abs(left - right) < 1e-9;
}

} // namespace

int main() {
    const NumericalDataset data{
        {"Positive", "Negative", "Zero"},
        {
            {1.0, 5.0, 1.0},
            {2.0, 4.0, 2.0},
            {3.0, 3.0, 1.0},
            {4.0, 2.0, 2.0},
            {5.0, 1.0, 1.0}
        }
    };
    const NumericalDataset original = data;
    const auto result = transformHeatmap(data);

    check("Correlation transform succeeds", result.has_value());
    check(
        "Correlation matrix has expected dimensions",
        result.has_value() &&
        result->correlation_matrix.size() == 3 &&
        result->correlation_matrix[0].size() == 3
    );
    check(
        "Feature ordering is preserved",
        result.has_value() &&
        result->feature_names == data.feature_names
    );
    check(
        "Perfect positive correlation is +1",
        result.has_value() &&
        result->correlation_matrix[0][0].has_value() &&
        closeTo(*result->correlation_matrix[0][0], 1.0)
    );
    check(
        "Perfect negative correlation is -1",
        result.has_value() &&
        result->correlation_matrix[0][1].has_value() &&
        closeTo(*result->correlation_matrix[0][1], -1.0)
    );
    check(
        "Zero correlation is calculated",
        result.has_value() &&
        result->correlation_matrix[0][2].has_value() &&
        closeTo(*result->correlation_matrix[0][2], 0.0)
    );
    check(
        "Correlation matrix is symmetric",
        result.has_value() &&
        result->correlation_matrix[1][0].has_value() &&
        result->correlation_matrix[0][1].has_value() &&
        closeTo(
            *result->correlation_matrix[1][0],
            *result->correlation_matrix[0][1]
        )
    );
    check(
        "Input is not mutated",
        data.feature_names == original.feature_names &&
        data.values == original.values
    );

    const NumericalDataset empty;
    check("Empty numerical dataset is rejected",
          !transformHeatmap(empty).has_value());
    check(
        "Non-finite values are rejected",
        !transformHeatmap(NumericalDataset{
            {"A", "B"},
            {{1.0, 2.0}, {std::numeric_limits<double>::infinity(), 3.0}}
        }).has_value()
    );
    check(
        "Constant features are rejected",
        !transformHeatmap(NumericalDataset{
            {"A", "B"},
            {{1.0, 2.0}, {1.0, 3.0}, {1.0, 4.0}}
        }).has_value()
    );

    std::cout << "\nFailures: " << failures << '\n';
    return failures == 0 ? 0 : 1;
}
