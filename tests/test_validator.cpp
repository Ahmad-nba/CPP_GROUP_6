#include "CPP_GROUP_6/validator.hpp"

#include <cassert>
#include <cmath>

using namespace cpp_group_6;

int main() {
    DataValidator validator;

    // Test 1: Valid dataset.
    Dataset valid_data = {
        {"Shoes", 120},
        {"Phones", 250},
        {"Books", 80}
    };

    assert(validator.validate(valid_data).valid);

    // Test 2: Empty dataset.
    Dataset empty_data;

    assert(!validator.validate(empty_data).valid);

    // Test 3: Missing category.
    Dataset missing_category = {
        {"Shoes", 120},
        {"", 250}
    };

    assert(!validator.validate(missing_category).valid);

    // Test 4: Non-finite numerical value.
    Dataset invalid_value = {
        {"Shoes", 120},
        {"Phones", std::nan("")}
    };

    assert(!validator.validate(invalid_value).valid);

    // Test 5: Zero and negative values.
    Dataset negative_values = {
        {"Profit", 100},
        {"Break-even", 0},
        {"Loss", -50}
    };

    assert(validator.validate(negative_values).valid);

    return 0;
}