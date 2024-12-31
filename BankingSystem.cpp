
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class Account {
private:
    int accountNumber;
    std::string accountHolder;
    double balance;
    std::vector<std::string> transactionHistory;

    void logTransaction(const std::string& transaction) {
        transactionHistory.push_back(transaction);
        std::ofstream file("transactions_" + std::to_string(accountNumber) + ".txt", std::ios::app);
        if (file) {
            file << transaction << std::endl;
        }
    }

public:
    Account(int accNum, const std::string& accHolder, double initialBalance) 
        : accountNumber(accNum), accountHolder(accHolder), balance(initialBalance) {
        logTransaction("Account created with balance: " + std::to_string(initialBalance));
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            logTransaction("Deposited: " + std::to_string(amount) + ", New Balance: " + std::to_string(balance));
        } else {
            std::cout << "Invalid deposit amount." << std::endl;
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            logTransaction("Withdrew: " + std::to_string(amount) + ", New Balance: " + std::to_string(balance));
        } else {
            std::cout << "Invalid or insufficient funds for withdrawal." << std::endl;
        }
    }

    void displayDetails() const {
        std::cout << "Account Number: " << accountNumber << std::endl;
        std::cout << "Account Holder: " << accountHolder << std::endl;
        std::cout << "Balance: " << balance << std::endl;
    }

    void displayTransactionHistory() const {
        std::cout << "Transaction History for Account " << accountNumber << ":" << std::endl;
        for (const auto& transaction : transactionHistory) {
            std::cout << transaction << std::endl;
        }
    }

    void loadTransactionHistory() {
        std::ifstream file("transactions_" + std::to_string(accountNumber) + ".txt");
        if (file) {
            std::string transaction;
            while (getline(file, transaction)) {
                transactionHistory.push_back(transaction);
            }
        }
    }
};

class BankingSystem {
private:
    std::vector<Account> accounts;

public:
    void createAccount(int accNum, const std::string& accHolder, double initialBalance) {
        accounts.emplace_back(accNum, accHolder, initialBalance);
        std::cout << "Account created successfully!" << std::endl;
    }

    Account* findAccount(int accNum) {
        for (auto& account : accounts) {
            if (account.getAccountNumber() == accNum) {
                return &account;
            }
        }
        std::cout << "Account not found." << std::endl;
        return nullptr;
    }
};

int main() {
    BankingSystem bank;
    int choice, accNum;
    double amount;
    std::string accHolder;

    while (true) {
        std::cout << "\nBanking System Menu:" << std::endl;
        std::cout << "1. Create Account" << std::endl;
        std::cout << "2. Deposit" << std::endl;
        std::cout << "3. Withdraw" << std::endl;
        std::cout << "4. Display Account Details" << std::endl;
        std::cout << "5. Display Transaction History" << std::endl;
        std::cout << "6. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter Account Number: ";
                std::cin >> accNum;
                std::cout << "Enter Account Holder Name: ";
                std::cin.ignore();
                std::getline(std::cin, accHolder);
                std::cout << "Enter Initial Balance: ";
                std::cin >> amount;
                bank.createAccount(accNum, accHolder, amount);
                break;

            case 2: {
                std::cout << "Enter Account Number: ";
                std::cin >> accNum;
                Account* account = bank.findAccount(accNum);
                if (account) {
                    std::cout << "Enter Deposit Amount: ";
                    std::cin >> amount;
                    account->deposit(amount);
                }
                break;
            }

            case 3: {
                std::cout << "Enter Account Number: ";
                std::cin >> accNum;
                Account* account = bank.findAccount(accNum);
                if (account) {
                    std::cout << "Enter Withdrawal Amount: ";
                    std::cin >> amount;
                    account->withdraw(amount);
                }
                break;
            }

            case 4: {
                std::cout << "Enter Account Number: ";
                std::cin >> accNum;
                Account* account = bank.findAccount(accNum);
                if (account) {
                    account->displayDetails();
                }
                break;
            }

            case 5: {
                std::cout << "Enter Account Number: ";
                std::cin >> accNum;
                Account* account = bank.findAccount(accNum);
                if (account) {
                    account->displayTransactionHistory();
                }
                break;
            }

            case 6:
                std::cout << "Exiting Banking System. Goodbye!" << std::endl;
                return 0;

            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
}
