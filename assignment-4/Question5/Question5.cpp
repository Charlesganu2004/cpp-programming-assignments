// ===========================================================================
//  Assignment 4 - Question 5
//  ---------------------------------------------------------------------------
//  A hierarchy of five classes in three levels exercising virtual dispatch:
//
//        Person
//          |
//    +-----+------+
//  Student     Employee
//                 |
//            +----+----+
//         Faculty    Staff
//
//  Each class overrides printInfo() to print its own class name followed by
//  every field it inherits plus its own. Data members are 'protected' so a
//  derived class can read the ancestor state directly when printing.
// ===========================================================================

#include <iostream>
#include <string>
using namespace std;

// ---------------------------------------------------------------------------
//  Person (root)
// ---------------------------------------------------------------------------
class Person {
protected:
    string name, address, phone, email;

public:
    Person(string n = "", string a = "", string p = "", string e = "")
        : name(n), address(a), phone(p), email(e) {}
    virtual ~Person() {}

    virtual void printInfo() const {
        cout << "Class: Person\n"
             << "  Name    : " << name    << "\n"
             << "  Address : " << address << "\n"
             << "  Phone   : " << phone   << "\n"
             << "  Email   : " << email   << "\n";
    }
};

// ---------------------------------------------------------------------------
//  Student : Person   (adds class status)
// ---------------------------------------------------------------------------
class Student : public Person {
protected:
    string classStatus;   // freshman / sophomore / junior / senior

public:
    Student(string n, string a, string p, string e, string status)
        : Person(n, a, p, e), classStatus(status) {}

    void printInfo() const override {
        cout << "Class: Student\n"
             << "  Name    : " << name        << "\n"
             << "  Address : " << address     << "\n"
             << "  Phone   : " << phone       << "\n"
             << "  Email   : " << email       << "\n"
             << "  Status  : " << classStatus << "\n";
    }
};

// ---------------------------------------------------------------------------
//  Employee : Person   (adds office, salary, dateHired)
// ---------------------------------------------------------------------------
class Employee : public Person {
protected:
    string office;
    double salary;
    string dateHired;

public:
    Employee(string n, string a, string p, string e,
             string off, double sal, string hired)
        : Person(n, a, p, e), office(off), salary(sal), dateHired(hired) {}

    void printInfo() const override {
        cout << "Class: Employee\n"
             << "  Name      : " << name      << "\n"
             << "  Address   : " << address   << "\n"
             << "  Phone     : " << phone     << "\n"
             << "  Email     : " << email     << "\n"
             << "  Office    : " << office    << "\n"
             << "  Salary    : " << salary    << "\n"
             << "  DateHired : " << dateHired << "\n";
    }
};

// ---------------------------------------------------------------------------
//  Faculty : Employee   (adds office hours and rank)
// ---------------------------------------------------------------------------
class Faculty : public Employee {
private:
    string officeHours, rank;

public:
    Faculty(string n, string a, string p, string e,
            string off, double sal, string hired,
            string hours, string rnk)
        : Employee(n, a, p, e, off, sal, hired),
          officeHours(hours), rank(rnk) {}

    void printInfo() const override {
        cout << "Class: Faculty\n"
             << "  Name        : " << name        << "\n"
             << "  Address     : " << address     << "\n"
             << "  Phone       : " << phone       << "\n"
             << "  Email       : " << email       << "\n"
             << "  Office      : " << office      << "\n"
             << "  Salary      : " << salary      << "\n"
             << "  DateHired   : " << dateHired   << "\n"
             << "  OfficeHours : " << officeHours << "\n"
             << "  Rank        : " << rank        << "\n";
    }
};

// ---------------------------------------------------------------------------
//  Staff : Employee   (adds title)
// ---------------------------------------------------------------------------
class Staff : public Employee {
private:
    string title;

public:
    Staff(string n, string a, string p, string e,
          string off, double sal, string hired, string ttl)
        : Employee(n, a, p, e, off, sal, hired), title(ttl) {}

    void printInfo() const override {
        cout << "Class: Staff\n"
             << "  Name      : " << name      << "\n"
             << "  Address   : " << address   << "\n"
             << "  Phone     : " << phone     << "\n"
             << "  Email     : " << email     << "\n"
             << "  Office    : " << office    << "\n"
             << "  Salary    : " << salary    << "\n"
             << "  DateHired : " << dateHired << "\n"
             << "  Title     : " << title     << "\n";
    }
};

int main() {
    // One object of each type with representative data.
    Person   person  ("Alice",  "1 Oak St",   "555-0100", "alice@example.com");
    Student  student ("Bob",    "2 Elm St",   "555-0101", "bob@example.com", "Junior");
    Employee employee("Carol",  "3 Pine St",  "555-0102", "carol@example.com",
                      "Rm 101", 65000, "2021-03-15");
    Faculty  faculty ("Dr. Dan","4 Maple St", "555-0103", "dan@example.com",
                      "Rm 250", 95000, "2015-08-01", "MWF 10-12", "Professor");
    Staff    staff   ("Eve",    "5 Birch St", "555-0104", "eve@example.com",
                      "Rm 12",  48000, "2019-06-10", "Administrative Assistant");

    // Store base pointers and dispatch polymorphically: each call resolves to
    // the most-derived override at run time.
    const Person* people[] = { &person, &student, &employee, &faculty, &staff };
    for (const Person* p : people) {
        p->printInfo();
        cout << "----------------------------------------\n";
    }

    return 0;
}
