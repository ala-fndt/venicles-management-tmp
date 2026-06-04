#include "../../include/model/FinanceManager.hpp"

FinanceManager::FinanceManager() : currentBudget(0.0) {};

void FinanceManager::addIncome(double amount, const std::string &description) {
    if (amount > 0) {
        currentBudget += amount;
        transactionHistory.push_back({amount, description});
    }
}

bool FinanceManager::addExpense(double amount, const std::string &description) {
    if (amount < 0) {
        return false;
    } else if (amount <= currentBudget) {
        currentBudget -= amount;
        transactionHistory.push_back({amount, description});
    }

    return true;
}

double FinanceManager::getBudget() {
    return currentBudget;
}

std::vector<Transaction> FinanceManager::getHistory() {
    return transactionHistory;
}