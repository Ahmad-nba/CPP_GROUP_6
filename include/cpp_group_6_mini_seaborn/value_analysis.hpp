#ifndef CPP_GROUP_6_VALUE_ANALYSIS_HPP
#define CPP_GROUP_6_VALUE_ANALYSIS_HPP

#include "dataset_view.hpp"
#include "observed_range.hpp"

#include <optional>

namespace cpp_group_6 {

std::optional<ObservedRange> analyzeValues(
    const DatasetView& view
);

} // namespace cpp_group_6

#endif