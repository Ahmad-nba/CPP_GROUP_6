# Plotting Engine: Dataset Separation and Value Analysis

## 1. Milestone Objective

Briefly describe the purpose of this milestone and its position in the plotting pipeline.

## 2. Implementation

### 2.1 Dataset View

* **Purpose:**
* **Structures and functions implemented:**
* **How categories and values are extracted:**
* **How category-value alignment is preserved:**

### 2.2 Numerical Value Analysis

* **Purpose:**
* **Structures and functions implemented:**
* **How minimum and maximum values are determined:**
* **How empty input is handled:**

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
