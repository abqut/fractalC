#include "imUtil.h"
#include "functions.h"
#include "polynomial.h"
#include "escapeTimeAlg.h"
#include <math.h>
#include <omp.h>
#include <stdlib.h>
#include <stdio.h>
/*
Creates an image based on the behaviour of the iterator function on a rectangle in the complex plane. (more detailed explanation: https://en.wikipedia.org/wiki/Mandelbrot_set#Computer_drawings).
Colors are chosen based on the the splines, one for each base color.
*/
image *compute(fractalRun run) {
    //Color gradient
    int *red = malloc((run.maxIt + 1) * (sizeof(int)));
    int *gre = malloc((run.maxIt + 1) * (sizeof(int)));
    int *blu = malloc((run.maxIt + 1) * (sizeof(int)));

    //Image creation
    image *im = malloc(sizeof(image));
    im->height = run.height;
    im->width = run.width;
    im->pixels = malloc(im->height * im->width * 3);

    //Variables used to display progress
    long tot = run.width * run.height;
    const double fx = (double)run.maxIt;

    //Construct colorgradient array using the splines passed to the function
    for (int du = 0; du <= run.maxIt; du++) {
        float fd = (float)du;
        float val = fd / fx;
        red[du] = (int)(evalSpline(run.R, run.xs, val, run.length));
        gre[du] = (int)(evalSpline(run.G, run.xs, val, run.length));
        blu[du] = (int)(evalSpline(run.B, run.xs, val, run.length));
    }

    long prog, tenth;
    //Step sizes
    const long double x_inc = (run.xmax - run.xmin) / run.width;
    const long double y_inc = (run.ymax - run.ymin) / run.height;
    prog = 0;
    tenth = 1;


#pragma omp parallel for 
    for (int i = 0; i < run.width * run.height; i++) {
        const long double x = i % run.width;
        const long double y = floor(i / run.width);
        const long double u = x * x_inc + run.xmin;
        const long double v = y * y_inc + run.ymin;
        int it = run.it(u, v, run.maxIt);
        //Display progress
        if (prog > tenth * (tot / 100)) {
            int p = (int)((((float)prog) / ((float)tot)) * 100);
            printf("\rIn progress %d", p);
            fflush(stdout);
            tenth++;
        }
        prog++;
        const int j = 3 * i;
        im->pixels[j] = (char)red[it];
        im->pixels[j + 1] = (char)gre[it];
        im->pixels[j + 2] = (char)blu[it];
    }
    free(red);
    free(gre);
    free(blu);
    return im;
}