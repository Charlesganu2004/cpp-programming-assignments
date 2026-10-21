# C++ Programming Assignments

**Timeline:** July 2026

Revised October 2026: assignment 3 Question 3 now draws values from 0 to 199 and uses a neighbour-swap bubble sort that stops after a pass with no swaps. Assignment 4 Question 4 prints amounts with two decimals (`-$600.00`) and calls `withdraw` through base-class pointers. The sample emails in assignment 4 Question 5 now use `example.com`.

Eight standalone C++ programs from two course assignments. Assignment 3 covers classes, struct composition, static members, pass by value and by reference, and a heap-allocated array that is sorted and binary-searched. Assignment 4 covers inheritance, constructor chaining, abstract classes, virtual functions, and polymorphism through base-class pointers. Each question is a single `.cpp` file with its own `main()` and uses only the C++ standard library.

## How it works

### Assignment 3: classes, references, heap arrays

- `assignment-3/Question1`: a `TempScale` class with public Fahrenheit and Celsius fields and two conversion methods, composed into a `Reading` struct (wind speed, humidity, temperature) that a `showReading` function prints by const reference.
- `assignment-3/Question2`: a `QuestionA` class with two instance variables and a static `PI`; `funA` returns the minimum of three ints, `funB` takes its three doubles by reference and returns the average, `funC` is a void method that prints a by-value parameter, and the static `funD` returns the volume of a sphere.
- `assignment-3/Question3`: `aveFun()` fills a 100-element `new[]` array with `rand() % 200` values, bubble sorts it, binary-searches for 135, prints the result, frees the array with `delete[]`, and returns the mean.

### Assignment 4: inheritance and polymorphism

- `assignment-4/Question1`: a `Shape` base class (color defaults to "White") and a `Rectangle` derived from it with three constructors that chain to the matching `Shape` constructor, plus area and perimeter.
- `assignment-4/Question2`: a `Triangle` derived from an abstract `GeometricObject` (pure virtual `getArea` and `getPerimeter`, virtual destructor), with area from Heron's formula. The sides must satisfy the triangle inequality. `Triangle` does not check it, and sides that break it can give a NaN area, for example 1, 2 and 10.
- `assignment-4/Question3`: an `Account` class with id, balance, and an annual interest rate stored as a percent, with `deposit`, `withdraw`, and a yearly-interest calculation.
- `assignment-4/Question4`: `CheckingAccount` (`withdraw` refuses any amount that would leave the balance below a configurable negative limit) and `SavingsAccount` (`withdraw` refuses any amount larger than the balance) derived from an `Account` whose `withdraw` and `printInfo` are virtual. `main` calls both through an `Account*` array, so each account type prints its own denial message for an oversized withdrawal. Amounts print with two decimals and negative balances print as `-$600.00`.
- `assignment-4/Question5`: a `Person` hierarchy of five classes in three levels (`Student`, `Employee`, and `Faculty` and `Staff` under `Employee`), each overriding `printInfo()`, driven through a `const Person*` array. The names, phone numbers, and `example.com` email addresses are made-up sample data.

## Build and run

Requires a C++ compiler with C++11 support. The commands below were run with g++ 13.3.0 on Ubuntu 24.04 under WSL. From the repository root:

```bash
mkdir -p build
for dir in assignment-3/Question* assignment-4/Question*; do
  q=$(basename "$dir")
  g++ -std=c++11 -Wall -Wextra "$dir/$q.cpp" -o "build/$(dirname "$dir")-$q"
done
./build/assignment-4-Question4
```

Replace the last line with any other binary in `build/`, for example `./build/assignment-3-Question1`. None of the programs read input.

`assignment-3/Question3` seeds the random generator from the clock, so its average changes from second to second. The search for 135 succeeds in about 39 percent of runs (1 - (199/200)^100 for 100 values drawn from 0 to 199).

## Sample output

`assignment-4/Question4`:

```
=== Savings Account ===
  [Savings #1001] Denied $1000.00 -- insufficient funds (balance $400.00)
Savings Account #1001 | Balance: $400.00

=== Checking Account ===
  [Checking #2002] Denied $1000.00 -- exceeds overdraft limit of $1000.00
Checking Account #2002 | Balance: -$600.00 | Overdraft limit: $1000.00

=== Through base-class pointers ===
  [Savings #1001] Denied $5000.00 -- insufficient funds (balance $400.00)
Savings Account #1001 | Balance: $400.00
  [Checking #2002] Denied $5000.00 -- exceeds overdraft limit of $1000.00
Checking Account #2002 | Balance: -$600.00 | Overdraft limit: $1000.00
```

## Tests

There is no automated test suite. All 8 programs compile with `g++ -std=c++11 -Wall -Wextra` without warnings, and all 8 run and exit with status 0. The printed values match hand calculations, for example a 4, 5, 6 triangle has perimeter 15 and area 9.92157, and the assignment 4 Question 3 account ends with a balance of 20500 and 922.5 yearly interest.

## Credits

The assignment 4 questions follow exercises from Y. Daniel Liang's *Introduction to
Programming with C++*: Rectangle (Question 1), Triangle derived from GeometricObject
(Question 2), Account (Question 3), Subclasses of Account (Question 4), and the Person,
Student, Employee, Faculty and Staff hierarchy (Question 5). The test values in
assignment 4 Questions 1 and 3 are the textbook's. Assignment 3 Question 1 follows the
Reading and showReading exercises in chapter 11 of Tony Gaddis's *Starting Out with C++
from Control Structures through Objects*. The `GeometricObject` base class was provided
with the assignment, and the sorting routine in `assignment-3/Question3` was adapted from
a sample provided with the assignment.

## Background

C++ programming coursework, 2026. Assignment 3 has three questions and assignment 4 has five.
