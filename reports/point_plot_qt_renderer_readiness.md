# Point Plot to Qt Renderer Readiness

## Overall status

**Data pipeline ready; Qt rendering layer not started.**

The project has a clean separation between plot-data preparation and UI code.
The point-plot transformation is implemented and tested, but the Qt demo
currently only displays a `QLabel`; no chart or renderer is connected yet.

## Current data flow

```text
Dataset
  -> PointPlotValidator
  -> transformPointPlot()
  -> PointPlotData
  -> Qt renderer: not implemented
```

## Input model

[`module1.hpp`](../include/cpp_group_6_mini_seaborn/module1.hpp) defines the
input as categorical observations with numeric values:

```cpp
struct DataPoint {
    std::string category;
    double value;
};

using Dataset = std::vector<DataPoint>;
```

## Validation

[`validator.cpp`](../src/validator.cpp) validates point-plot input by checking:

- The dataset is not empty.
- Every category is non-empty.
- Every numeric value is finite.
- Validation errors are collected in `ValidationResult`.

Invalid input causes the point transformation to return `std::nullopt`.

## Point-plot transformation

[`point_plot.cpp`](../src/point_plot.cpp) currently:

- Groups observations by category.
- Calculates the arithmetic mean for each category.
- Produces one output point per category.
- Uses deterministic category ordering through `std::map`.
- Preserves each category as a string and each calculated mean as a `double`.

The output types in
[`point_plot.hpp`](../include/cpp_group_6_mini_seaborn/point_plot.hpp) are:

```cpp
struct PointPlotPoint {
    std::string category;
    double value;
};

struct PointPlotData {
    std::vector<PointPlotPoint> points;
};
```

Example:

```text
Input:
B -> 2
A -> -2
B -> 4
A -> 0

Output:
A -> -1
B -> 3
```

## Tests

[`test_plot_transformers.cpp`](../tests/test_plot_transformers.cpp) verifies:

- Successful transformation.
- One output point per category.
- Deterministic category ordering.
- Correct category means.
- Rejection of empty datasets.
- Rejection of non-finite values.

The transformer is included in the core library through
[`CMakeLists.txt`](../CMakeLists.txt). Qt remains isolated to the optional demo
target.

## What is ready for the renderer

The Qt renderer can consume:

```cpp
const auto transformed = cpp_group_6::transformPointPlot(data);

if (!transformed) {
    // Display validation failure
}

for (const auto& point : transformed->points) {
    const std::string& category = point.category;
    const double value = point.value;
}
```

The renderer already has:

- Category labels.
- Numeric Y-values.
- Stable category ordering.
- Validated finite values.
- One drawable point per category.

## What is still missing

`PointPlotData` is not yet a complete rendering model. The renderer still
needs decisions and implementation for:

- X-axis positions for categories, such as `0, 1, 2...`.
- Y-axis range and margins.
- Pixel-to-data coordinate conversion.
- Axis and tick rendering.
- Point size, color, and styling.
- Labels and title.
- Handling empty or invalid transformation results.
- Optional tooltip or hover mapping back to category and value.
- A Qt widget or graphics implementation.

The current
[`qt_integration_demo.cpp`](../examples/qt_integration_demo.cpp) only creates
a `QApplication` and displays a `QLabel`; it does not consume `Dataset` or
`PointPlotData`.

## Recommended integration boundary

Keep the existing transformation independent of Qt:

```text
Dataset
  -> transformPointPlot()
  -> PointPlotData
  -> Qt adapter/widget
  -> screen coordinates and drawing
```

A first renderer can use a custom `QWidget` with `paintEvent()`. It should
receive `PointPlotData` and handle only coordinate mapping and drawing. For
each output point, a basic mapping could be:

```text
x = left_margin + category_index * category_spacing
y = plot_bottom - normalized(value) * plot_height
```

This preserves the current architecture and avoids introducing Qt types into
the core library.
