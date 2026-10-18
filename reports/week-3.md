# Plotting Engine: Dataset Separation and Value Analysis

## 1. Milestone Objective

Briefly describe the purpose of this milestone and its position in the plotting pipeline.

## 2. Implementation
2.1 Dataset View

Purpose
 The dataset view is responsible for organizing and displaying the data in a clear format.

Structures and functions implemented
 The implementation uses suitable C++ data structures, such as vectors and strings, to store category names and their corresponding values.

How categories and values are extracted
 Category names and numerical values are retrieved from the dataset and stored separately for further processing.

How category-value alignment is preserved
 Each category is kept in the same position as its corresponding numerical value. This ensures that the correct value corresponds  with the correct category when the data is displayed or plotted.

2.2 Numerical Value Analysis

Purpose
 Numerical value analysis identifies important numerical information in the dataset, most importantly the minimum and maximum values. These values help to determine the range of the data and help in the plotting process.

Structures and functions implemented
 The implementation uses numerical data structures and functions to check the values in a dataset.

How minimum and maximum values are determined
 The first numerical value can be used to initialize both the minimum and maximum. The program then check the remaining values. If a value is smaller than the current minimum, the minimum is changed. If a value is larger than the current maximum, the maximum is changed. After processing all the values, the program has identified the minimum and maximum values.

How empty input is handled
 The program checks whether the dataset contains any numerical values before attempting to calculate the minimum and maximum. If the dataset is empty, it avoids accessing nonexistent elements and handles the situation safely.

## 3. C++ Design Decisions

Briefl explained usage:

* "struct" for "DatasetView" and "ObservedRange". Structures group related data into a single type, improving code organization and readability.
* Functions for dataset transformation and value analysis. Separate functions handle different tasks, improving modularity, reusability, and maintainability.
* "const" references and standard-library algorithms where applicable. Constant references avoid unnecessary copying and prevent modification through the reference, while standard-library algorithms simplify data processing and reduce repetitive code.


## 4. Testing and Results

| Test Case       | Expected Result             | Actual Result | Status |
| --------------- | --------------------------- | ------------- | ------ |
| Positive values | Correct minimum and maximum |               |        |
| Negative values | Correct minimum and maximum |               |        |
| Mixed values    | Correct minimum and maximum |               |        |
| Single value    | Minimum equals maximum      |               |        |
| All-zero values | Both extrema equal zero     |               |        |
| Empty values    | No observed range returned  |               |        |

**Build status:**
**Test execution status:**
**Issues encountered and resolutions:**

## 5. Files and Responsibilities

| File                 | Responsibility                                         |
| -------------------- | ------------------------------------------------------ |
| `dataset_view.hpp`   | Declares `DatasetView` and the transformation function |
| `dataset_view.cpp`   | Extracts categories and values from `Dataset`          |
| `observed_range.hpp` | Defines `ObservedRange`                                |
| `value_analysis.hpp` | Declares the numerical analysis function               |
| `value_analysis.cpp` | Determines the observed minimum and maximum            |
| Test files           | Verify dataset transformation and numerical analysis   |

*Update this table to match the actual implementation.*

## 6. Milestone Outcome

* **Completed:**
* **Outstanding issues:**
* **Next milestone:** Derivation of the plotting range from the observed extrema.

## 7. Scope Boundary

This milestone covers dataset separation and numerical value analysis only. Plot-range derivation, scaling, bar geometry, and Qt rendering are outside its scope.
