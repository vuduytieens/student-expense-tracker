#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

struct Expense {
    int id;
    double amount;
    std::string category;
    std::string description;
    std::string date;
};

std::string toLower(std::string text) {
    for (char& c : text) {
        c = static_cast<char>(
            std::tolower(static_cast<unsigned char>(c))
        );
    }

    return text;
}

void addExpense(std::vector<Expense>& expenses) {
    Expense expense;

    expense.id = expenses.empty()
        ? 1
        : expenses.back().id + 1;

    std::cout << "\n===== ADD EXPENSE =====\n";

    std::cout << "Amount: ";
    std::cin >> expense.amount;

    std::cin.ignore();

    std::cout << "Category: ";
    std::getline(std::cin, expense.category);

    std::cout << "Description: ";
    std::getline(std::cin, expense.description);

    std::cout << "Date: ";
    std::getline(std::cin, expense.date);

    expenses.push_back(expense);

    std::cout << "\nExpense added successfully!\n";
}

void viewExpenses(const std::vector<Expense>& expenses) {
    std::cout << "\n===== EXPENSES =====\n";

    if (expenses.empty()) {
        std::cout << "No expenses found.\n";
        return;
    }

    for (const Expense& expense : expenses) {
        std::cout << "\nID: " << expense.id << '\n';
        std::cout << "Amount: " << expense.amount << " VND\n";
        std::cout << "Category: " << expense.category << '\n';
        std::cout << "Description: " << expense.description << '\n';
        std::cout << "Date: " << expense.date << '\n';
        std::cout << "-----------------------------\n";
    }
}

void searchExpense(const std::vector<Expense>& expenses) {
    if (expenses.empty()) {
        std::cout << "\nNo expenses found.\n";
        return;
    }

    std::cin.ignore();

    std::string keyword;

    std::cout << "\n===== SEARCH EXPENSE =====\n";
    std::cout << "Enter category or description: ";
    std::getline(std::cin, keyword);

    keyword = toLower(keyword);

    bool found = false;

    for (const Expense& expense : expenses) {
        std::string category = toLower(expense.category);
        std::string description = toLower(expense.description);

        if (category.find(keyword) != std::string::npos ||
            description.find(keyword) != std::string::npos) {

            std::cout << "\nID: " << expense.id << '\n';
            std::cout << "Amount: " << expense.amount << " VND\n";
            std::cout << "Category: " << expense.category << '\n';
            std::cout << "Description: " << expense.description << '\n';
            std::cout << "Date: " << expense.date << '\n';
            std::cout << "-----------------------------\n";

            found = true;
        }
    }

    if (!found) {
        std::cout << "\nNo matching expense found.\n";
    }
}

double calculateTotal(const std::vector<Expense>& expenses) {
    double total = 0;

    for (const Expense& expense : expenses) {
        total += expense.amount;
    }

    return total;
}

void showStatistics(const std::vector<Expense>& expenses) {
    if (expenses.empty()) {
        std::cout << "\nNo expenses found.\n";
        return;
    }

    std::map<std::string, double> statistics;

    for (const Expense& expense : expenses) {
        statistics[expense.category] += expense.amount;
    }

    std::cout << "\n===== CATEGORY STATISTICS =====\n";

    for (const auto& item : statistics) {
        std::cout << item.first
                  << " : "
                  << item.second
                  << " VND\n";
    }
}

void saveExpenses(const std::vector<Expense>& expenses) {
    std::ofstream file("data/expenses.txt");

    if (!file) {
        std::cout << "Cannot open file for saving.\n";
        return;
    }

    for (const Expense& expense : expenses) {
        file << expense.id << '|'
             << expense.amount << '|'
             << expense.category << '|'
             << expense.description << '|'
             << expense.date << '\n';
    }
}

void loadExpenses(std::vector<Expense>& expenses) {
    std::ifstream file("data/expenses.txt");

    if (!file) {
        return;
    }

    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);

        Expense expense;
        std::string value;

        std::getline(ss, value, '|');
        expense.id = std::stoi(value);

        std::getline(ss, value, '|');
        expense.amount = std::stod(value);

        std::getline(ss, expense.category, '|');
        std::getline(ss, expense.description, '|');
        std::getline(ss, expense.date);

        expenses.push_back(expense);
    }
}

void showMenu() {
    std::cout << "\n====================================\n";
    std::cout << "       STUDENT EXPENSE TRACKER\n";
    std::cout << "====================================\n";

    std::cout << "1. Add expense\n";
    std::cout << "2. View expenses\n";
    std::cout << "3. Search expense\n";
    std::cout << "4. Total spending\n";
    std::cout << "5. Category statistics\n";
    std::cout << "6. Exit\n";

    std::cout << "\nChoose: ";
}

int main() {
    std::vector<Expense> expenses;

    loadExpenses(expenses);

    int choice;

    do {
        showMenu();

        std::cin >> choice;

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
                std::cout << "\nTotal spending: "
                          << calculateTotal(expenses)
                          << " VND\n";
                break;

            case 5:
                showStatistics(expenses);
                break;

            case 6:
                saveExpenses(expenses);
                std::cout << "\nGoodbye!\n";
                break;

            default:
                std::cout << "\nInvalid choice!\n";
        }

    } while (choice != 6);

    return 0;
}