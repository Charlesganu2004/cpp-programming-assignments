// ===========================================================================
//  Assignment 4 - Question 3
//  ---------------------------------------------------------------------------
//  A simple bank Account model. The annual interest rate is stored as a
//  PERCENT (e.g. 4.5 means 4.5%), so the yearly interest earned on the current
//  balance is  balance * annualInterestRate / 100.
// ===========================================================================

#include <iostream>
using namespace std;

class Account {
private:
    int    id;                  // account number
    double balance;             // current balance
    double annualInterestRate;  // stored as a percent, e.g. 4.5 == 4.5%

public:
    // No-arg constructor: a zeroed-out default account.
    Account() : id(0), balance(0.0), annualInterestRate(0.0) {}

    // Accessors / mutators.
    int    getId() const                 { return id; }
    void   setId(int newId)              { id = newId; }

    double getBalance() const            { return balance; }
    void   setBalance(double b)          { balance = b; }

    double getAnnualInterestRate() const { return annualInterestRate; }
    void   setAnnualInterestRate(double r) { annualInterestRate = r; }

    // Withdraw / deposit. Kept deliberately simple (no overdraft checking
    // here -- that arrives in Question 4's derived classes).
    void withdraw(double amount) { balance -= amount; }
    void deposit(double amount)  { balance += amount; }

    // Convenience: interest earned over one year on the current balance.
    double getYearlyInterest() const {
        return balance * annualInterestRate / 100.0;
    }
};

int main() {
    // Build the account, then configure it via the mutators.
    Account acct;
    acct.setId(1122);
    acct.setBalance(20000);
    acct.setAnnualInterestRate(4.5);   // 4.5%

    acct.withdraw(2500);   // 20000 - 2500 = 17500
    acct.deposit(3000);    // 17500 + 3000 = 20500

    cout << "Account ID       : " << acct.getId() << "\n";
    cout << "Balance          : $" << acct.getBalance() << "\n";
    cout << "Annual Rate      : " << acct.getAnnualInterestRate() << "%\n";
    cout << "Yearly Interest  : $" << acct.getYearlyInterest() << "\n";

    return 0;
}
