# Qt Integration Report

## 1. Baseline

The existing project uses CMake with Ninja and C++17:

- CMake minimum version: 3.20
- CMake detected: 4.4.3
- Ninja detected: 1.13.2
- Compiler: MSYS2 UCRT64 GCC 15.2.0
- Compiler path: `C:\msys64\ucrt64\bin\g++.exe`
- Core library target: `cpp_group_6`

The current library contains the data model, validation, dataset view,
numerical analysis, and point, swarm, and heatmap transformation modules. The
core target has no Qt dependency.

The current CTest targets are:

- `test_module1`
- `test_validator`
- `test_value_analysis`
- `test_dataset_view`
- `test_plot_transformers`

Baseline commands executed:

```text
cmake --build build
ctest --test-dir build --output-on-failure
```

Result:

```text
100% tests passed out of 5
```

No pre-existing test failures were observed during this audit.

## 2. Qt availability

The following Qt discovery commands were checked:

```text
qmake
qtpaths
```

Neither command is currently available.

The following locations were checked and did not contain a Qt installation:

```text
C:\Qt
C:\Program Files\Qt
C:\msys64\ucrt64\include\qt6
C:\msys64\mingw64\include\qt6
```

No Qt6 DLLs or Qt package configuration were found in the MSYS2 UCRT64
environment. CMake therefore cannot currently discover `Qt6::Widgets`.

MSYS2 package search confirms that a matching UCRT64 package is available:

```text
ucrt64/mingw-w64-ucrt-x86_64-qt6-base 6.10.1-2
```

The package is built for the same UCRT64 environment as the active GCC
compiler. The installation command for an MSYS2 UCRT64 terminal is:

```text
pacman -S --needed mingw-w64-ucrt-x86_64-qt6-base
```

The package is now installed and verified in the UCRT64 environment:

- Installed package: `mingw-w64-ucrt-x86_64-qt6-base 6.10.1-2`
- Qt CMake configuration:
  `C:\msys64\ucrt64\lib\cmake\Qt6\Qt6Config.cmake`
- Widgets runtime library:
  `C:\msys64\ucrt64\bin\Qt6Widgets.dll`
- Qt path tool:
  `C:\msys64\ucrt64\bin\qtpaths6.exe`

The Qt package must not be mixed with MSVC-built Qt libraries or packages from
the MSYS2 MINGW64 environment.

## 3. CMake integration

The optional `CPP_GROUP_6_BUILD_QT_DEMO` option was added to
`CMakeLists.txt` and defaults to `OFF`. When enabled, CMake requires Qt6
Widgets and creates the separate `cpp_group_6_qt_demo` executable.

The integration is:

```cmake
option(CPP_GROUP_6_BUILD_QT_DEMO
       "Build the Qt Widgets integration demo"
       OFF)

if(CPP_GROUP_6_BUILD_QT_DEMO)
    find_package(Qt6 REQUIRED COMPONENTS Widgets)

    add_executable(cpp_group_6_qt_demo
        examples/qt_integration_demo.cpp
    )
    target_link_libraries(cpp_group_6_qt_demo
        PRIVATE
            cpp_group_6
            Qt6::Widgets
    )
endif()
```

The option should default to `OFF` so the existing Qt-independent library and
tests remain buildable on machines without Qt. When explicitly enabled,
missing Qt must be a configuration error rather than silently skipping the
demo.

Qt must be linked only to the application target. Existing data-model,
validation, transformation, and numerical-analysis headers must remain free
of Qt includes.

## 4. Application target

The Qt application source is:

```text
examples/qt_integration_demo.cpp
```

The application constructs a `QApplication`, displays a titled `QLabel`
window, sets an initial size, and enters the event loop. It does not implement
plot rendering or modify existing plot transformers.

The expected launch command after successful configuration and build is:

```text
build\cpp_group_6_qt_demo.exe
```

This command is the launch command for the built demo:

## 5. Verification

Commands executed:

```text
cmake -S . -B build-qt -G Ninja -DCPP_GROUP_6_BUILD_QT_DEMO=ON
cmake --build build-qt
ctest --test-dir build-qt --output-on-failure
cmake -S . -B build-core-only -G Ninja -DCPP_GROUP_6_BUILD_QT_DEMO=OFF
cmake --build build-core-only
ctest --test-dir build-core-only --output-on-failure
```

Observed results:

- The Qt-enabled configuration found Qt6 Widgets and completed successfully.
- `cpp_group_6_qt_demo.exe` compiled and linked successfully.
- The Qt-enabled CTest run passed all five existing tests.
- The core-only configuration completed without Qt discovery and built the
  existing targets successfully.
- The core-only CTest run passed all five existing tests.
- CMake emitted a non-fatal `WrapVulkanHeaders` not-found message while
  configuring Qt; it did not affect the Widgets target or build.

The demo was launched with:

```text
build-qt\cpp_group_6_qt_demo.exe
```

For the runtime check, the UCRT64 runtime directory was placed on `PATH`, and
the process reported:

```text
WindowHandle=1838988
WindowTitle=CPP Group 6 - Qt Integration
HasExited=False
```

The process was then closed by its specific PID. This verified that the
application initialized `QApplication`, created a visible desktop window, and
remained running in its event loop until closed.

The GUI demo is intentionally not registered as a normal CTest test because
it runs an event loop until its window is closed.

## 6. Current status

The milestone is complete. Qt is installed for the matching UCRT64 GCC
toolchain, the optional application target builds without coupling Qt to the
core library, and both Qt-enabled and core-only configurations pass the
existing test suite.

The next milestone can add renderer-specific Qt code while continuing to keep
plot-ready data structures and transformation logic independent of Qt.
