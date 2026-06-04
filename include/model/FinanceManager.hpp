#include <vector>
#include <string>

struct Transaction {
    double amount;
    std::string description;
};

class FinanceManager {
    private:
        double currentBudget;
        std::vector<Transaction> transactionHistory;

    public:
        FinanceManager();
        ~FinanceManager() = default;

        void addIncome(double amount, const std::string& description);
        bool addExpense(double amount, const std::string& description);
        double getBudget();
        std::vector<Transaction> getHistory();

};