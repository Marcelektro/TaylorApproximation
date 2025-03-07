#include "approximation.h"
#include "math.h"


double taylorApproxSin(double x, const int terms) {
    // normalize x to [0, 2pi]
    x = fmod(x, 2 * PI);

    if (x < 0)
        x += 2 * PI; // normalize negative angles

    int negativeVal; // whether the value will be negative (quadrants 3 and 4)

    // use only first quadrant

    // 4th quadrant (3pi/2 to 2pi)
    if (x >= 3*PI/2) {
        x = 2*PI - x;
        negativeVal = -1;
    }
    // 3rd quadrant (pi to 3pi/2)
    else if (x >= PI) {
        x = x - PI;
        negativeVal = -1;
    }
    // 2nd quadrant (pi/2 to pi)
    else if (x >= PI/2) {
        x = PI - x;
        negativeVal = 1;
    }
    // 1st quadrant (0 to pi/2)
    else {
        negativeVal = 1;
    }

    double sin_x = x;
    double term = x;
    double sign = -1;

    // get number of iterations
    const int iters = terms * 2 - 1;

    // second and subsequent terms
    for (int i = 3; i <= iters; i += 2) {
        term *= x * x / (i * (i - 1)); // x^i / i!
        sin_x += sign * term; // add or subtract term
        sign *= -1; // flip sign for next term
    }

    return negativeVal * sin_x;
}

