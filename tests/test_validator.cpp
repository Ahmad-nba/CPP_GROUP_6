
#include "validator.hpp"

// #include <cmath>
#include <iostream>
#include <limits>
#include <string>

using namespace cpp_group_6;

int main() {
    DataValidator validator;

    int passed = 0;
    int failed = 0;

    auto run_test = [&](const std::string& name, bool condition) {
        if (condition) {
            std::cout << "[PASS] " << name << '\n';
            ++passed;
        } else {
            std::cout << "[FAIL] " << name << '\n';
            ++failed;
        }
    };

    // Test 1: Empty dataset
    Dataset empty_data;

    ValidationResult empty_result = validator.validate(empty_data);

    run_test(
        "Empty dataset is rejected",
        !empty_result.valid &&
        empty_result.errors.size() == 1 &&
        empty_result.errors[0] == "Dataset cannot be empty."
    );

    // Test 2: Valid dataset
    Dataset valid_data = {
        {"apples", 10.0},
        {"Bananas", 15.5},
        {"Oranges", 20.0}
    };

    ValidationResult valid_result = validator.validate(valid_data);

    run_test(
        "Valid dataset is accepted",
        valid_result.valid && valid_result.errors.empty()
    );

    // Test 3: Empty category
    Dataset empty_category_data = {
        {"", 10.0}
    };

    ValidationResult category_result =
        validator.validate(empty_category_data);

    run_test(
        "Empty category is rejected",
        !category_result.valid &&
        category_result.errors.size() == 1 &&
        category_result.errors[0] ==
            "Row 1: Category cannot be empty."
    );

    // Test 4: Infinite value
    Dataset infinite_value_data = {
        {"Apples", std::numeric_limits<double>::infinity()}
    };

    ValidationResult infinite_result =
        validator.validate(infinite_value_data);

    run_test(
        "Infinite value is rejected",
        !infinite_result.valid &&
        infinite_result.errors.size() == 1 &&
        infinite_result.errors[0] ==
            "Row 1: Value must be finite."
    );

    // Test 5: NaN value
    Dataset nan_data = {
        {"Apples", std::numeric_limits<double>::quiet_NaN()}
    };

    ValidationResult nan_result = validator.validate(nan_data);

    run_test(
        "NaN value is rejected",
        !nan_result.valid &&
        nan_result.errors.size() == 1 &&
        nan_result.errors[0] ==
            "Row 1: Value must be finite."
    );

    // Test summary
    std::cout << "\n========== TEST SUMMARY ==========\n";
    std::cout << "Total:  " << passed + failed << '\n';
    std::cout << "Passed: " << passed << '\n';
    std::cout << "Failed: " << failed << '\n';

    if (failed == 0) {
        std::cout << "Result: ALL TESTS PASSED\n";
    } else {
        std::cout << "Result: SOME TESTS FAILED\n";
    }

    return failed == 0 ? 0 : 1;
}

