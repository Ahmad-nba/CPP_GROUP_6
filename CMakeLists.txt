cmake_minimum_required(VERSION 3.20)
project(CPP_GROUP_6 VERSION  4.4.3 )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(
    CPP_GROUP_6_BUILD_POINT_PLOT
    "Build the Qt point plot application"
    OFF
)

add_library(cpp_group_6
    src/module1.cpp
    src/validator.cpp
    src/value_analysis.cpp
    src/dataset_view.cpp
    src/transformers/point_plot.cpp
    src/transformers/swarm_plot.cpp
    src/transformers/heatmap_plot.cpp
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

add_executable(
    test_heatmap_correlation
    tests/test_heatmap_correlation.cpp
)
target_link_libraries(test_heatmap_correlation PRIVATE cpp_group_6)
add_test(NAME test_heatmap_correlation COMMAND test_heatmap_correlation)

add_executable(test_swarm_plot tests/test_swarm_plot.cpp)
target_link_libraries(test_swarm_plot PRIVATE cpp_group_6)
add_test(NAME test_swarm_plot COMMAND test_swarm_plot)

if(CPP_GROUP_6_BUILD_POINT_PLOT)
    find_package(Qt6 REQUIRED COMPONENTS Widgets)

    add_executable(
        point_plot_run
        examples/point_plot_run.cpp
        data/input/input_data.cpp
        widget_scaling/point_plot_widget.cpp
        include/cpp_group_6_mini_seaborn/point_plot_widget.hpp
        data/input/input_data.hpp
    )
    target_link_libraries(
        point_plot_run
        PRIVATE
            cpp_group_6
            Qt6::Widgets
    )
    target_compile_definitions(
        point_plot_run
        PRIVATE
            POINT_PLOT_OUTPUT_DIRECTORY="${CMAKE_CURRENT_SOURCE_DIR}/examples/saved_plots"
    )

    add_executable(
        heatmap_run
        examples/heatmap_run.cpp
        data/input/input_data.cpp
        widget_scaling/heatmap_plot_widget.cpp
        include/cpp_group_6_mini_seaborn/heatmap_plot_widget.hpp
        data/input/input_data.hpp
    )
    target_link_libraries(
        heatmap_run
        PRIVATE
            cpp_group_6
            Qt6::Widgets
    )
    target_compile_definitions(
        heatmap_run
        PRIVATE
            HEATMAP_OUTPUT_DIRECTORY="${CMAKE_CURRENT_SOURCE_DIR}/examples/saved_plots"
    )

    add_executable(
        swarm_plot_run
        examples/swarm_plot_run.cpp
        data/input/input_data.cpp
        widget_scaling/Swarm_plot_widget.cpp
        include/cpp_group_6_mini_seaborn/swarm_plot-widget.hpp
        data/input/input_data.hpp
    )
    target_link_libraries(
        swarm_plot_run
        PRIVATE
            cpp_group_6
            Qt6::Widgets
    )
    target_include_directories(
        point_plot_run
        PRIVATE
            ${PROJECT_SOURCE_DIR}/data/input
    )
    target_include_directories(
        heatmap_run
        PRIVATE
            ${PROJECT_SOURCE_DIR}/data/input
    )
    target_include_directories(
        swarm_plot_run
        PRIVATE
            ${PROJECT_SOURCE_DIR}/data/input
    )
    target_compile_definitions(
        swarm_plot_run
        PRIVATE
            SWARM_PLOT_OUTPUT_DIRECTORY="${CMAKE_CURRENT_SOURCE_DIR}/examples/saved_plots"
    )
endif()

# add_executable(example1 examples/example1.cpp)
# target_link_libraries(example1 PRIVATE cpp_group_6)

# add_executable(example2 examples/example2.cpp)
# target_link_libraries(example2 PRIVATE cpp_group_6)
