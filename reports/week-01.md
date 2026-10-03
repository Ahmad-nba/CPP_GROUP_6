# Week 1 Report — Project Scaffolding & Understanding

> **Purpose:** Document our initial understanding of the project, its structure, build system, development workflow, and the approach we will take toward deeper implementation.

---

## 1. Project Overview

### 1.1 The Core Project

**Assigned to:** Obuluk Agatha

Describe what the project is fundamentally about.
The purpose is to give programmers an easy " data first" library in C++ where they can just hand the program the data file , pick their axes  and instantly get a clean statistical graph.

Its major capabilities include:
Data and statistics 
Scaling
Drawing
Export

Expected Inputs : Comma seperated data files (.csv) full of words and numbers , along with user selected titles and column axes

Expected Outputs : 


# 2. Project Architecture & Folder Structure

### 2.1 Repository Structure

**Assigned to:** Janefer Mbabazi
```
project-name/
│
├── README.md
├── CMakeLists.txt
├── LICENSE
├── .gitignore
│
├── include/
│   └── project-name/
│       ├── module1.hpp
│       ├── module2.hpp
│       └── ...
│
├── src/
│   ├── module1.cpp
│   ├── module2.cpp
│   └── ...
│
├── tests/
│   ├── test_module1.cpp
│   ├── test_module2.cpp
│   └── ...
│
├── examples/
│   ├── example1.cpp
│   ├── example2.cpp
│   └── ...
│
├── reports/
│   ├── week-01.md
│   ├── week-02.md
│   ├── week-03.md
│   └── final-report.md
│
└── data/
    ├── input/
    └── output/


```


### 2.2 Folder Responsibilities

# include- 
It has only the files that are accessible to the external user.
# source -
 it has all the  files containing what the entire
 program does.
# test directory-
 this is where testing of whether the program works is done using differnt input values by the people designing the program.
# example directory-
 this is where implementing of the program happens by inputing different function inputs to see the output.
---

### 4.1 Build System Overview

Explain the overall build system and its components.

### 4.2 Understanding `CMakeLists.txt`

Document the important CMake instructions used by the project.

Example:

```cmake
cmake_minimum_required(...)
project(...)

add_executable(...)
```

Explain what each relevant command does.

### 4.3 CMake → Build System → Compiler

Document the relationship between the tools.

```text
CMake
  ↓
Build System / Generator
  ↓
Ninja / Make / etc.
  ↓
Compiler
  ↓
Object Files / Executable
```

Explain the role of each layer.

### 4.4 Configuring the Project

Document the configuration process.

```bash
# Commands used
```

Explain:

- What configuration does
- Where the build files are generated
- What generator is being used
- Any configuration requirements

### 4.5 Building the Project

Document the build process.

```bash
# Build commands
```

Explain what happens when the project is built.

### 4.6 Running the Project

Document:

```bash
# Run commands
```

Include:

- Location of the generated executable
- How the executable is launched
- Expected output
- Current running status

### 4.7 Build Issues Encountered

Document any issues encountered during configuration/building.

| Issue | Cause | Resolution |
| ----- | ----- | ---------- |
|       |       |            |
|       |       |            |

---

# 9. Next Phase

### 9.1 Areas Requiring Deeper Investigation

What parts of the project require further investigation?

-
-
-

### 9.2 Planned Technical Work

What will we actually do in the next phase?

1.
2.
3.
4.

# 10. Conclusion

Summarize the team's Week 1 progress.

Address:

- What do we now understand about the project?
- What have we successfully set up?
- What remains unclear?
- What is our immediate next step?

---

## Appendix

### A. Useful Commands

```bash
# Project configuration


# Project build


# Running the project


# Testing
```

### B. Important References

-
-
-

### C. Additional Diagrams / Notes

_Add any supporting diagrams, screenshots, or technical notes here._
