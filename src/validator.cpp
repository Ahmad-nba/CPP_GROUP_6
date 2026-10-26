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
    : matrix_data_(&data),
      numerical_data_(nullptr) {}

HeatmapValidator::HeatmapValidator(const NumericalDataset& data)
    : matrix_data_(nullptr),
      numerical_data_(&data) {}

ValidationResult HeatmapValidator::validate() const {
    if (numerical_data_ != nullptr) {
        ValidationResult result{true, {}};
        const auto& data = *numerical_data_;

        if (data.feature_names.empty()) {
            result.valid = false;
            result.errors.push_back("Heatmap requires at least one feature.");
        }

        if (data.values.size() < 2) {
            result.valid = false;
            result.errors.push_back(
                "Heatmap requires at least two observations."
            );
        }

        if (data.feature_names.size() !=
            (data.values.empty() ? 0 : data.values.front().size())) {
            result.valid = false;
            result.errors.push_back(
                "Feature count must match the numerical row width."
            );
        }

        for (std::size_t feature = 0;
             feature < data.feature_names.size();
             ++feature) {
            if (data.feature_names[feature].empty()) {
                result.valid = false;
                result.errors.push_back(
                    "Feature " + std::to_string(feature + 1) +
                    " cannot be empty."
                );
            }

            for (std::size_t previous = 0; previous < feature; ++previous) {
                if (data.feature_names[feature] ==
                    data.feature_names[previous]) {
                    result.valid = false;
                    result.errors.push_back(
                        "Feature names must be unique."
                    );
                    break;
                }
            }
        }

        if (!data.values.empty()) {
            const std::size_t feature_count = data.values.front().size();
            for (std::size_t row = 0; row < data.values.size(); ++row) {
                if (data.values[row].size() != feature_count) {
                    result.valid = false;
                    result.errors.push_back(
                        "Row " + std::to_string(row + 1) +
                        ": Numerical row length is inconsistent."
                    );
                    continue;
                }

                for (std::size_t feature = 0;
                     feature < data.values[row].size();
                     ++feature) {
                    if (!std::isfinite(data.values[row][feature])) {
                        result.valid = false;
                        result.errors.push_back(
                            "Cell (" + std::to_string(row + 1) + ", " +
                            std::to_string(feature + 1) +
                            "): Value must be finite."
                        );
                    }
                }
            }

            if (result.valid && feature_count > 0) {
                for (std::size_t feature = 0;
                     feature < feature_count;
                     ++feature) {
                    const double first = data.values.front()[feature];
                    bool has_variation = false;
                    for (const auto& row : data.values) {
                        if (row[feature] != first) {
                            has_variation = true;
                            break;
                        }
                    }

                    if (!has_variation) {
                        result.valid = false;
                        result.errors.push_back(
                            "Feature " + std::to_string(feature + 1) +
                            ": Pearson correlation is undefined for a "
                            "constant feature."
                        );
                    }
                }
            }
        }

        return result;
    }

    const auto& data = *matrix_data_;
    ValidationResult result{true, {}};

    if (data.values.empty()) {
        return ValidationResult{false, {"Heatmap matrix cannot be empty."}};
    }

    const std::size_t columnCount = data.values.front().size();
    if (columnCount == 0) {
        result = invalidResult();
        result.errors.push_back("Heatmap matrix must contain at least one column.");
    }

    if (!data.rowLabels.empty() &&
        data.rowLabels.size() != data.values.size()) {
        result.valid = false;
        result.errors.push_back(
            "Row label count must match the matrix row count."
        );
    }

    if (!data.columnLabels.empty() &&
        data.columnLabels.size() != columnCount) {
        result.valid = false;
        result.errors.push_back(
            "Column label count must match the matrix column count."
        );
    }

    for (std::size_t row = 0; row < data.values.size(); ++row) {
        const auto& values = data.values[row];

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

    for (std::size_t row = 0; row < data.rowLabels.size(); ++row) {
        if (data.rowLabels[row].empty()) {
            result.valid = false;
            result.errors.push_back(
                "Row label " + std::to_string(row + 1) +
                " cannot be empty."
            );
        }
    }

    for (std::size_t column = 0; column < data.columnLabels.size(); ++column) {
        if (data.columnLabels[column].empty()) {
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