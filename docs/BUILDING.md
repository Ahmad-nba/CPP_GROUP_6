# Building and Running

This project uses CMake to generate build files and Ninja to compile them.
It has two independent build trees:

- `build/` is the Qt-independent library and test build.
- `build-qt/` is the Qt-enabled build and contains the plot applications.

Both directories are generated output and are ignored by Git. Configure them
locally after cloning.

## Requirements

- CMake 3.20 or newer
- A C++17 compiler
- Ninja
- Qt 6 Widgets for the graphical applications

On Windows with MSYS2 UCRT64, install the matching toolchain packages:

```bash
pacman -S --needed \
  git \
  mingw-w64-ucrt-x86_64-gcc \
  mingw-w64-ucrt-x86_64-cmake \
  mingw-w64-ucrt-x86_64-ninja
pacman -S --needed mingw-w64-ucrt-x86_64-qt6-base
```

Use the UCRT64 compiler with the UCRT64 Qt package. Do not mix UCRT64
libraries with MINGW64 or MSVC Qt installations.

## Build the core library and tests

From the repository root:

```bash
cmake -S . -B build -G Ninja \
  -DCPP_GROUP_6_BUILD_POINT_PLOT=OFF
cmake --build build
ctest --test-dir build --output-on-failure
```

The core build contains the `cpp_group_6` static library and all unit-test
executables. It does not require Qt.

The current test suite reports one known failure in
`test_plot_transformers`: the swarm transformer offsets repeated observations
even when their values do not collide. The build itself succeeds, and the
validator, heatmap-correlation, and remaining tests pass. Treat a CTest exit
code of `8` as this known behavioral failure until that separate issue is
addressed.

To build a single target:

```bash
cmake --build build --target test_validator
```

## Build the Qt applications

Configure the Qt build separately. If Qt is installed under MSYS2 UCRT64,
the prefix can be supplied explicitly:

```bash
cmake -S . -B build-qt -G Ninja \
  -DCPP_GROUP_6_BUILD_POINT_PLOT=ON \
  -DCMAKE_PREFIX_PATH=C:/msys64/ucrt64
cmake --build build-qt
ctest --test-dir build-qt --output-on-failure
```

The option name is historical: when enabled, it builds all three
applications:

- `point_plot_run`
- `heatmap_run`
- `swarm_plot_run`

Build one application when needed:

```bash
cmake --build build-qt --target point_plot_run
```

## Run a visualization on Windows

In PowerShell, make the Qt runtime DLLs available and launch the executable:

```powershell
$env:PATH = "C:\msys64\ucrt64\bin;" + $env:PATH
.\build-qt\point_plot_run.exe
```

The other applications are launched similarly:

```powershell
.\build-qt\heatmap_run.exe
.\build-qt\swarm_plot_run.exe
```

Each application opens a Qt window and writes a PNG to
`examples/saved_plots/`. The directory is created automatically.

If Qt reports that it cannot load a platform plugin, set the plugin paths
before launching:

```powershell
$env:QT_PLUGIN_PATH = "C:\msys64\ucrt64\share\qt6\plugins"
$env:QT_QPA_PLATFORM_PLUGIN_PATH = "C:\msys64\ucrt64\share\qt6\plugins\platforms"
```

### Ideal workflow in MSYS2 UCRT64 to run a plot.
```
cd ~/dev/learning/cpp/CPP_GROUP_6/build-qt

cmake --build . --target heatmap_run

export PATH=/c/msys64/ucrt64/bin:$PATH
export QT_PLUGIN_PATH=/c/msys64/ucrt64/share/qt6/plugins
export QT_QPA_PLATFORM_PLUGIN_PATH=/c/msys64/ucrt64/share/qt6/plugins/platforms

./heatmap_run.exe
```

The GUI event loop remains active until the window is closed. The PNG is
created during startup after the window has been rendered.

## Reconfigure or clean

After source changes, rebuild the relevant tree:

```bash
cmake --build build
cmake --build build-qt
```

If CMake options or compiler/Qt paths change, rerun the corresponding
configure command. To recreate both generated trees in PowerShell:

```powershell
Remove-Item -Recurse -Force build, build-qt
```

Then configure them again using the commands above. Do not copy build
directories between machines because their caches contain absolute paths.
