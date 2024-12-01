#ifndef ESCAPETIMEALG_H
#define ESCAPETIMEALG_H
#include "imUtil.h"
#include "polynomial.h"

typedef int (*iterator)(long double, long double, int);

//Parameters which define the image
typedef struct {
    iterator it;
    int width;
    int height;
    double xmin;
    double xmax;
    double ymin;
    double ymax;
    int maxIt;
    Polynomial *R;
    Polynomial *G;
    Polynomial *B;
    float *xs;
    int length;
} fractalRun;

image *compute(fractalRun run);
#endif // !ESCAPETIMEALG_H

