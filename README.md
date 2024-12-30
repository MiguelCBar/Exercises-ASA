# Analysis and Synthesis of Algorithms Exercises

## Description
This repository contains three project reports and their respective implementations.

The reports are in Portuguese.

## Projects

### [Project 1: Optimizing Sheet Cutting](/Exercises-ASA/Exercise1OptimizingSheetCutting/exercise1.cpp)
#### Problem: Maximize the profit from cutting a sheet into pieces with predefined dimensions and values.
    - Dynamic programming is used to calculate the optimal cuts, considering horizontal and vertical possibilities.
    - Optimizations include processing only half the matrix (due to symmetry) and reducing redundant calculations.

### [Project 2: Maximum Disease Spread in a Graph](/Exercises-ASA/Exercise2MaximumDiseaseSpread/exercise2.cpp)
#### Problem: Determine the maximum number of "jumps" a disease can make between individuals in a directed graph, considering that individuals in a strongly connected component (SCC) infect each other instantly.
  - Two depth-first searches (DFS) are performed:
    - The first DFS determines the finish order of vertices.
    - The second DFS identifies SCCs and calculates the maximum jumps between them.

### [Project 3: Optimizing Toy and Package Production](/Exercises-ASA/Exercise3OptimizingToyAndPackageProduction/exercise3.py)
#### Problem: Maximize daily profits from toy production and special packages under capacity constraints.
  - The problem is formulated as a linear programming model:
    - Decision variables represent the production of toys and packages.
    - Constraints ensure production remains within capacity limits.
  - The model is solved using a linear programming solver.
  - A Python implementation uses the `PuLP` library to solve the linear programming problem.

## Credits
This project was developed by [Miguel Barbosa]() and [Diogo Almada]().
