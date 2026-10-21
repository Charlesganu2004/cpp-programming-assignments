// ===========================================================================
//  Assignment 3 - Question 1
//  ---------------------------------------------------------------------------
//  Demonstrates a public "plain-old-data + methods" class (TempScale), a
//  struct that composes it (Reading), and a free function that reports the
//  aggregate. Temperature conversion uses the standard linear formulas.
// ===========================================================================

#include <iostream>
using namespace std;

// ---------------------------------------------------------------------------
//  TempScale
//  Encapsulates a paired Fahrenheit/Celsius temperature and supplies the two
//  canonical conversions. The assignment mandates that *every* member be
//  public, so this behaves like a C struct that happens to carry
//  its own conversion routines.
// ---------------------------------------------------------------------------
class TempScale {
public:
    double fahrenheit;   // stored temperature, degrees Fahrenheit
    double celsius;      // stored temperature, degrees Celsius

    // Two-argument constructor: seed both data members directly from the
    // caller's arguments via an initializer list (cheaper than assigning in
    // the body, and required for const/reference members in general).
    TempScale(double f, double c) : fahrenheit(f), celsius(c) {}

    // Convert a Fahrenheit value to Celsius:  C = (F - 32) * 5/9.
    // The parameter is deliberately independent of the stored 'fahrenheit'
    // field so a single object can convert arbitrary values on demand.
    // NOTE the literals are written 32.0 / 5.0 / 9.0 to force floating-point
    // arithmetic; 5/9 in integer math would collapse to 0.
    double fahrenheitToCelsius(double f) {
        return (f - 32.0) * 5.0 / 9.0;
    }

    // Convert a Celsius value to Fahrenheit:  F = C * 9/5 + 32.
    double celsiusToFahrenheit(double c) {
        return c * 9.0 / 5.0 + 32.0;
    }
};

// ---------------------------------------------------------------------------
//  Reading
//  A weather snapshot. It *composes* a TempScale by value (has-a), which is
//  the right relationship here: a reading contains a temperature, it is not a
//  kind of temperature.
// ---------------------------------------------------------------------------
struct Reading {
    int windSpeed;         // wind speed, mph
    double humidity;       // relative humidity, percent
    TempScale temperature; // the paired F/C temperature for this reading
};

// ---------------------------------------------------------------------------
//  showReading
//  Prints every field of a Reading. The parameter is taken by const-reference
//  rather than by value: it is still logically "one parameter of type
//  Reading", but we avoid copying the struct (and its embedded object) and the
//  'const' documents/enforces that the function is read-only.
// ---------------------------------------------------------------------------
void showReading(const Reading& r) {
    cout << "Wind speed             : " << r.windSpeed              << " mph\n";
    cout << "Humidity               : " << r.humidity              << " %\n";
    cout << "Fahrenheit temperature : " << r.temperature.fahrenheit << " F\n";
    cout << "Celsius temperature    : " << r.temperature.celsius    << " C\n";
}

int main() {
    // 1-2. Create 'today' and store the required values. Because TempScale has
    //       no default constructor, Reading is aggregate-initialised: the brace
    //       list feeds windSpeed, then humidity, then invokes TempScale(f, c),
    //       strictly in member-declaration order.
    Reading today = { 37, 32.0, TempScale(32.0, 0.0) };

    // 3. Display the stored snapshot.
    cout << "--- Today's Reading ---\n";
    showReading(today);

    // 4. A separate TempScale object used purely to exercise the converters
    //    (its stored 68/20 pair happens to match the values we convert).
    TempScale ts(68.0, 20.0);

    // 5. Run both conversions.
    double asCelsius    = ts.fahrenheitToCelsius(68.0);
    double asFahrenheit = ts.celsiusToFahrenheit(20.0);

    // 6. Report the results returned by the member functions.
    cout << "\n--- TempScale Conversions ---\n";
    cout << "68 F  ->  " << asCelsius    << " C\n";
    cout << "20 C  ->  " << asFahrenheit << " F\n";

    return 0;
}
