// ===========================================================================
//  Assignment 4 - Question 2
//  ---------------------------------------------------------------------------
//  A concrete Triangle deriving from the abstract GeometricObject.
//
//  GeometricObject is the abstract base class provided with the assignment,
//  written out here as a complete class. Its pure virtual functions are
//  declared 'const' so that Triangle's CONST getArea()/getPerimeter() genuinely
//  OVERRIDE them -- a const method cannot override a non-const one, and the
//  mismatch would leave Triangle abstract (and therefore impossible to
//  instantiate).
//
//  Precondition: the three sides must satisfy the triangle inequality. Triangle
//  does not check this, and Heron's formula can give a NaN area for sides
//  that break it, for example 1, 2 and 10.
// ===========================================================================

#include <iostream>
#include <cmath>     // sqrt
using namespace std;

// ---------------------------------------------------------------------------
//  GeometricObject (abstract base) -- provided with the assignment.
// ---------------------------------------------------------------------------
class GeometricObject {
public:
    GeometricObject() {
        cout << "class GeometricObject constructor" << endl;
    }
    virtual double getArea() const = 0;       // pure virtual => abstract class
    virtual double getPerimeter() const = 0;
    virtual ~GeometricObject() {}             // virtual dtor: safe base-ptr delete
};

// ---------------------------------------------------------------------------
//  Triangle : public GeometricObject
// ---------------------------------------------------------------------------
class Triangle : public GeometricObject {
private:
    double side1, side2, side3;

public:
    // No-arg: a default unit triangle (all sides 1.0). The base constructor
    // runs first (implicitly), printing its message.
    Triangle() : side1(1.0), side2(1.0), side3(1.0) {}

    // Parameterised: caller specifies the three sides.
    Triangle(double s1, double s2, double s3)
        : side1(s1), side2(s2), side3(s3) {}

    // Accessors / mutators for all three sides.
    double getSide1() const   { return side1; }
    double getSide2() const   { return side2; }
    double getSide3() const   { return side3; }
    void   setSide1(double s) { side1 = s; }
    void   setSide2(double s) { side2 = s; }
    void   setSide3(double s) { side3 = s; }

    // Area via Heron's formula: with s = perimeter/2,
    //   area = sqrt( s (s-a)(s-b)(s-c) ).
    // 'override' makes the compiler verify this overrides the base.
    double getArea() const override {
        double s = (side1 + side2 + side3) / 2.0;
        return sqrt(s * (s - side1) * (s - side2) * (s - side3));
    }

    double getPerimeter() const override {
        return side1 + side2 + side3;
    }
};

int main() {
    // First object: no-arg constructor (prints the base-constructor message).
    Triangle t1;
    // Second object: parameterised constructor (prints it again).
    Triangle t2(0, 0, 0);   // values overwritten below via mutators

    // Assign the required sides through the mutator functions.
    t1.setSide1(4); t1.setSide2(5); t1.setSide3(6);
    t2.setSide1(7); t2.setSide2(8); t2.setSide3(9);

    cout << "\nTriangle 1 (sides 4, 5, 6):\n";
    cout << "  Perimeter = " << t1.getPerimeter() << "\n";
    cout << "  Area      = " << t1.getArea()      << "\n";

    cout << "Triangle 2 (sides 7, 8, 9):\n";
    cout << "  Perimeter = " << t2.getPerimeter() << "\n";
    cout << "  Area      = " << t2.getArea()      << "\n";

    return 0;
}
