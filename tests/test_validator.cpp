#include "validator.hpp"

#include <cmath>
#include <iostream>
#include <limits>
#include <string>

using namespace cpp_group_6;

namespace {

int countFailures = 0;

void runTest(const std::string& name, bool condition) {
    if (condition) {
        std::cout << "[PASS] " << name << '\n';
    } else {
        std::cout << "[FAIL] " << name << '\n';
        ++countFailures;
    }
}

bool containsError(const ValidationResult& result, const std::string& text) {
    for (const auto& error : result.errors) {
        if (error.find(text) != std::string::npos) {
            return true;
        }
    }
    return false;
}

bool datasetsEqual(const Dataset& left, const Dataset& right) {
    if (left.size() != right.size()) {
        return false;
    }

    for (std::size_t i = 0; i < left.size(); ++i) {
        if (left[i].category != right[i].category ||
            left[i].value != right[i].value) {
            return false;
        }
    }

    return true;
}

void testDatasetRules(const std::string& validatorName,
                      const Dataset& validData,
                      const Dataset& emptyData) {
    SwarmPlotValidator validator(validData);
    const DataValidator& polymorphicValidator = validator;
    const auto validResult = polymorphicValidator.validate();

    runTest(validatorName + " accepts valid data",
            validResult.valid && validResult.errors.empty());

    const Dataset original = validData;
    const auto unchangedResult = validator.validate();
    runTest(validatorName + " does not mutate input",
            validData.size() == original.size() &&
            datasetsEqual(validData, original) &&
            unchangedResult.valid);

    SwarmPlotValidator emptyValidator(emptyData);
    const auto emptyResult = emptyValidator.validate();
    runTest(validatorName + " rejects empty data",
            !emptyResult.valid &&
            containsError(emptyResult, "Dataset cannot be empty."));

    Dataset invalidData = {
        {"", std::numeric_limits<double>::quiet_NaN()},
        {"valid", std::numeric_limits<double>::infinity()},
        {"", -std::numeric_limits<double>::infinity()}
    };
    SwarmPlotValidator invalidValidator(invalidData);
    const auto invalidResult = invalidValidator.validate();

    runTest(validatorName + " reports all invalid observations",
            !invalidResult.valid && invalidResult.errors.size() == 5);
}

} // namespace

int main() {
    const Dataset validData = {
        {"apples", 10.0},
        {"apples", 0.0},
        {"bananas", -5.0},
        {"oranges", 20.0}
    };
    const Dataset emptyData;

    testDatasetRules("Swarm validator", validData, emptyData);

    PointPlotValidator pointValidator(validData);
    const DataValidator& pointBase = pointValidator;
    const auto pointResult = pointBase.validate();
    runTest("Point validator accepts repeated and signed values",
            pointResult.valid && pointResult.errors.empty());

    Dataset pointInvalidData = {{"", 1.0}};
    PointPlotValidator pointInvalidValidator(pointInvalidData);
    runTest("Point validator rejects empty category",
            !pointInvalidValidator.validate().valid);

    PointPlotValidator pointEmptyValidator(emptyData);
    runTest("Point validator rejects empty data",
            !pointEmptyValidator.validate().valid);

    Dataset pointNonFiniteData = {
        {"apples", std::numeric_limits<double>::quiet_NaN()},
        {"bananas", std::numeric_limits<double>::infinity()},
        {"oranges", -std::numeric_limits<double>::infinity()}
    };
    PointPlotValidator pointNonFiniteValidator(pointNonFiniteData);
    runTest("Point validator rejects non-finite values",
            !pointNonFiniteValidator.validate().valid &&
            pointNonFiniteValidator.validate().errors.size() == 3);

    HeatmapData validHeatmap{
        {"North", "South"},
        {"Q1", "Q2", "Q3"},
        {{1.0, 0.0, -2.0}, {3.0, 4.0, 5.0}}
    };
    HeatmapValidator heatmapValidator(validHeatmap);
    const DataValidator& heatmapBase = heatmapValidator;
    const auto heatmapResult = heatmapBase.validate();
    runTest("Heatmap validator accepts labelled rectangular matrix",
            heatmapResult.valid && heatmapResult.errors.empty());

    HeatmapData unlabelledHeatmap{
        {},
        {},
        {{1.0, 2.0}, {3.0, 4.0}}
    };
    runTest("Heatmap validator accepts omitted labels",
            HeatmapValidator(unlabelledHeatmap).validate().valid);

    runTest("Heatmap validator rejects empty matrix",
            !HeatmapValidator(HeatmapData{{}, {}, {}}).validate().valid);
    runTest("Heatmap validator rejects empty row",
            !HeatmapValidator(HeatmapData{{}, {}, {{}}}).validate().valid);
    runTest("Heatmap validator rejects inconsistent row lengths",
            !HeatmapValidator(HeatmapData{{}, {}, {{1.0}, {2.0, 3.0}}})
                 .validate().valid);

    const double nan = std::numeric_limits<double>::quiet_NaN();
    const double positiveInfinity = std::numeric_limits<double>::infinity();
    const double negativeInfinity = -positiveInfinity;
    runTest("Heatmap validator rejects NaN",
            !HeatmapValidator(HeatmapData{{}, {}, {{nan}}}).validate().valid);
    runTest("Heatmap validator rejects positive infinity",
            !HeatmapValidator(HeatmapData{{}, {}, {{positiveInfinity}}})
                                  .validate().valid);
    runTest("Heatmap validator rejects negative infinity",
            !HeatmapValidator(HeatmapData{{}, {}, {{negativeInfinity}}})
                                  .validate().valid);

    runTest("Heatmap validator rejects row-label count mismatch",
            !HeatmapValidator(HeatmapData{{"one"}, {}, {{1.0}, {2.0}}})
                 .validate().valid);
    runTest("Heatmap validator rejects column-label count mismatch",
            !HeatmapValidator(HeatmapData{{}, {"one"}, {{1.0, 2.0}}})
                 .validate().valid);
    runTest("Heatmap validator rejects empty supplied row label",
            !HeatmapValidator(HeatmapData{{""}, {}, {{1.0}}}).validate().valid);
    runTest("Heatmap validator rejects empty supplied column label",
            !HeatmapValidator(HeatmapData{{}, {""}, {{1.0}}}).validate().valid);

    std::cout << "\n========== TEST SUMMARY ==========\n";
    std::cout << "Failed: " << countFailures << '\n';
    std::cout << (countFailures == 0
                      ? "Result: ALL TESTS PASSED\n"
                      : "Result: SOME TESTS FAILED\n");

    return countFailures == 0 ? 0 : 1;
}
