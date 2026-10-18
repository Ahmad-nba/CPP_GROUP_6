# Problem Description: Failing to build or add the executable to the library after adding src and header files. 


## Observed Behaviour:
THe build process fails with an error message:
```
$ ninja
[2/2] Linking CXX executable test_value_analysis.exe
FAILED: [code=1] test_value_analysis.exe 
C:\Windows\system32\cmd.exe /C "cd . && C:\msys64\ucrt64\bin\c++.exe   CMakeFiles/test_value_analysis.dir/tests/test_value_analysis.cpp.obj -o test_value_analysis.exe -Wl,--out-implib,libtest_value_analysis.dll.a -Wl,--major-image-version,0,--minor-image-version,0  libcpp_group_6.a  -lkernel32 -luser32 -lgdi32 -lwinspool -lshell32 -lole32 -loleaut32 -luuid -lcomdlg32 -ladvapi32 && cd ."
collect2.exe: error: ld returned 1 exit status
ninja: build stopped: subcommand failed.
```

## Navigation: 
-> Look out in Cmake file; 
1. Make sure you have added the src file to the library creation method, 
```
add_library(cpp_group_6
    src/module1.cpp
    src/validator.cpp
    src/value_analysis.cpp
    # src/module2.cpp
)
```

2. Make sure you have added the add executable method to create an executable especially for test files. 
```
add_executable(test_value_analysis tests/test_value_analysis.cpp)
target_link_libraries(test_value_analysis PRIVATE cpp_group_6)
add_test(NAME test_value_analysis COMMAND test_value_analysis)
```

## Root cause: 
-> The Linker clearly reaches step 2/2 of adding my test executable to the libarary binary file but fails. 

-> From the definition of a linker: It collects the object files from around the codebase, now an error at the linker level, means it looked for a object file to use it in producing the out put and could not find it. 

-> Therefore for the stage your building, look at the header files, make sure they are properly included in the source files. Look at the src files and make sure they are included in the cmake file, and look at the test files and make sure they are included in the cmake file.