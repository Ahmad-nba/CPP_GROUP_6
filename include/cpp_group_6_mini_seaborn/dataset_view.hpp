#ifndef CPP_GROUP_6_DATASET_VIEW_HPP
#define CPP_GROUP_6_DATASET_VIEW_HPP

#include "module1.hpp"

#include <string>
#include <vector>

namespace cpp_group_6 {

struct DatasetView {
    std::vector<std::string> categories;
    std::vector<double> values;
};

DatasetView createDatasetView(const Dataset& data);

} // namespace cpp_group_6

#endif
