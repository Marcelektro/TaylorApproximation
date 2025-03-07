#ifndef APPROXIMATION_H
#define APPROXIMATION_H


#define PI 3.14159265358979323846

/**
* Approximate sin(x) using Taylor series
* Formula: sin(x) = x - x^3/3! + x^5/5! - x^7/7! + ...
*
* @param x angle in radians, any value
* @param terms number of terms in the series
* @return sin(x) approximation
*/
double taylorApproxSin(double x, int terms);


#endif //APPROXIMATION_H
