cmake_minimum_required(VERSION 3.20)
project(CPP_GROUP_6 VERSION  4.4.3 )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(cpp_group_6
    src/module1.cpp
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

# add_executable(test_module2 tests/test_module2.cpp)
# target_link_libraries(test_module2 PRIVATE cpp_group_6)
# add_test(NAME test_module2 COMMAND test_module2)

# add_executable(example1 examples/example1.cpp)
# target_link_libraries(example1 PRIVATE cpp_group_6)

# add_executable(example2 examples/example2.cpp)
# target_link_libraries(example2 PRIVATE cpp_group_6)
