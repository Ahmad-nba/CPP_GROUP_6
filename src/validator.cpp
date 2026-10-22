#include "validator.hpp"

#include <cmath>

namespace cpp_group_6 {

namespace {

ValidationResult validateDatasetImpl(const Dataset& data) {
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

ValidationResult invalidResult() {
    return ValidationResult{false, {}};
}

} // namespace

ValidationResult DataValidator::validateDataset(const Dataset& data) {
    return validateDatasetImpl(data);
}

SwarmPlotValidator::SwarmPlotValidator(const Dataset& data)
    : data_(data) {}

ValidationResult SwarmPlotValidator::validate() const {
    return DataValidator::validateDataset(data_);
}

PointPlotValidator::PointPlotValidator(const Dataset& data)
    : data_(data) {}

ValidationResult PointPlotValidator::validate() const {
    return DataValidator::validateDataset(data_);
}

HeatmapValidator::HeatmapValidator(const HeatmapData& data)
    : data_(data) {}

ValidationResult HeatmapValidator::validate() const {
    ValidationResult result{true, {}};

    if (data_.values.empty()) {
        return ValidationResult{false, {"Heatmap matrix cannot be empty."}};
    }

    const std::size_t columnCount = data_.values.front().size();
    if (columnCount == 0) {
        result = invalidResult();
        result.errors.push_back("Heatmap matrix must contain at least one column.");
    }

    if (!data_.rowLabels.empty() &&
        data_.rowLabels.size() != data_.values.size()) {
        result.valid = false;
        result.errors.push_back(
            "Row label count must match the matrix row count."
        );
    }

    if (!data_.columnLabels.empty() &&
        data_.columnLabels.size() != columnCount) {
        result.valid = false;
        result.errors.push_back(
            "Column label count must match the matrix column count."
        );
    }

    for (std::size_t row = 0; row < data_.values.size(); ++row) {
        const auto& values = data_.values[row];

        if (values.empty()) {
            result.valid = false;
            result.errors.push_back(
                "Row " + std::to_string(row + 1) +
                ": Heatmap row cannot be empty."
            );
        }

        if (values.size() != columnCount) {
            result.valid = false;
            result.errors.push_back(
                "Row " + std::to_string(row + 1) +
                ": Matrix row length is inconsistent."
            );
        }

        for (std::size_t column = 0; column < values.size(); ++column) {
            if (!std::isfinite(values[column])) {
                result.valid = false;
                result.errors.push_back(
                    "Cell (" + std::to_string(row + 1) + ", " +
                    std::to_string(column + 1) +
                    "): Value must be finite."
                );
            }
        }
    }

    for (std::size_t row = 0; row < data_.rowLabels.size(); ++row) {
        if (data_.rowLabels[row].empty()) {
            result.valid = false;
            result.errors.push_back(
                "Row label " + std::to_string(row + 1) +
                " cannot be empty."
            );
        }
    }

    for (std::size_t column = 0; column < data_.columnLabels.size(); ++column) {
        if (data_.columnLabels[column].empty()) {
            result.valid = false;
            result.errors.push_back(
                "Column label " + std::to_string(column + 1) +
                " cannot be empty."
            );
        }
    }

    return result;
}

} // namespace cpp_group_6