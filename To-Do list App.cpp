#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdlib>

using namespace std;

class Expense {
public:
    double amount;
    string category;
    string date;

    Expense(double amt, string cat, string dt) {
        amount = amt;
        category = cat;
        date = dt;
    }
};

vector<Expense> expenses;

// Save expenses to file
void saveExpenses() {
    ofstream file("expenses.txt");

    for (size_t i = 0; i < expenses.size(); i++) {
        file << expenses[i].amount << "|"
             << expenses[i].category << "|"
             << expenses[i].date << endl;
    }

    file.close();
}

// Load expenses from file
void loadExpenses() {
    ifstream file("expenses.txt");

    if (!file.is_open()) {
        return;
    }

    string line;

    while (getline(file, line)) {
        stringstream ss(line);

        string amountStr;
        string category;
        string date;

        getline(ss, amountStr, '|');
        getline(ss, category, '|');
        getline(ss, date);

        try {
            double amount = atof(amountStr.c_str()); // FIXED: was stod(amountStr)
            if (amount <= 0) continue;
            expenses.push_back(Expense(amount, category, date));
        }
        catch (...) {
            continue;
        }
    }

    file.close();
}

// Add expense
void addExpense() {
    double amount;
    string category;
    string date;

    cout << "\nEnter expense amount: ";

    if (!(cin >> amount) || amount <= 0) {
        cout << "Invalid amount!" << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }

    cin.ignore(10000, '\n');

    cout << "Enter category (Food/Travel/Shopping/etc): ";
    getline(cin, category);

    cout << "Enter date (DD-MM-YYYY): ";
    getline(cin, date);

    expenses.push_back(Expense(amount, category, date));

    saveExpenses();

    cout << "Expense added successfully!" << endl;
}

// View expenses
void viewExpenses() {
    cout << "\n=========== EXPENSE HISTORY ===========" << endl;

    if (expenses.empty()) {
        cout << "No expenses found." << endl;
        return;
    }

    cout << left
         << setw(5) << "No"
         << setw(15) << "Amount"
         << setw(20) << "Category"
         << setw(15) << "Date" << endl;

    cout << "--------------------------------------------------" << endl;

    for (size_t i = 0; i < expenses.size(); i++) {
        cout << left
             << setw(5) << i + 1
             << setw(15) << fixed << setprecision(2) << expenses[i].amount
             << setw(20) << expenses[i].category
             << setw(15) << expenses[i].date << endl;
    }
}

// Total spending
void totalSpending() {
    double total = 0;

    for (size_t i = 0; i < expenses.size(); i++) {
        total += expenses[i].amount;
    }

    cout << "\nTotal Spending: Rs. "
         << fixed << setprecision(2)
         << total << endl;
}

// Delete expense
void deleteExpense() {
    viewExpenses();

    if (expenses.empty())
        return;

    int index;

    cout << "\nEnter expense number to delete: ";
    cin >> index;

    if (index < 1 || index > static_cast<int>(expenses.size())) {
        cout << "Invalid expense number!" << endl;
        return;
    }

    expenses.erase(expenses.begin() + (index - 1));

    saveExpenses();

    cout << "Expense deleted successfully!" << endl;
}

// Category summary
void categorySummary() {
    double food = 0;
    double travel = 0;
    double shopping = 0;
    double other = 0;

    for (size_t i = 0; i < expenses.size(); i++) {

        string category = expenses[i].category;

        if (category == "Food" || category == "food") {
            food += expenses[i].amount;
        }
        else if (category == "Travel" || category == "travel") {
            travel += expenses[i].amount;
        }
        else if (category == "Shopping" || category == "shopping") {
            shopping += expenses[i].amount;
        }
        else {
            other += expenses[i].amount;
        }
    }

    cout << "\n=========== CATEGORY SUMMARY ===========" << endl;
    cout << "Food: Rs. " << food << endl;
    cout << "Travel: Rs. " << travel << endl;
    cout << "Shopping: Rs. " << shopping << endl;
    cout << "Other: Rs. " << other << endl;
}

// Menu
void showMenu() {
    cout << "\n=========== EXPENSE TRACKER ===========" << endl;
    cout << "1. Add Expense" << endl;
    cout << "2. View Expenses" << endl;
    cout << "3. Total Spending" << endl;
    cout << "4. Delete Expense" << endl;
    cout << "5. Category Summary" << endl;
    cout << "6. Exit" << endl;
    cout << "Choose an option: ";
}

int main() {
    loadExpenses();

    int choice;

    do {
        showMenu();

        if (!(cin >> choice)) {
            cout << "Invalid input!" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
        case 1:
            addExpense();
            break;

        case 2:
            viewExpenses();
            break;

        case 3:
            totalSpending();
            break;

        case 4:
            deleteExpense();
            break;

        case 5:
            categorySummary();
            break;

        case 6:
            cout << "Exiting application..." << endl;
            break;

        default:
            cout << "Invalid option! Please try again." << endl;
        }

    } while (choice != 6);

    return 0;
}