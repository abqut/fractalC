#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
//Defines polynomial with float coefficients
typedef struct{
    float *coeff;
    int degree;
} Polynomial;

float fastPow(float b, int p);

//Assigns elements of C as coefficients for P
void assignCoeff(float C[], Polynomial *P, int N);

//Returns p + q
Polynomial add(Polynomial p, Polynomial q);

//Evaluates polynomial P at point x and returnes the result
float eval(Polynomial p, float x);

//Returns x * p
Polynomial smultiply(Polynomial p, float x);

//Returns p * q
Polynomial multiply(Polynomial p, Polynomial q);

//Returns a pointer to an array of monotone cubic polynomials which interpolate the points (x[k], y[k]) for all k < length
Polynomial* monCubIn(float x[], float y[], int length);

float evalSpline(Polynomial *Spline, float *xs, float x, int length);

void freePolyPtr(Polynomial* ptr);

void freeSpline(Polynomial *Spline, int N);
#endif // !POLYNOMIAL_H

