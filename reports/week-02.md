# Input Validation Module — Implementation Report

## 1. Module Overview

The input module establishes how data is represented and validated before being passed to subsequent components of the visualization library and this key.

For this implementation phase, data is supplied 
directly through C++ code using a predefined data structure. External file input, such as CSV reading, is not included in the current scope.

The module has two primary responsibilities:

1. Data representation:  Define a consistent structure for storing categories and their numerical values.

2. Data validation:  Check whether a dataset satisfies the rules required by the current implementation.
 With this, we can describe  the kind of data required to produce the graph.

## 2. Data Representation in C++

**File:** `include/CPP_GROUP_6/module1.hpp`

### 2.1 The `DataPoint` Structure
This groups two related objects into one object such as category label and its numerical value.for example {shoes, 69}. This creates one object. amusing a datapoint structure makes the data easy for other components to access and process.

## 3. Implementing Validation with a C++ Class

**Files:**

* `include/CPP_GROUP_6/validator.hpp`
* `src/validator.cpp`

3.1 The `ValidationResult` Structure
Implementing Validation Using a C++ Class

In our group project, we used a C++ class called `DataValidator` to check whether the data entered meets the required conditions. We created a `ValidationResult` structure to show whether the data is valid and to store any errors found.

The `validate()` method performs the checking and returns the results without changing the original data. We separated the code into `validator.hpp` and `validator.cpp` to make it easier to organize, understand, and maintain.

In conclusion, this approach helps us detect errors, keep our code organized, and reuse the same validation method in different parts of the project.



## 4. Validation Logic and Rules

#The validate() function is used to test whether a certain condition is correct or wrong and returns a value according to the criteria followed.

### 4.1 Implemented Validation Rules

As earleir introduced, validate() is used to test a condition 
it checks the input data to make sure no invalid information is passed. 

-> missing values in the plot column.
-> Strings as values to plot, they can be labels but not plot values. 





### Conclusion

[Briefly explain what the input validation module now does, how its C++ structures and class work together, and whether the implementation and tests behaved as expected.]
