// ===========================================================================
//  Assignment 3 - Question 3
//  ---------------------------------------------------------------------------
//  aveFun() builds a 100-element HEAP array of random integers, sorts it,
//  binary-searches for the value 135, reports the outcome, and returns the
//  arithmetic mean of the array. main() calls aveFun() and prints that mean.
//
//  Key detail: binary search is only correct on a SORTED range, so the array
//  is sorted before it is searched.
// ===========================================================================

#include <iostream>
#include <cstdlib>   // rand(), srand()
#include <ctime>     // time() for seeding the generator
using namespace std;

// -- Forward declarations (definitions follow main-supporting order) ---------
double aveFun();
void   bubbleSort(int a[], int size);
int    binarySearch(int a[], int size, int key);

// ---------------------------------------------------------------------------
//  aveFun
//  No parameters; returns the average of the array it creates as a double.
// ---------------------------------------------------------------------------
double aveFun() {
    const int N = 100;

    // Allocate the array on the HEAP (free store), NOT the stack, as required.
    int* data = new int[N];

    // Populate every element with a pseudo-random value in [0, 199]. The small
    // range lets the search below find 135 in a good share of runs; with the
    // full [0, RAND_MAX] range it would almost never be present.
    for (int i = 0; i < N; ++i)
        data[i] = rand() % 200;

    // Binary search presupposes sorted input, so sort first. The choice of sort
    // algorithm does not matter here, so a straightforward bubble sort is used.
    bubbleSort(data, N);

    // Search the now-sorted array for the value 135.
    int index = binarySearch(data, N, 135);
    if (index != -1)
        cout << "Binary search : value 135 found at index " << index << endl;
    else
        cout << "Binary search : nothing" << endl;   // 135 not present

    // Compute the arithmetic mean. Accumulate in a long long so the running
    // total cannot overflow whatever the width of long, then divide as double
    // to retain the fractional part.
    long long sum = 0;
    for (int i = 0; i < N; ++i)
        sum += data[i];
    double average = static_cast<double>(sum) / N;

    // Release the heap block: every 'new[]' needs a matching 'delete[]',
    // otherwise this function leaks 400 bytes on each call.
    delete[] data;

    return average;
}

// ---------------------------------------------------------------------------
//  bubbleSort - ascending, in place. Each pass swaps neighbouring elements that
//  are out of order, so the largest remaining value settles at the end of the
//  unsorted range; a pass with no swaps means the array is sorted and the loop
//  stops. O(n^2), perfectly adequate for N = 100.
//  (Adapted from the sample provided with the assignment.)
// ---------------------------------------------------------------------------
void bubbleSort(int a[], int size) {
    for (int pass = 0; pass < size - 1; ++pass) {
        bool swapped = false;
        for (int j = 0; j < size - 1 - pass; ++j) {
            if (a[j] > a[j + 1]) {      // neighbours out of order: swap them
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped)
            break;                      // no swaps in a full pass: already sorted
    }
}

// ---------------------------------------------------------------------------
//  binarySearch - classic iterative variant on an ascending array.
//  Returns the index of 'key' if found, or -1 if it is absent.
// ---------------------------------------------------------------------------
int binarySearch(int a[], int size, int key) {
    int low = 0, high = size - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;   // (low+high)/2 could overflow; this can't
        if (a[mid] == key)
            return mid;                     // hit
        else if (a[mid] < key)
            low = mid + 1;                  // discard the left half
        else
            high = mid - 1;                 // discard the right half
    }
    return -1;                              // miss
}

int main() {
    // Seed the PRNG from the clock so runs in different seconds differ. For reproducible
    // output (e.g. while grading), replace this with a fixed seed such as
    // srand(1); or comment the line out entirely.
    srand(static_cast<unsigned>(time(nullptr)));

    double average = aveFun();
    cout << "Average of the 100 elements = " << average << endl;

    return 0;
}
