# Plotting Engine: Dataset Separation and Value Analysis

## 1. plotting values
This week emphasis is put on how to plot values that shall be visualized on the graphs  

## 2. Implementation
first, we validate the data to make sure the right values are passed with no errrors. 
then, we split the values into the features on the x axis and  values that shall be on the y axis.
we then analyse the values to get a suitable scale 
the features are divided into their own view as well as the values 
we can then develop a mathematival mathod for delepoing a suitable scale for the respective features and values scale.
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

Briefly explain the use of:

* `struct` for `DatasetView` and `ObservedRange`.
* A function for dataset transformation and a function for value analysis.
* `const` references and standard-library algorithms where applicable.

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
