#include <math.h>
#include <complex.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "functions.h"

int cosine(long double x, long double y, int maxIt){
    /*
    Returns number of iterations it takes to diverge (if divergence occures at all).
    */
    long double x0, y0, xn, yn, ex, nex, cx, sx;
    x0 = 0.0;
    y0 = 0.0;
    int k;
    int i = 1;
    for (k = 1; k < maxIt && (x0 * x0 + y0 * y0) < 1024; k++) {
        ex = exp(y0);
        nex = 1/ex;
        sx = sin(x0);
        cx = cos(x0);
        xn = 0.5 * ((cx * (ex + nex)) * x - (sx * (nex - ex)) * y);
        yn = 0.5 * ((sx * (nex - ex)) * x + (cx * (ex + nex)) * y);
        x0 = xn;
        y0 = yn;
        i++;
    }
    return i;
}

int exponentialAdd(long double x, long double y, int maxIt){
        /*
    Returns number of iterations it takes to diverge (if divergence occures at all).
    */
    long double x0, y0, xn, yn, ex;
    x0 = 0.0;
    y0 = 0.0;
    int k;
    int i = 1;
    for (k = 1; k < maxIt && (x0) < 8 ; k++) {
        ex = exp(x0);
        xn = ex * cos(y0) + x;
        yn = ex * sin(y0) + y;
        x0 = xn;
        y0 = yn;
        i++;
    }
    return i;
}

int exponential(long double x, long double y, int maxIt){
        /*
    Returns number of iterations it takes to diverge (if divergence occures at all).
    */
    long double x0, y0, xn, yn, ex, nex, x2y2, arg;
    x0 = 0.0;
    y0 = 0.0;
    x2y2 = x*x + y*y;
    arg = atan2(y , x);
    int k;
    int i = 1;
    for (k = 1; k < maxIt && (x0 * x0 + y0 * y0) < 1024 ; k++) {
        ex = pow(x2y2, x0 * 0.5) * exp(-y0 * arg);
        nex = x0 * arg + 0.5 * y0 * log(x2y2);
        xn = ex * cos(nex);
        yn = ex * sin(nex);
        x0 = xn;
        y0 = yn;
        i++;
    }
    return i;
}

int weirdSinh(long double x, long double y, int maxIt){
        /*
    Returns number of iterations it takes to diverge (if divergence occures at all).
    */
    long double complex zn, z0, c, root;
    c = x + y * I;
    root = 1.0 / c;
    z0 = 0.9 - 0.05 * I;
    int k;
    int i = 1;
    for (k = 1; k < maxIt && cabs(z0) < 100 ; k++) {
        zn = csinh(z0) + root;
        z0 = zn;
        i++;
    }
    return i;
}

int weird(long double x, long double y, int maxIt){
        /*
    Returns number of iterations it takes to diverge (if divergence occures at all).
    */
    long double complex zn, z0, c, root;
    c = x + y * I;
    root = clog(c * c * c * c * c * c * c * c * c);
    z0 = 1.0 + 1.0 * I;
    int k;
    int i = 1;
    for (k = 1; k < maxIt && cabs(z0) < 100 ; k++) {
        zn = cexp((z0 * z0 + 3.0000 * z0) / root);
        z0 = zn;
        i++;
    }
    return i;
}

int weirdExp(long double x, long double y, int maxIt){
        /*
    Returns number of iterations it takes to diverge (if divergence occures at all).
    */
    long double complex zn, z0, c, root;
    c = x + y * I;
    root = c * c * c;
    z0 = 0.0 + 0.0 * I;
    int k;
    int i = 1;
    for (k = 1; k < maxIt && cabs(z0) < 100 ; k++) {
        zn = cexp((z0 * z0 - 1.00001 * z0) / root);
        z0 = zn;
        i++;
    }
    return i;
}

int juliasine(long double x, long double y, int maxIt){
    /*
    Returns number of iterations it takes to diverge (if divergence occures at all).
    */
    long double x0, y0, xn, yn, ex, nex, cx, sx;
    x0 = x;
    y0 = y;
    int k;
    int i = 1;
    for (k = 1; k < maxIt && (y0 * y0) < 50 * 50; k++) {
        ex = exp(y0);
        nex = 1/ex;
        sx = sin(x0);
        cx = cos(x0);
        xn = 0.5 * ((sx * (ex + nex)) * JSXSIN + (cx * (nex - ex)) * JSYSIN);
        yn = 0.5 * ((sx * (ex + nex)) * JSYSIN - (cx * (nex - ex)) * JSXSIN);
        x0 = xn;
        y0 = yn;
        i++;
    }
    return i;
}

int julia(long double x, long double y, int maxIt){
    long double x0, y0, xn, yn;
    x0 = x;
    y0 = y;
    int k;
    int i = 1;
    for (k = 1; k < maxIt && (x0 * x0 + y0 * y0) < 4.0; k++) {
        xn = JSX + (x0 * x0) - (y0 * y0);
        yn = JSY + 2 * y0 * x0;
        x0 = xn;
        y0 = yn;
        i++;
    }
    return i;
}

float mandelbrotLog(long double x, long double y, int maxIt) {
    /*
    Returns number of iterations it takes to diverge (if divergence occures at all).
    */
    long double x0, y0, xn, yn;
    x0 = 0.0;
    y0 = 0.0;
    int k;
    float i = 1;
    for (k = 1; k < maxIt && (x0 * x0 + y0 * y0) < (1 << 16); k++) {
        xn = (x0 * x0 - y0 * y0) + x;
        yn = (2 * x0 * y0) + y;
        x0 = xn;
        y0 = yn;
        i++;
    }

    if(i < maxIt){
        float logzn = logf(x0 * x0 + y0 * y0) / 2;
        float nu = logf(logzn / logf(2)) / logf(2);
        i -= nu;
    }
    return i;
}

int mandelbrot(long double x, long double y, int maxIt) {
    /*
    Returns number of iterations it takes to diverge (if divergence occures at all).
    */
    long double q = (x - 0.25) * (x - 0.25) + y * y;
    long double p = (x + 1) * (x + 1) + y * y;
    if(p <= 0.0625 || (q * (q + x - 0.25)) <= 0.25 * y * y){
        return maxIt;
    }   
    long double x0, y0, xn, yn;
    x0 = 0.0;
    y0 = 0.0;
    int k;
    int i = 1;
    for (k = 1; k < maxIt && (x0 * x0 + y0 * y0) < 4.0; k++) {
        xn = (x0 * x0 - y0 * y0) + x;
        yn = (2 * x0 * y0) + y;
        x0 = xn;
        y0 = yn;
        i++;
    }
    return i;
}