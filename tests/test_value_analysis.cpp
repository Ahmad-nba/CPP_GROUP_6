#include "value_analysis.hpp"

#include <iostream>
#include <optional>
#include <string>
#include <vector>

using namespace cpp_group_6;

int main() {
    int passed = 0;
    int failed = 0;
    constexpr int total_tests = 6;

    std::cout << "\n========================================\n";
    std::cout << "   PHASE 2: VALUE ANALYSIS TESTS\n";
    std::cout << "========================================\n\n";

    // Test 1: Ordinary positive values
    {
        std::cout << "[TEST 1] Ordinary positive values\n";

        DatasetView positive{
            {"January", "February", "March", "April"},
            {15.0, 25.0, 10.0, 30.0}
        };

        auto result = analyzeValues(positive);

        bool success =
            result.has_value() &&
            result->min_observed == 10.0 &&
            result->max_observed == 30.0;

        if (success) {
            std::cout << "  [PASS] Minimum = 10, Maximum = 30\n";
            ++passed;
        } else {
            std::cout << "  [FAIL] Expected minimum = 10, maximum = 30\n";

            if (result.has_value()) {
                std::cout << "         Actual minimum = "
                          << result->min_observed << '\n';
                std::cout << "         Actual maximum = "
                          << result->max_observed << '\n';
            } else {
                std::cout << "         No analysis result returned.\n";
            }

            ++failed;
        }
    }

    // Test 2: All-negative values
    {
        std::cout << "\n[TEST 2] All-negative values\n";

        DatasetView negative{
            {"A", "B", "C"},
            {-8.0, -3.0, -12.0}
        };

        auto result = analyzeValues(negative);

        bool success =
            result.has_value() &&
            result->min_observed == -12.0 &&
            result->max_observed == -3.0;

        if (success) {
            std::cout << "  [PASS] Minimum = -12, Maximum = -3\n";
            ++passed;
        } else {
            std::cout << "  [FAIL] Expected minimum = -12, maximum = -3\n";

            if (result.has_value()) {
                std::cout << "         Actual minimum = "
                          << result->min_observed << '\n';
                std::cout << "         Actual maximum = "
                          << result->max_observed << '\n';
            } else {
                std::cout << "         No analysis result returned.\n";
            }

            ++failed;
        }
    }

    // Test 3: Mixed positive and negative values
    {
        std::cout << "\n[TEST 3] Mixed positive and negative values\n";

        DatasetView mixed{
            {"A", "B", "C", "D"},
            {-5.0, 10.0, 15.0, -2.0}
        };

        auto result = analyzeValues(mixed);

        bool success =
            result.has_value() &&
            result->min_observed == -5.0 &&
            result->max_observed == 15.0;

        if (success) {
            std::cout << "  [PASS] Minimum = -5, Maximum = 15\n";
            ++passed;
        } else {
            std::cout << "  [FAIL] Expected minimum = -5, maximum = 15\n";

            if (result.has_value()) {
                std::cout << "         Actual minimum = "
                          << result->min_observed << '\n';
                std::cout << "         Actual maximum = "
                          << result->max_observed << '\n';
            } else {
                std::cout << "         No analysis result returned.\n";
            }

            ++failed;
        }
    }

    // Test 4: A single value
    {
        std::cout << "\n[TEST 4] A single value\n";

        DatasetView single{
            {"A"},
            {7.0}
        };

        auto result = analyzeValues(single);

        bool success =
            result.has_value() &&
            result->min_observed == 7.0 &&
            result->max_observed == 7.0;

        if (success) {
            std::cout << "  [PASS] Minimum = 7, Maximum = 7\n";
            ++passed;
        } else {
            std::cout << "  [FAIL] Expected minimum = 7, maximum = 7\n";

            if (result.has_value()) {
                std::cout << "         Actual minimum = "
                          << result->min_observed << '\n';
                std::cout << "         Actual maximum = "
                          << result->max_observed << '\n';
            } else {
                std::cout << "         No analysis result returned.\n";
            }

            ++failed;
        }
    }

    // Test 5: All values are zero
    {
        std::cout << "\n[TEST 5] All values are zero\n";

        DatasetView zeros{
            {"A", "B", "C"},
            {0.0, 0.0, 0.0}
        };

        auto result = analyzeValues(zeros);

        bool success =
            result.has_value() &&
            result->min_observed == 0.0 &&
            result->max_observed == 0.0;

        if (success) {
            std::cout << "  [PASS] Minimum = 0, Maximum = 0\n";
            ++passed;
        } else {
            std::cout << "  [FAIL] Expected minimum = 0, maximum = 0\n";

            if (result.has_value()) {
                std::cout << "         Actual minimum = "
                          << result->min_observed << '\n';
                std::cout << "         Actual maximum = "
                          << result->max_observed << '\n';
            } else {
                std::cout << "         No analysis result returned.\n";
            }

            ++failed;
        }
    }

    // Test 6: Empty values
    {
        std::cout << "\n[TEST 6] Empty values\n";

        DatasetView empty{
            {},
            {}
        };

        auto result = analyzeValues(empty);

        bool success = !result.has_value();

        if (success) {
            std::cout << "  [PASS] Empty dataset correctly rejected\n";
            ++passed;
        } else {
            std::cout << "  [FAIL] Expected no analysis result for empty data\n";
            std::cout << "         An analysis result was returned.\n";
            ++failed;
        }
    }

    // Final test summary
    std::cout << "\n========================================\n";
    std::cout << "       VALUE ANALYSIS SUMMARY\n";
    std::cout << "========================================\n";

    std::cout << "Total tests : " << total_tests << '\n';
    std::cout << "Passed      : " << passed << '\n';
    std::cout << "Failed      : " << failed << '\n';

    double pass_rate =
        static_cast<double>(passed) / total_tests * 100.0;

    std::cout << "Pass rate   : " << pass_rate << "%\n";

    if (failed == 0) {
        std::cout << "\nRESULT: ALL TESTS PASSED\n";
    } else {
        std::cout << "\nRESULT: SOME TESTS FAILED\n";
    }

    std::cout << "========================================\n\n";

    return failed == 0 ? 0 : 1;
}
