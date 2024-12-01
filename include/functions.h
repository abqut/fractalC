#ifndef FUNCTIONS_H
#define FUNCTIONS_H


/*
This file contains functions which can be iterated with the escape time algorithm for some interesting patterns.
As these are examples, this file and its corresponding source file are meant to be customized by the user.
All of these (.c) functions return the number of iterations it took for the point to pass a certain threshhold.
*/


//These are constans used by the functions.
#define JSX -0.4 //julia seed real part
#define JSY -0.59 //julia seed imag part    

#define JSXSIN -0.2 //julia seed real part
#define JSYSIN 1 //julia seed imag part    

int cosine(long double x, long double y, int maxIt);

int exponentialAdd(long double x, long double y, int maxIt);

int exponential(long double x, long double y, int maxIt);

int weirdSinh(long double x, long double y, int maxIt);

int weird(long double x, long double y, int maxIt);

int weirdExp(long double x, long double y, int maxIt);

int juliasine(long double x, long double y, int maxIt);

int julia(long double x, long double y, int maxIt);

int mandelbrot(long double x, long double y, int maxIt);
#endif // !FUNCTIONS_H
