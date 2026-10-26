# Swarm Plot Implementation Report

## Implementation

The swarm plot now follows the existing pipeline:

```text
Dataset
  -> SwarmPlotValidator
  -> transformSwarmPlot
  -> SwarmPlotData
  -> SwarmPlotWidget
  -> QPainter
```

The core transformation remains Qt-independent.

### Files added

- `include/cpp_group_6_mini_seaborn/swarm_plot_widget.hpp`
- `widget_scaling/swarm_plot_widget.cpp`
- `examples/swarm_plot_run.cpp`
- `tests/test_swarm_plot.cpp`

### Files modified

- `src/transformers/swarm_plot.cpp`
  - Replaced the alternating offset stub with deterministic collision-aware
    positioning.
- `tests/test_plot_transformers.cpp`
  - Updated the old stub-specific expectation so non-colliding observations
    remain centered.
- `CMakeLists.txt`
  - Added the dedicated swarm transformation test and `swarm_plot_run` Qt
    executable.

## Transformation and positioning

`transformSwarmPlot()`:

1. Validates the input using `SwarmPlotValidator`.
2. Preserves every observation and its original category/value.
3. Assigns category positions in first-appearance order.
4. Normalizes values within the dataset's numerical range for collision checks.
5. Tries candidate horizontal offsets closest to the category center first.
6. Separates points when their normalized vertical positions and horizontal
   positions would overlap.
7. Uses a bounded search and preserves all points even for dense categories.

The offset is a visual horizontal displacement only. It does not change the
observation's numerical value or category.

For dense categories where every candidate collides, the algorithm selects the
candidate with the fewest collisions after the bounded search. This guarantees
termination without silently discarding observations.

## Rendering

`SwarmPlotWidget` renders:

- A chart title.
- Numerical horizontal grid lines and y-axis labels.
- Category labels on the x-axis.
- Individual circular observation markers.
- Category-centered points plus their transformed horizontal offsets.
- A responsive plot area based on the current widget dimensions.
- An error message for invalid plot data.

The vertical coordinate is calculated from each point's original numerical
value using the widget's numerical axis range. Qt-specific rendering is
contained in the widget implementation.

## Tests

The dedicated swarm tests cover:

- Successful transformation.
- Preservation of every observation.
- First-appearance category ordering.
- Category and value preservation.
- Separate offsets for duplicate values.
- Deterministic output.
- Input immutability.
- Dense categories.
- Empty input rejection.
- Non-finite value rejection.

## Verification

Core build and tests passed:

```text
cmake --build build
ctest --test-dir build --output-on-failure
```

Result: all 7 tests passed.

Qt build and tests passed:

```text
cmake --build build-qt
ctest --test-dir build-qt --output-on-failure
```

Result: all 7 tests passed. The existing point-plot and heatmap targets and
the new `swarm_plot_run` target linked successfully.

The swarm Qt demo was launched from `C:\Windows\Temp` with the MSYS2 UCRT64
runtime path and remained active in the Qt event loop for the startup
verification period.

## Known limitations

- No automated screenshot or pixel-comparison test was added.
- Collision thresholds are normalized constants rather than calculated from
  final widget pixels. The widget still applies the same offsets consistently
  during rendering.
- The swarm demo does not currently export a PNG. Point-plot and heatmap PNG
  export paths remain unchanged.

## Suggested next step

If swarm image export is required, mirror the existing point-plot and heatmap
example export helper in `swarm_plot_run.cpp`, using the same
`examples/saved_plots` output directory.
