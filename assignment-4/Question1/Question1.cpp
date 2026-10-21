// ===========================================================================
//  Assignment 4 - Question 1
//  ---------------------------------------------------------------------------
//  Constructor chaining through inheritance: a base Shape and a derived
//  Rectangle. Each Rectangle constructor explicitly forwards to a Shape
//  constructor via its member-initializer list, which is the C++ mechanism
//  for "calling the base constructor" (there is no super() keyword).
// ===========================================================================

#include <iostream>
#include <string>
using namespace std;

// ---------------------------------------------------------------------------
//  Shape  (base class)
// ---------------------------------------------------------------------------
class Shape {
private:
    string color;   // the shape's color

public:
    // No-argument constructor: default color is "White".
    Shape() : color("White") {}

    // Parameterised constructor: caller supplies the color.
    Shape(string c) : color(c) {}

    // Accessor (getter) / mutator (setter) for color.
    string getColor() const      { return color; }
    void   setColor(string c)    { color = c; }

    // Report the shape's color.
    void displayShape() const {
        cout << "Color : " << color << endl;
    }
};

// ---------------------------------------------------------------------------
//  Rectangle  (publicly derived from Shape)
//  "publicly derived" => the Shape public interface stays public in Rectangle,
//  so a Rectangle IS-A Shape.
// ---------------------------------------------------------------------------
class Rectangle : public Shape {
private:
    double width;
    double height;

public:
    // No-arg: chain to Shape() (color -> "White"), sides default to 1.
    Rectangle() : Shape(), width(1.0), height(1.0) {}

    // width/height given: still chain to the Shape NO-ARG constructor as the
    // spec requires (color therefore defaults to "White").
    Rectangle(double w, double h) : Shape(), width(w), height(h) {}

    // color/width/height given: chain to the CORRESPONDING Shape(color)
    // constructor, then store the dimensions.
    Rectangle(string c, double w, double h) : Shape(c), width(w), height(h) {}

    // Accessors / mutators.
    double getWidth() const     { return width; }
    void   setWidth(double w)   { width = w; }
    double getHeight() const    { return height; }
    void   setHeight(double h)  { height = h; }

    // Geometry.
    double getArea() const      { return width * height; }
    double getPerimeter() const { return 2.0 * (width + height); }

    // Report the rectangle's own dimensions.
    void displayRectangle() const {
        cout << "Width : " << width << "  Height : " << height << endl;
    }
};

// Helper for the test program: print everything required for one rectangle.
static void report(const string& label, const Rectangle& r) {
    cout << "--- " << label << " ---\n";
    cout << "Color     : " << r.getColor()     << "\n";   // inherited from Shape
    cout << "Width     : " << r.getWidth()     << "\n";
    cout << "Height    : " << r.getHeight()    << "\n";
    cout << "Area      : " << r.getArea()      << "\n";
    cout << "Perimeter : " << r.getPerimeter() << "\n\n";
}

int main() {
    // 1. No-arg constructor, then set dimensions with the mutators.
    Rectangle r1;
    r1.setWidth(4);
    r1.setHeight(40);

    // 2. width/height constructor.
    Rectangle r2(3.5, 35.9);

    // 3. color/width/height constructor.
    Rectangle r3("Blue", 5, 20);

    report("Rectangle 1 (no-arg + mutators)", r1);
    report("Rectangle 2 (width, height)",     r2);
    report("Rectangle 3 (color, width, height)", r3);

    return 0;
}
