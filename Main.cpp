#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cctype>

using namespace std;

struct Item {
    string name;
    int price;
    int priority;
};

const int MAX_BUDGET = 100000;
long long comparisons = 0;

string toLowerCase(string s) {
    for (size_t i = 0; i < s.size(); i++) {
        s[i] = (char)tolower((unsigned char)s[i]);
    }
    return s;
}

void printLine() {
    cout << "  " << string(54, '-') << "\n";
}

void printComplexity(const string& timeC, const string& spaceC) {
    cout << "\n  Time Complexity  : " << timeC << "\n";
    cout << "  Space Complexity : " << spaceC << "\n";
}

bool readInt(const string& prompt, int minValue, int maxValue, int& value) {
    string line;
    cout << prompt;
    getline(cin, line);
    if (line.empty() || line.size() > 9) return false;
    for (size_t i = 0; i < line.size(); i++) {
        if (!isdigit((unsigned char)line[i])) return false;
    }
    value = stoi(line);
    return value >= minValue && value <= maxValue;
}

int getInt(const string& prompt, int minValue, int maxValue) {
    int value;
    while (!readInt(prompt, minValue, maxValue, value)) {
        cout << "  Invalid input. Enter a whole number from "
             << minValue << " to " << maxValue << ".\n";
    }
    return value;
}

// Naive String Matching: returns start position or -1.
// Every character comparison is counted in 'comparisons'.
int naiveSearch(const string& text, const string& pattern) {
    int n = (int)text.size();
    int m = (int)pattern.size();
    if (m == 0 || m > n) return -1;

    for (int i = 0; i <= n - m; i++) {
        int j = 0;
        while (j < m) {
            comparisons++;
            if (text[i + j] != pattern[j]) break;
            j++;
        }
        if (j == m) return i;
    }
    return -1;
}

bool compareItems(const Item& a, const Item& b) {
    comparisons++;
    if (a.priority != b.priority) return a.priority > b.priority;
    return toLowerCase(a.name) < toLowerCase(b.name);
}

void addItem(vector<Item>& items) {
    Item it;
    cout << "\n  Enter item name: ";
    getline(cin, it.name);
    if (it.name.empty()) {
        cout << "  Item name cannot be empty.\n";
        return;
    }
    it.price = getInt("  Enter price (whole number, Rs.): ", 1, MAX_BUDGET);
    it.priority = getInt("  Enter priority (higher = more important): ", 1, 1000000);
    items.push_back(it);
    cout << "  Item added successfully.\n";
    printComplexity("O(1) amortized (O(N) when the vector grows)", "O(1) extra");
}

void searchItem(const vector<Item>& items) {
    if (items.empty()) {
        cout << "\n  The list is empty.\n";
        return;
    }
    string query;
    cout << "\n  Enter item name or part of a name: ";
    getline(cin, query);
    if (query.empty()) {
        cout << "  Search text cannot be empty.\n";
        return;
    }

    string pattern = toLowerCase(query);
    comparisons = 0;
    int found = 0;

    cout << "\n  Naive String Matching steps (pattern = \"" << pattern << "\"):\n";
    printLine();
    for (size_t i = 0; i < items.size(); i++) {
        long long before = comparisons;
        int pos = naiveSearch(toLowerCase(items[i].name), pattern);
        cout << "  " << left << setw(20) << items[i].name;
        if (pos >= 0) {
            cout << "MATCH at position " << pos;
            found++;
        } else {
            cout << "no match";
        }
        cout << "  (" << (comparisons - before) << " comparisons)\n";
    }
    printLine();
    cout << "  Matching items found : " << found << "\n";
    cout << "  Total comparisons    : " << comparisons << "\n";
    printComplexity("Best O(m) per name, Worst O(N x L x m)", "O(1) auxiliary");
}

void displayByPriority(const vector<Item>& items) {
    if (items.empty()) {
        cout << "\n  The list is empty.\n";
        return;
    }
    vector<Item> sorted = items;  // sort a copy, original order stays unchanged
    comparisons = 0;
    sort(sorted.begin(), sorted.end(), compareItems);

    cout << "\n  " << left << setw(5) << "No." << setw(22) << "Item"
         << setw(12) << "Price(Rs.)" << "Priority\n";
    printLine();
    for (size_t i = 0; i < sorted.size(); i++) {
        cout << "  " << left << setw(5) << (i + 1) << setw(22) << sorted[i].name
             << setw(12) << sorted[i].price << sorted[i].priority << "\n";
    }
    printLine();
    cout << "  Comparisons made while sorting: " << comparisons << "\n";
    printComplexity("O(N log N) comparisons", "O(N) for the sorted copy");
}

void optimizeForBudget(const vector<Item>& items) {
    if (items.empty()) {
        cout << "\n  The list is empty.\n";
        return;
    }
    int budget = getInt("\n  Enter your budget (whole number, Rs.): ", 0, MAX_BUDGET);
    int n = (int)items.size();

    // dp[i][b] = best total priority using first i items with budget b
    vector<vector<int> > dp(n + 1, vector<int>(budget + 1, 0));
    long long steps = 0;

    for (int i = 1; i <= n; i++) {
        for (int b = 0; b <= budget; b++) {
            steps++;
            dp[i][b] = dp[i - 1][b];
            if (items[i - 1].price <= b) {
                dp[i][b] = max(dp[i][b],
                               dp[i - 1][b - items[i - 1].price] + items[i - 1].priority);
            }
        }
    }

    // Show the DP table step by step (only for small budgets)
    if (budget <= 30) {
        cout << "\n  Dynamic Programming table (rows = items, columns = budget):\n";
        cout << "  " << left << setw(14) << "Item \\ Budget";
        for (int b = 0; b <= budget; b++) cout << right << setw(4) << b;
        cout << "\n";
        for (int i = 0; i <= n; i++) {
            string label = (i == 0) ? "(none)" : items[i - 1].name.substr(0, 12);
            cout << "  " << left << setw(14) << label;
            for (int b = 0; b <= budget; b++) cout << right << setw(4) << dp[i][b];
            cout << "\n";
        }
    } else {
        cout << "\n  (DP table not printed because the budget is large.)\n";
    }

    // Trace back to find the selected items
    vector<int> selected;
    int b = budget;
    for (int i = n; i >= 1; i--) {
        if (dp[i][b] != dp[i - 1][b]) {
            selected.push_back(i - 1);
            b -= items[i - 1].price;
        }
    }
    reverse(selected.begin(), selected.end());

    if (selected.empty()) {
        cout << "\n  No item can be selected within this budget.\n";
    } else {
        int totalPrice = 0, totalPriority = 0;
        cout << "\n  Best items to buy with Rs. " << budget << ":\n";
        printLine();
        for (size_t k = 0; k < selected.size(); k++) {
            const Item& it = items[selected[k]];
            cout << "  " << left << setw(22) << it.name << "Rs. " << setw(8) << it.price
                 << "Priority " << it.priority << "\n";
            totalPrice += it.price;
            totalPriority += it.priority;
        }
        printLine();
        cout << "  Total price    : Rs. " << totalPrice << "\n";
        cout << "  Total priority : " << totalPriority << "\n";
    }
    cout << "  Table entries computed : " << steps << "\n";
    printComplexity("O(N x B)", "O(N x B) for the DP table");
}

void deleteItem(vector<Item>& items) {
    if (items.empty()) {
        cout << "\n  The list is empty.\n";
        return;
    }
    string name;
    cout << "\n  Enter exact item name to delete: ";
    getline(cin, name);
    string target = toLowerCase(name);

    for (size_t i = 0; i < items.size(); i++) {
        if (toLowerCase(items[i].name) == target) {
            cout << "  Deleted: " << items[i].name << "\n";
            items.erase(items.begin() + i);
            printComplexity("O(N x L) to find + O(N) to erase", "O(1) extra");
            return;
        }
    }
    cout << "  Item not found.\n";
}

void showMenu() {
    cout << "\n========== SMART GROCERY SHOPPING LIST OPTIMIZER ==========\n";
    cout << "  1. Add Item\n";
    cout << "  2. Search Item\n";
    cout << "  3. Display List by Priority\n";
    cout << "  4. Optimize for Budget\n";
    cout << "  5. Delete Item\n";
    cout << "  6. Exit\n";
    cout << "============================================================\n";
}

int main() {
    vector<Item> items;
    int choice;

    do {
        showMenu();
        choice = getInt("  Enter your choice (1-6): ", 1, 6);

        switch (choice) {
            case 1: addItem(items); break;
            case 2: searchItem(items); break;
            case 3: displayByPriority(items); break;
            case 4: optimizeForBudget(items); break;
            case 5: deleteItem(items); break;
            case 6: cout << "\n  Thank you! Exiting program.\n"; break;
        }
    } while (choice != 6);

    return 0;
}
