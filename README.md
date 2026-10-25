Smart Grocery Shopping List Optimizer
Project Overview

The Smart Grocery Shopping List Optimizer is a menu-driven C++ console application developed as a mini project for Design and Analysis of Algorithms (DAA) – 202045601. It helps a user manage a grocery list and choose the most valuable items for a given budget.

Each item has a name, a price and a priority. The program solves the 0/1 Knapsack problem using Dynamic Programming, where the price of an item is its weight and its priority is its value.

Features
Add an item (name, price, priority).
Search an item by full or partial name (case-insensitive).
Display the list in order of priority (highest first).
Optimize the list for a budget (best total priority within the budget).
Delete an item by exact name (case-insensitive).
Exit the program.

The program also handles invalid menu input and invalid numbers safely.

Algorithms Used
Feature	Algorithm	Time Complexity
Optimize for Budget	0/1 Knapsack (Dynamic Programming)	O(N × B) time, O(N × B) space
Search Item	Naive String Matching	O(N × L × m) worst case
Display by Priority	std::sort() with custom comparator (on a copy)	O(N log N) comparisons
Delete Item	Linear search + vector erase	O(N × L) + O(N)
Add Item	vector::push_back	O(1) amortized

Here N = number of items, B = budget, L = maximum item-name length, m = search-pattern length.

Data Structures Used
struct Item – stores name, price and priority.
vector<Item> – stores the grocery list dynamically.
2D vector<vector<int>> – dynamic programming table.
Temporary vector copy – used for priority-ordered display without changing the stored order.
How to Run
bash
g++ main.cpp -o grocery
./grocery

On Windows:

bash
g++ main.cpp -o grocery.exe
grocery.exe
Example (Why Dynamic Programming?)
Item	Price (Rs.)	Priority
Tea	10	6
Milk	20	10
Rice	30	12

With a budget of Rs. 50, a greedy choice (priority per rupee) picks Tea + Milk = priority 16. Dynamic programming picks Milk + Rice (Rs. 50) = priority 22, which is the optimal answer.

Output Screenshots

Screenshots of the program output are available in the Outputs folder.

<!-- After adding your screenshots, remove the comment markers below --> <!-- ![Output 1](Outputs/Output1.png) ![Output 2](Outputs/Output2.png) ![Output 3](Outputs/Output3.png) -->
Limitations
Items are stored in memory only and are lost when the program ends.
No file or database storage, and no graphical interface.
Duplicate items are not prevented and quantities are not handled.
Prices must be whole numbers; memory and time grow with the budget value.
Future Scope
Save and load the list from a file.
Prevent duplicate items.
Support item quantities (bounded knapsack).
Support decimal prices.
Reduce optimizer memory to O(B) when only the best total is needed.
Add a graphical user interface.
Project Details
Student: Laksh Thakkar (12402080601070)
Faculty Guide: Minakashi Patil, Assistant Professor
Subject: Design and Analysis of Algorithms (202045601)
Institute: A D Patel Institute of Technology, CVM University
Academic Year: 2026–2027
