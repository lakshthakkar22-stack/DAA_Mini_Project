# Smart Grocery Shopping List Optimizer

## 1. Project Overview

The Smart Grocery Shopping List Optimizer is a simple menu-driven grocery management application developed as part of the Design and Analysis of Algorithms (DAA) project. It allows users to add grocery items with a price and priority, search for items by name, view items in order of priority, choose the best items for a given budget, and delete items through a console interface.

The project demonstrates the practical application of dynamic programming, string matching and sorting algorithms.

## 2. Objectives

* To select the best items within a budget using the 0/1 Knapsack dynamic programming algorithm.
* To implement item searching using the Naive String Matching algorithm.
* To arrange items by priority using sorting.
* To provide a simple and interactive menu-driven interface.
* To demonstrate the practical use of DAA concepts in a real-world application.

## 3. Technologies Used

* **C++:** Complete implementation of the application, including the DAA algorithms.
* **C++ Standard Library:** `vector`, `string`, `algorithm` (`std::sort`), `iomanip` and `iostream` for data storage, sorting and input/output.

## 4. Features

* Add new items with name, price and priority.
* Search items by full or partial name (case-insensitive).
* Display items by priority (highest first).
* Optimize the list for a budget to get the highest total priority.
* Delete an item by exact name (case-insensitive).
* Handle invalid menu input and invalid numbers safely.
* Items are stored in memory during the program run.

## 5. Algorithms Used

### 0/1 Knapsack (Dynamic Programming)

The price of an item is treated as its weight and its priority as its value. The algorithm builds a table `dp[i][b]` that stores the best total priority using the first `i` items with a budget of `b`. For each item, it either skips the item or buys it, and keeps the better result. The selected items are found by tracing back through the table.

Time Complexity:

* O(N × B) time.
* O(N × B) space (needed to trace back the selected items).

Here, N is the number of items and B is the budget.

### Naive String Matching

The Naive String Matching algorithm checks a search pattern against an item name by comparing characters at each possible position. It is used for full-name and partial-name searching. Both the name and the pattern are converted to lowercase first.

Time Complexity:

* Best case: O(m), when the pattern is found at the start of the name.
* Worst case: O(n × m) for one name, or O(N × L × m) across the whole list.

Here, n is the length of the item name, m is the length of the search pattern, L is the maximum name length and N is the number of items.

### Sorting

Items are sorted by priority (highest first) using `std::sort()` with a custom comparator. If two items have the same priority, they are ordered alphabetically. Sorting is done on a copy of the list, so the original order is not changed.

Time Complexity:

* O(N log N) comparisons.

## 6. Project Structure

* `main.cpp` — C++ source file with the complete implementation.
* `README.md` — Project documentation.
* `Outputs/` — Screenshots of the program output.

## 7. How to Run the Project

1. Download or clone the project folder.
2. Open the folder in Visual Studio Code (or any C++ editor).
3. Make sure a C++ compiler (such as g++) is installed.
4. Compile the program:

   ```bash
   g++ main.cpp -o grocery
   ```

5. Run the program:

   ```bash
   ./grocery
   ```

   On Windows, use `grocery.exe`.

6. Use the menu to add, search, view, optimize and delete items.

No additional framework or package installation is required.

## 8. Important Implementation Note

This is a console-based C++ application. It does not have a web interface or a graphical interface. Items are stored in memory only and are lost when the program ends. Prices must be whole numbers because they are used as indices in the dynamic programming table.

## 9. Conclusion

The Smart Grocery Shopping List Optimizer demonstrates how dynamic programming, string matching and sorting algorithms can be applied to grocery planning. The project combines algorithmic concepts with a simple menu-driven program to make budget planning easier to understand and use.

It also provides a foundation for future improvements, such as saving the list in a file, preventing duplicate items, supporting item quantities and decimal prices, and adding a graphical user interface.
