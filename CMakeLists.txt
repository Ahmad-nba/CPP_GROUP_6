cmake_minimum_required(VERSION 3.20)
project(CPP_GROUP_6 VERSION  4.4.3 )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(cpp_group_6
    src/module1.cpp
    src/validator.cpp
    src/value_analysis.cpp
    src/dataset_view.cpp
    src/point_plot.cpp
    src/swarm_plot.cpp
    src/heatmap_plot.cpp
    # src/module2.cpp
)

target_include_directories(cpp_group_6
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include/cpp_group_6_mini_seaborn
)

enable_testing()

add_executable(test_module1 tests/test_module1.cpp)
target_link_libraries(test_module1 PRIVATE cpp_group_6)
add_test(NAME test_module1 COMMAND test_module1)

add_executable(test_validator tests/test_validator.cpp)
target_link_libraries(test_validator PRIVATE cpp_group_6)
add_test(NAME test_validator COMMAND test_validator)

add_executable(test_value_analysis tests/test_value_analysis.cpp)
target_link_libraries(test_value_analysis PRIVATE cpp_group_6)
add_test(NAME test_value_analysis COMMAND test_value_analysis)

add_executable(test_dataset_view tests/test_dataset_view.cpp)
target_link_libraries(test_dataset_view PRIVATE cpp_group_6)
add_test(NAME test_dataset_view COMMAND test_dataset_view)

add_executable(test_plot_transformers tests/test_plot_transformers.cpp)
target_link_libraries(test_plot_transformers PRIVATE cpp_group_6)
add_test(NAME test_plot_transformers COMMAND test_plot_transformers)

# add_executable(example1 examples/example1.cpp)
# target_link_libraries(example1 PRIVATE cpp_group_6)

# add_executable(example2 examples/example2.cpp)
# target_link_libraries(example2 PRIVATE cpp_group_6)
