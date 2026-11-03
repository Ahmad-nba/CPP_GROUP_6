WEEK 2 INPUT VALIDATION MODULE - IMPLEMENTATION REPORT

## 1. What's completed so far
Repository structure was established by designing a clean folder separating public headers (include), source code (src), testing scrips (tests), example implementation (examples) and documetation reports (reports).

## 2. In progress 

We are building the input validation module for data visualization library . Instead of reading complex csv files right away, we ensure data is fed directly through the C++ code to get the core logic working.The input module establishes how data is represented and validated before being passed to subsequent components of the visualization library and this key.

The module basically focuses on two primary responsibilities:

1. Data representation: It focuses on grouping related data together forexample pairing a category label with it's number like {shoes, 40}, student's name and marks like {Esther,90}.This ensures that the rest of the program can read it.In simple terms define a consistent structure for storing categories and their numerical values.

2. Data validation: We are adding data validators acting as a security gatekeeper. This checks data to make sure people aren't trying to plot missing values or pass text/strinds where numbers are supposed to go.In simple terms this checks whether a dataset satisfies the rules required by the current implementation.With this, we can describe  the kind of data required to produce the graph.

## 3. Detailed explanation of the files added in this week

**File:** `include/CPP_GROUP_6/module1.hpp`

### 3.1 The `DataPoint` Structure
This groups two related objects into one object such as category label and its numerical value.for example {shoes, 40}. This creates one object. amusing a datapoint structure makes the data easy for other components to access and process.

## 4. Implementing Validation with a C++ Class

**Files:**

* `include/CPP_GROUP_6/validator.hpp`
* `src/validator.cpp`

3.1 The `ValidationResult` Structure
Implementing Validation Using a C++ Class

In our group project, we used a C++ class called `DataValidator` to check whether the data entered meets the required conditions. We created a `ValidationResult` structure to show whether the data is valid and to store any errors found.

The `validate()` method performs the checking and returns the results without changing the original data. We separated the code into `validator.hpp` and `validator.cpp` to make it easier to organize, understand, and maintain.

In conclusion, this approach helps us detect errors, keep our code organized, and reuse the same validation method in different parts of the project.

## 5. Validation Logic and Rules
The validate() function is used to test whether a certain condition is correct or wrong and returns a value according to the criteria followed.

### 5.1 Implemented Validation Rules
As earleir introduced, validate() is used to test a condition 
it checks the input data to make sure no invalid information is passed. 
-> missing values in the plot column.
-> Strings as values to plot, they can be labels but not plot values. 

## 6.Possible challenges that may occur 
The programmer may input completely empty datasets, negative numbers where maybe only possitive numbers are required and also mixed-up data columns.
## 6.1 Overcoming the challenges
This is all catered for by the validator that gives a clear helpful error message so the programmer knows why their data failed. 

### 7.Conclusion
We successfully built the foundation for our data's journey into the visualization library. By creating the Input Validation and Data Representation modules, we ensured that our program can safely catch errors, handle missing pieces, and organize category labels and values neatly. With this safe pipeline in place, we are now fully prepared to head into Week 3 to analyze value ranges and start connecting our data to a rendering framework.

## 8. Plans for next week
1. Datasetview: We plan to ensure that the validated data is split into two distinct tracts ie category labels for the X-axis and numerical figures for the Y-axis. Also ensure both tracks maintain strict alignment using index positions so that a label never gets mismatched from it's corresponding value.
2. Qt Rendering: We anticipate that the data will eventually need to fit into a graphical interface framework like Qt for rendering swarmplots, point plots and heat maps.