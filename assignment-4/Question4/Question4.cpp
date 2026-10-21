// ===========================================================================
//  Assignment 4 - Question 4
//  ---------------------------------------------------------------------------
//  Two derived accounts on top of the Question 3 Account:
//    * CheckingAccount -- withdraw() refuses any amount that would leave the
//                         balance below -overdraftLimit.
//    * SavingsAccount  -- withdraw() refuses any amount larger than the balance.
//  withdraw() is virtual so each subclass enforces its own policy, and a
//  virtual printInfo() is overridden to label the account type.
// ===========================================================================

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// Formats an amount with two decimals and the sign in front of the dollar
// sign: $400.00 or -$600.00. An amount that rounds to zero prints as $0.00,
// never as -$0.00.
string formatMoney(double amount) {
    ostringstream out;
    out << fixed << setprecision(2);
    if (amount > -0.005 && amount < 0.005)
        amount = 0.0;
    if (amount < 0) {
        out << "-";
        amount = -amount;
    }
    out << "$" << amount;
    return out.str();
}

// ---------------------------------------------------------------------------
//  Account (base) -- same design as Q3, with withdraw() and printInfo() made
//  virtual so subclasses can specialise behaviour through a base pointer.
// ---------------------------------------------------------------------------
class Account {
protected:
    int    id;
    double balance;
    double annualInterestRate;

public:
    Account(int i = 0, double b = 0.0, double r = 0.0)
        : id(i), balance(b), annualInterestRate(r) {}
    virtual ~Account() {}

    int    getId() const                 { return id; }
    void   setId(int i)                  { id = i; }
    double getBalance() const            { return balance; }
    void   setBalance(double b)          { balance = b; }
    double getAnnualInterestRate() const { return annualInterestRate; }
    void   setAnnualInterestRate(double r) { annualInterestRate = r; }

    void deposit(double amount) { balance += amount; }

    // Base policy: unrestricted withdrawal. Subclasses override.
    virtual void withdraw(double amount) { balance -= amount; }

    // Polymorphic printout; overridden to name the concrete type.
    virtual void printInfo() const {
        cout << "Account #" << id << " | Balance: " << formatMoney(balance) << endl;
    }
};

// ---------------------------------------------------------------------------
//  CheckingAccount -- overdraft allowed up to 'overdraftLimit'.
// ---------------------------------------------------------------------------
class CheckingAccount : public Account {
private:
    double overdraftLimit;

public:
    CheckingAccount(int i = 0, double b = 0.0, double r = 0.0,
                    double limit = 1000.0)
        : Account(i, b, r), overdraftLimit(limit) {}

    // Refuse any amount that would leave the balance below -overdraftLimit.
    void withdraw(double amount) override {
        if (amount <= balance + overdraftLimit) {
            balance -= amount;
        } else {
            cout << "  [Checking #" << id << "] Denied " << formatMoney(amount)
                 << " -- exceeds overdraft limit of " << formatMoney(overdraftLimit)
                 << endl;
        }
    }

    void printInfo() const override {
        cout << "Checking Account #" << id << " | Balance: " << formatMoney(balance)
             << " | Overdraft limit: " << formatMoney(overdraftLimit) << endl;
    }
};

// ---------------------------------------------------------------------------
//  SavingsAccount -- withdraw() refuses to take the balance below zero.
// ---------------------------------------------------------------------------
class SavingsAccount : public Account {
public:
    SavingsAccount(int i = 0, double b = 0.0, double r = 0.0)
        : Account(i, b, r) {}

    // Reject any withdrawal that would drive the balance negative.
    void withdraw(double amount) override {
        if (amount <= balance) {
            balance -= amount;
        } else {
            cout << "  [Savings #" << id << "] Denied " << formatMoney(amount)
                 << " -- insufficient funds (balance " << formatMoney(balance)
                 << ")" << endl;
        }
    }

    void printInfo() const override {
        cout << "Savings Account #" << id << " | Balance: " << formatMoney(balance)
             << endl;
    }
};

int main() {
    cout << "=== Savings Account ===\n";
    SavingsAccount sav(1001, 500.0, 3.0);
    sav.deposit(200);        // -> 700
    sav.withdraw(300);       // -> 400  (allowed)
    sav.withdraw(1000);      // denied: cannot overdraw
    sav.printInfo();

    cout << "\n=== Checking Account ===\n";
    CheckingAccount chk(2002, 500.0, 2.0, 1000.0);
    chk.deposit(100);        // -> 600
    chk.withdraw(1200);      // -> -600 (allowed: within $1000 overdraft)
    chk.withdraw(1000);      // denied: -600 - 1000 = -1600 < -limit
    chk.printInfo();

    // Demonstrate polymorphism: same call, different behaviour via base ptr.
    // $5000 is more than either account allows, so each withdraw() override
    // prints its own denial message.
    cout << "\n=== Through base-class pointers ===\n";
    Account* accounts[] = { &sav, &chk };
    for (Account* a : accounts) {
        a->withdraw(5000);   // dispatches to the correct override
        a->printInfo();      // dispatches to the correct override
    }

    return 0;
}
