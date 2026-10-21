// ===========================================================================
//  Assignment 3 - Question 2
//  ---------------------------------------------------------------------------
//  A single class, QuestionA, that showcases:
//    * instance variables      (gvar1, gvar2)          - one copy per object
//    * a static (class) variable (PI)                  - one copy shared by all
//    * a value-returning instance method (funA, funB)
//    * a void instance method with a side effect (funC)
//    * a static function (funD)                        - no receiver required
//  main() drives every member: funB is invoked BY REFERENCE, everything else
//  BY VALUE, exactly as the specification requires.
// ===========================================================================

#include <iostream>
using namespace std;

class QuestionA {
public:
    // -- Instance ("global within an object") variables ---------------------
    // Each QuestionA object owns its own gvar1/gvar2.
    int gvar1;
    int gvar2;

    // -- Static / class variable --------------------------------------------
    // Exactly one PI exists no matter how many QuestionA objects are created.
    // Declared here; it must also be *defined* once outside the class (below).
    static double PI;

    // Constructor so the instance variables have deterministic values for
    // funC to compare. (Not strictly demanded by the spec, but a class with
    // uninitialised members is a bug waiting to happen.)
    QuestionA(int a, int b) : gvar1(a), gvar2(b) {}

    // funA: return the minimum of three integers. Written as an explicit
    // running-minimum rather than std::min so the "return statement"
    // requirement is unmistakable.
    int funA(int a, int b, int c) {
        int smallest = a;
        if (b < smallest) smallest = b;
        if (c < smallest) smallest = c;
        return smallest;               // <-- required return statement
    }

    // funB: return the average of three doubles. The parameters are declared
    // as references (double&) so that main can call this function
    // "by reference" as the spec dictates. We never mutate them, so they
    // could be const references; plain references keep the call site literal.
    double funB(double& a, double& b, double& c) {
        return (a + b + c) / 3.0;      // 3.0, not 3, to stay in floating point
    }

    // funC: choose the smaller of the two instance variables, copy it into the
    // parameter psum, and print psum. There is NO return statement. Because
    // psum is passed by value, writing to it here does not affect the caller's
    // argument -- the reassignment lives and dies inside this function.
    void funC(int psum) {
        psum = (gvar1 < gvar2) ? gvar1 : gvar2;
        cout << "funC : smaller of gvar1(" << gvar1 << ") and gvar2("
             << gvar2 << ") assigned to psum = " << psum << endl;
    }

    // funD: volume of a sphere = (4/3) * PI * r^3.  CRITICAL: write 4.0/3.0.
    // As integer math, 4/3 == 1 and the volume would be silently understated.
    // Static because it depends only on the class-level PI and its argument,
    // never on per-object state.
    static double funD(int radius) {
        return 4.0 / 3.0 * PI * radius * radius * radius;
    }
};

// Definition (storage allocation) of the static member. A static data member
// declared inside the class is only a declaration; it must be defined once, in
// exactly one translation unit, or the linker will complain.
double QuestionA::PI = 3.14159;

int main() {
    QuestionA obj(7, 3);   // gvar1 = 7, gvar2 = 3

    // --- funA : pass-by-value -------------------------------------------
    cout << "funA : min(9, 4, 6) = " << obj.funA(9, 4, 6) << endl;

    // --- funB : pass-by-REFERENCE ---------------------------------------
    // Reference parameters cannot bind to literals, which is precisely why we
    // stage the values in named locals and hand THOSE to funB.
    double v1 = 4.0, v2 = 5.0, v3 = 9.0;
    cout << "funB : avg(4, 5, 9) = " << obj.funB(v1, v2, v3) << endl;

    // --- funC : pass-by-value (void, prints internally) -----------------
    obj.funC(0);           // the argument 0 is irrelevant; funC overwrites it

    // --- funD : static, pass-by-value -----------------------------------
    // Called on the class itself (QuestionA::) since it needs no object.
    cout << "funD : volume(radius=2) = " << QuestionA::funD(2) << endl;

    return 0;
}
