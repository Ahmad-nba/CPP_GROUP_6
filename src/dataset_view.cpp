#include "dataset_view.hpp"

namespace cpp_group_6 {

DatasetView createDatasetView(const Dataset& data) {
    DatasetView view;

    view.categories.reserve(data.size());
    view.values.reserve(data.size());

    for (const auto& point : data) {
        view.categories.push_back(point.category);
        view.values.push_back(point.value);
    }

    return view;
}

} // namespace cpp_group_6