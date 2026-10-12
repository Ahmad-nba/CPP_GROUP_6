# Input Validation Module — Implementation Report

## 1. Module Overview

<!-- The input module establishes how data is represented and validated before being passed to subsequent components of the visualization library.

For this implementation phase, data is supplied directly through C++ code using a predefined data structure. External file input, such as CSV reading, is not included in the current scope.

The module has two primary responsibilities:

1. **Data representation:** Define a consistent structure for storing categories and their numerical values.
2. **Data validation:** Check whether a dataset satisfies the rules required by the current implementation. -->

### Current Input Flow
<!-- describe how the input enters and how we handle it to produce the graph -->
---

## 2. Data Representation in C++

**File:** `include/CPP_GROUP_6/module1.hpp`

### 2.1 The `DataPoint` Structure

<!-- ```cpp
struct DataPoint {
    std::string category;
    double value;
};
```

The `DataPoint` structure groups two related pieces of information into one object: a category label and its numerical value.

For example:

```cpp
DataPoint item{"Shoes", 120};
```

This creates one data point with the category `"Shoes"` and the value `120`.

Using a structure keeps the category and its associated value together, making the data easier for other components to access and process. -->
<!--  -->

## 3. Implementing Validation with a C++ Class

**Files:**

* `include/CPP_GROUP_6/validator.hpp`
* `src/validator.cpp`

### 3.1 The `ValidationResult` Structure

```cpp
struct ValidationResult {
    bool valid;
    std::vector<std::string> errors;
};
```

This structure represents the outcome of validating a dataset.

* `valid` indicates whether the dataset passed validation.
* `errors` stores descriptions of any validation problems found.

Returning both fields allows the calling program to determine whether validation succeeded and understand why it failed.

### 3.2 The `DataValidator` Class

```cpp
class DataValidator {
public:
    ValidationResult validate(const Dataset& data) const;
};
```

The `DataValidator` class encapsulates the validation operation behind a public method named `validate()`.

The method receives a dataset and returns a `ValidationResult`.

**Understanding the method signature:**

* `const Dataset& data`: Passes the dataset by reference without making a full copy and prevents the method from modifying the supplied dataset.
* `ValidationResult`: Defines the information returned to the caller.
* The trailing `const`: Indicates that the method does not modify the observable state of the `DataValidator` object.

The class separates validation behavior from the demonstration program and future plotting components. Other parts of the project can use the same validator instead of implementing their own checks.

### 3.3 Why Use a Class?

The class provides a clear interface for the validation responsibility. The calling code only needs to create a `DataValidator` object and call its `validate()` method; it does not need to know the internal validation procedure.

The interface is declared in `validator.hpp`, while its implementation is defined in `validator.cpp`. This separates what the module exposes from how it performs its work.

Although validation could also be implemented as a standalone function, the class provides an explicit component boundary for this project.

---

## 4. Validation Logic and Rules

The `validate()` method checks the supplied dataset and returns a result describing whether it meets the current requirements.

### 4.1 Implemented Validation Rules

<!-- | Condition                              | Result  | Reason                                                              |
| -------------------------------------- | ------- | ------------------------------------------------------------------- |
| Dataset is empty                       | Invalid | No data points are available.                                       |
| Category label is empty                | Invalid | The data point has no category label.                               |
| Value is NaN                           | Invalid | The numerical value is not finite.                                  |
| Value is positive or negative infinity | Invalid | The numerical value is not finite.                                  |
| Value is zero                          | Valid   | Zero is a legitimate numerical value.                               |
| Value is negative but finite           | Valid   | Negative values can represent meaningful quantities such as losses. |
| Category labels are duplicated         | Allowed | Duplicate-category handling has not yet been restricted.            | -->

<!-- Describe in your own words -->
### 4.2 How Validation Works

The implementation follows these steps:

1. Initialize a `ValidationResult` indicating success with an empty error list.
2. Check whether the dataset is empty. If it is, record an error and return immediately.
3. Iterate through the data points.
4. Check each category label for emptiness.
5. Check each numerical value using `std::isfinite()`.
6. Record descriptive error messages for any failed checks.
7. Return the final result.

The validator does not modify the original dataset. It examines the supplied data and reports its findings.

The current design also allows the validator to collect multiple errors in a single pass instead of stopping at the first invalid data point.




### Conclusion

[Briefly explain what the input validation module now does, how its C++ structures and class work together, and whether the implementation and tests behaved as expected.]
