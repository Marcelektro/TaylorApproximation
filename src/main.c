//
// Created by marcelektro on 3/4/25.
//

#include "stdio.h"
#include "math.h"

#define PI 3.14159265358979323846

/**
* Approximate sin(x) using Taylor series
* Formula: sin(x) = x - x^3/3! + x^5/5! - x^7/7! + ...
*
* @param x angle in radians, any value
* @param steps number of terms in the series
* @return sin(x) approximation
*/
double taylorApproxSin(double x, int steps) {
    // normalize x to [0, 2pi]
    x = fmod(x, 2 * PI);

    printf("sin(%f)\n", x);

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
    const int iters = steps * 2 - 1;

    // second and subsequent terms
    for (int i = 3; i <= iters; i += 2) {
        term *= x * x / (i * (i - 1)); // x^i / i!
        sin_x += sign * term; // add or subtract term
        sign *= -1; // flip sign for next term
        // printf("i=%i sin(%f) = %f\n", i, x, sin_x);
    }

    return negativeVal * sin_x;
}


int main() {

    // user input
    // 133*PI/4;
    // 0.15708;
    // 2.984513;
    // PI/4;

    double deg = 235;



    const double radians = deg * PI / 180;
    const int steps = 10000000;


    printf("sin(%f) = %f\n", radians, taylorApproxSin(radians, steps));

    // compare with math.h
    printf("math.h sin(%f) = %f\n", radians, sin(radians));

    return 0;
}
