#include "dataset_view.hpp"

#include <iostream>
#include <string>

using namespace cpp_group_6;

// Print a DatasetView in a readable format.
void printDatasetView(const std::string& title, const DatasetView& view) {
    std::cout << "\n--- " << title << " ---\n";

    std::cout << "Categories: ";
    for (const auto& category : view.categories) {
        std::cout << category << " ";
    }

    std::cout << "\nValues:     ";
    for (const auto& value : view.values) {
        std::cout << value << " ";
    }

    std::cout << "\n";
}

int main() {
    int passed = 0;
    int failed = 0;

    auto run_test = [&](const std::string& name, bool success) {
        if (success) {
            std::cout << "[PASS] " << name << '\n';
            ++passed;
        } else {
            std::cout << "[FAIL] " << name << '\n';
            ++failed;
        }
    };

    // Dataset 1: Monthly sales
    Dataset data1 = {
        {"January", 15.0},
        {"February", 25.0},
        {"March", 10.0},
        {"April", 30.0}
    };

    DatasetView view1 = createDatasetView(data1);

    // Dataset 2: Values including negative numbers
    Dataset data2 = {
        {"A", -10.0},
        {"B", 0.0},
        {"C", 20.0}
    };

    DatasetView view2 = createDatasetView(data2);

    // Print both created DatasetViews.
    printDatasetView("Dataset View 1: Monthly Sales", view1);
    printDatasetView("Dataset View 2: Mixed Values", view2);

    // Test Dataset View 1.
    run_test(
        "Dataset 1 category count",
        view1.categories.size() == 4
    );

    run_test(
        "Dataset 1 value count",
        view1.values.size() == 4
    );

    run_test(
        "Dataset 1 categories and order",
        view1.categories == std::vector<std::string>{
            "January", "February", "March", "April"
        }
    );

    run_test(
        "Dataset 1 values and order",
        view1.values == std::vector<double>{
            15.0, 25.0, 10.0, 30.0
        }
    );

    // Test Dataset View 2.
    run_test(
        "Dataset 2 category count",
        view2.categories.size() == 3
    );

    run_test(
        "Dataset 2 value count",
        view2.values.size() == 3
    );

    run_test(
        "Dataset 2 categories and order",
        view2.categories == std::vector<std::string>{
            "A", "B", "C"
        }
    );

    run_test(
        "Dataset 2 values and order",
        view2.values == std::vector<double>{
            -10.0, 0.0, 20.0
        }
    );

    // Summary.
    const int total = passed + failed;

    std::cout << "\n========== TEST SUMMARY ==========\n";
    std::cout << "Total tests: " << total << '\n';
    std::cout << "Passed:      " << passed << '\n';
    std::cout << "Failed:      " << failed << '\n';

    if (failed == 0) {
        std::cout << "RESULT: ALL TESTS PASSED\n";
    } else {
        std::cout << "RESULT: SOME TESTS FAILED\n";
    }

    return failed == 0 ? 0 : 1;
}

