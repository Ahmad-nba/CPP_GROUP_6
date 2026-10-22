#ifndef CPP_GROUP_6_VALIDATOR_HPP
#define CPP_GROUP_6_VALIDATOR_HPP

#include "module1.hpp"

#include <string>
#include <vector>

namespace cpp_group_6 {

struct ValidationResult {
    bool valid;
    std::vector<std::string> errors;
};

class DataValidator {
public:
    virtual ~DataValidator() = default;

    virtual ValidationResult validate() const = 0;

protected:
    static ValidationResult validateDataset(const Dataset& data);
};

struct HeatmapData {
    std::vector<std::string> rowLabels;
    std::vector<std::string> columnLabels;
    std::vector<std::vector<double>> values;
};

class SwarmPlotValidator final : public DataValidator {
public:
    explicit SwarmPlotValidator(const Dataset& data);

    ValidationResult validate() const override;

private:
    const Dataset& data_;
};

class PointPlotValidator final : public DataValidator {
public:
    explicit PointPlotValidator(const Dataset& data);

    ValidationResult validate() const override;

private:
    const Dataset& data_;
};

class HeatmapValidator final : public DataValidator {
public:
    explicit HeatmapValidator(const HeatmapData& data);

    ValidationResult validate() const override;

private:
    const HeatmapData& data_;
};

} // namespace cpp_group_6

#endif
