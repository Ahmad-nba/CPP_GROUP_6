#include "validator.hpp"

#include <cmath>

namespace cpp_group_6 {

ValidationResult DataValidator::validate(
    const Dataset& data
) const {

    ValidationResult result{true, {}};

    if (data.empty()) {
        result.valid = false;
        result.errors.push_back("Dataset cannot be empty.");
        return result;
    }

    for (std::size_t i = 0; i < data.size(); ++i) {
        const auto& point = data[i];

        if (point.category.empty()) {
            result.valid = false;
            result.errors.push_back(
                "Row " + std::to_string(i + 1) +
                ": Category cannot be empty."
            );
        }

        if (!std::isfinite(point.value)) {
            result.valid = false;
            result.errors.push_back(
                "Row " + std::to_string(i + 1) +
                ": Value must be finite."
            );
        }
    }

    return result;
}

} // namespace cpp_group_6