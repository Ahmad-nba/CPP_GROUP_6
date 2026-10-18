#include "value_analysis.hpp"

#include <algorithm>

namespace cpp_group_6 {

std::optional<ObservedRange> analyzeValues(
    const DatasetView& view
) {
    if (view.values.empty()) {
        return std::nullopt;
    }

    const auto [min_it, max_it] = std::minmax_element(
        view.values.begin(),
        view.values.end()
    );

    return ObservedRange{
        *min_it,
        *max_it
    };
}

} // namespace cpp_group_6