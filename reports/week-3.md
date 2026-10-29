# Weeek three report 
Plotting Engine: Dataset Separation and Value Analysis
# 1. Recap of the previous week two report 
In week two, our group worked on the input validation module. its purpose was to basically check whether the data provided to the plotting grogram is correct and yields the right results.
This (the validation module) is important because the program needs corect data it can process before being visualized on the graphs.
## 2. What we are working on this week 
This week emphasis is put on how to plot values that shall be visualized on the graphs. (bar graph, point plots,swarm plots, heatmaps.)
This is achieved through seperating datasets and analysing numerical values.  

## 2.1  Steps for plotting the values  
First, we validate the data to make sure the right values are passed with no errrors. 
Then, we split the values into the features(category names) on the x axis and  nunerical values that shall be on the y axis.
We then analyse the values to get a suitable scale
The features are divided into their own view as well as the values.
We can then develop a mathematical method for developing a suitable scale for the respective features and values scale.
this is developed by determing the maximum and minimum data values to get a range that will be accomaodated by a suitable numerical scale for the graph.
for example if our largest value is 100, the scale would run from 0 -100 with the intervals between the markings.
Afterwards other plotting tasks are performed, such as detemining interval sizes and the plotting the graphs using Qt.
### Dataset View

# 2.2 Structures and functions implemented
 The implementation uses suitable C++ data structures, such as vectors and strings, to store category names and their corresponding values.

# 2.3 How categories and values are extracted
 Category names and numerical values are retrieved from the dataset and stored separately for further processing.

# 2.4 How category-value alignment is preserved
 Each category is kept in the same position as its corresponding numerical value. This ensures that the correct value corresponds  with the correct category when the data is displayed or plotted.



## 2.4 How empty input is handled
 The program checks whether the dataset contains any numerical values before attempting to calculate the minimum and maximum. If the dataset is empty, it avoids accessing nonexistent elements and handles the situation safely.

## 3. C++ Design Decisions

### Brief explained usage:

* "struct" for "DatasetView" and "ObservedRange". Structures group related data into a single type, improving code organization and readability.
* Functions for dataset transformation and value analysis. Separate functions handle different tasks, improving modularity, reusability, and maintainability.
* "const" references and standard-library algorithms where applicable. Constant references avoid unnecessary copying and prevent modification through the reference, while standard-library algorithms simplify data processing and reduce repetitive code.
   DatasetView  -> splist the dataset
    ValueAnalysis -> analyze the values to get the minimum and maximum observed values 


## 4. Conclusion:
In conclusion, week three builds on the input validation module from the previous week ,adding on the plotting program by focusing on organising datasets and analysing their numerical values before they are visualized on the different graphs.

## Next week 
For the next week, we plan on the actual visualization of category features and their corresponding values on the graphs, that is to say, the bar graphs, swam plots, heatmaps,point plots, as we were assigned.

## challenges faced in this week
Keeping data correctly matched,for example making sure that every category actually matches its numerical value.
Handling of negative values, that is to say the program caters for every minimum number including the negatives, to mae the scale suitable for the available range.
 So far, this week those are thechallenges faced and then the program will be tested such that it behaves correctly when given positive umbers, negative values, zeroes and empty datasets.



 
    
        
     ```

### 