# Templates. 
- A template allows us to write a function or class that operates on different data types without having to rewrite the same implementation for every type.

- We can have function templates or class templates. 

## Syntax for a template. 
- 
```
    template <typename T>
    T add(T a, T b) {
        return a + b;
    }
```
- The function above now at runtime accepts any data type to execute at runtime. 
- It can take in int, float, double, etc.

# using the template function.
``` add(2, 3) // returns 5
add(2.5, 3.5) // returns 6.0
```

 ### The 'Concept'
 - A concept is a compile-time predicate that constrains the types that can be used with a template.

 ### How we can use it in our project. 
 
![Diagram for how we can use templates in our code.  ](<WhatsApp Image 2026-11-03 at 6.25.11 PM.jpeg>)

## Area of use. 

```
 cpp
template <typename T>
struct DataPoint {
    std::string category;
    T value;
};

template <typename T>
using Dataset = std::vector<DataPoint<T>>;


Usage:

 cpp
Dataset<int> integerDataset;
Dataset<float> floatDataset;
Dataset<double> decimalDataset;


A data point could be created as:

 cpp
DataPoint<int> point{"East", 25};
DataPoint<double> measurement{"West", 25.75};


```


### C. Why use a template?

The structure of a data point remains the same: it has a category and a
numerical value. Only the numerical representation changes.

A class template avoids defining separate structures for integer, float,
and double data points.

However, the benefit must be weighed against the cost of changing every
component that currently expects Dataset.