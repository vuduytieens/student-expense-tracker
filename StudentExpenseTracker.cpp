#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct Expense {
    int id;
    double amount;
    string category;
    string description;
    string date;
};

string toLower(string text) {
    for (int i = 0; i < text.length(); i++) {
        text[i] = tolower(text[i]);
    }
    return text;
}

void addExpense(vector<Expense>& expenses) {
    Expense expense;

    if (expenses.empty())
        expense.id = 1;
    else
        expense.id = expenses.back().id + 1;

    cout << "\n ADD EXPENSE \n";

    cout << "Amount: ";
    cin >> expense.amount;
    cin.ignore();

    cout << "Category: ";
    getline(cin, expense.category);

    cout << "Description: ";
    getline(cin, expense.description);

    cout << "Date: ";
    getline(cin, expense.date);

    expenses.push_back(expense);

    cout << "\nExpense added successfully!\n";
}

void viewExpenses(vector<Expense>& expenses) {
    cout << "\n EXPENSES \n";

    if (expenses.empty()) {
        cout << "No expenses found.\n";
        return;
    }

    for (int i = 0; i < expenses.size(); i++) {
        cout << "\nID: " << expenses[i].id << '\n';
        cout << "Amount: " << expenses[i].amount << " VND\n";
        cout << "Category: " << expenses[i].category << '\n';
        cout << "Description: " << expenses[i].description << '\n';
        cout << "Date: " << expenses[i].date << '\n';
        cout << "-----------------------------\n";
    }
}

void searchExpense(vector<Expense>& expenses) {
    if (expenses.empty()) {
        cout << "\nNo expenses found.\n";
        return;
    }

    cin.ignore();

    string keyword;

    cout << "\n SEARCH EXPENSE \n";
    cout << "Enter category or description: ";
    getline(cin, keyword);

    keyword = toLower(keyword);

    bool found = 0;

    for (int i = 0; i < expenses.size(); i++) {
        string category = toLower(expenses[i].category);
        string description = toLower(expenses[i].description);

        if (category.find(keyword) != string::npos ||
            description.find(keyword) != string::npos) {

            cout << "\nID: " << expenses[i].id << '\n';
            cout << "Amount: " << expenses[i].amount << " VND\n";
            cout << "Category: " << expenses[i].category << '\n';
            cout << "Description: " << expenses[i].description << '\n';
            cout << "Date: " << expenses[i].date << '\n';
            cout << "-----------------------------\n";

            found = 1;
        }
    }

    if (!found)
        cout << "\nNo matching expense found.\n";
}

double calculateTotal(vector<Expense>& expenses) {
    double total = 0;

    for (int i = 0; i < expenses.size(); i++)
        total += expenses[i].amount;

    return total;
}

void showStatistics(vector<Expense>& expenses) {
    if (expenses.empty()) {
        cout << "\nNo expenses found.\n";
        return;
    }

    map<string, double> statistics;

    for (int i = 0; i < expenses.size(); i++)
        statistics[expenses[i].category] += expenses[i].amount;

    cout << "\n CATEGORY STATISTICS \n";

    for (map<string, double>::iterator it = statistics.begin();
         it != statistics.end();
         it++) {

        cout << it->first << " : "
             << it->second << " VND\n";
    }
}

void saveExpenses(vector<Expense>& expenses) {
    ofstream file("data/expenses.txt");

    for (int i = 0; i < expenses.size(); i++) {
        file << expenses[i].id << '|'
             << expenses[i].amount << '|'
             << expenses[i].category << '|'
             << expenses[i].description << '|'
             << expenses[i].date << '\n';
    }
}

void loadExpenses(vector<Expense>& expenses) {
    ifstream file("data/expenses.txt");

    if (!file)
        return;

    string line;

    while (getline(file, line)) {
        stringstream ss(line);

        Expense expense;
        string value;

        getline(ss, value, '|');
        expense.id = stoi(value);

        getline(ss, value, '|');
        expense.amount = stod(value);

        getline(ss, expense.category, '|');
        getline(ss, expense.description, '|');
        getline(ss, expense.date);

        expenses.push_back(expense);
    }
}

void showMenu() {
    cout << "\n====================================\n";
    cout << "       STUDENT EXPENSE TRACKER\n";
    cout << "====================================\n";

    cout << "1. Add expense\n";
    cout << "2. View expenses\n";
    cout << "3. Search expense\n";
    cout << "4. Total spending\n";
    cout << "5. Category statistics\n";
    cout << "6. Exit\n";

    cout << "\nChoose: ";
}

int main() {
    vector<Expense> expenses;

    loadExpenses(expenses);

    int choice;

    do {
        showMenu();

        cin >> choice;

        switch (choice) {
            case 1:
                addExpense(expenses);
                saveExpenses(expenses);
                break;

            case 2:
                viewExpenses(expenses);
                break;

            case 3:
                searchExpense(expenses);
                break;

            case 4:
                cout << "\nTotal spending: "
                     << calculateTotal(expenses)
                     << " VND\n";
                break;

            case 5:
                showStatistics(expenses);
                break;

            case 6:
                cout << "\nGoodbye!\n";
                break;

            default:
                cout << "\nInvalid choice!\n";
        }

    } 
    while (choice != 6);

    return 0;
}
