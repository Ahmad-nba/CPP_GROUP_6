#ifndef CPP_GROUP_6_MODULE1_HPP
#define CPP_GROUP_6_MODULE1_HPP

#include <string>
#include <vector>

namespace cpp_group_6{

    struct DataPoint{
        std::string category;
        double value;
    };

    using Dataset = std::vector<DataPoint>;

    struct NumericalDataset {
        std::vector<std::string> feature_names;
        std::vector<std::vector<double>> values;
    };
}// namespace cpp_group_6
#endif