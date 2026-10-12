#ifndef CPP_GROUP_6_VALIDATOR_HPP
#define CPP_GROUP_6_VALIDATOR_HPP

#include "CPP_GROUP_6/module1.hpp"

#include <string>
#include <vector>

namespace cpp_group_6 {

struct ValidationResult {
    bool valid;
    std::vector<std::string> errors;
};

class DataValidator {
public:
    ValidationResult validate(const Dataset& data) const;
};

} // namespace cpp_group_6

#endif