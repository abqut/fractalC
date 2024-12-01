#include <time.h>

#include "functions.h"
#include "polynomial.h"
#include "escapeTimeAlg.h"
#include "imUtil.h"
#include <stdio.h>
#include <stdlib.h>


char *generateFractalPathJulia(fractalRun run){
    char* outPath = malloc(200 * sizeof(char));
    double x = (run.xmax + run.xmin) * 0.5;
    double y = (run.ymax + run.ymin) * 0.5;
    snprintf(outPath, 200, "./julia%.2f_%.2f_%dx%d_%.2f_%.2f_%d",x,y, run.width, run.height, JSX, JSY, run.maxIt);
    return outPath;
}

char *generateFractalPathMandelbrot(fractalRun run){
    char* outPath = malloc(200 * sizeof(char));
    double x = (run.xmax + run.xmin) * 0.5;
    double y = (run.ymax + run.ymin) * 0.5;
    snprintf(outPath, 200, "./mandel%.2f_%.2f_%dx%d_%d",x,y, run.width, run.height, run.maxIt);
    return outPath;
}

int main() {
    //Example usage of the program which generates a PNG of a julia set.
    const int width = 10000;
    const int height = 10000;

    float yr[10] = {0, 112, 160, 206, 239, 255, 255, 255, 255, 255};
    float ygg[10] = {0, 0, 0, 0, 52, 97, 140, 179, 255, 255};
    float yb[10] = {0, 136, 72, 0, 0, 0, 0, 0, 0, 255};
    float x[10] = {0, 0.1111, 0.2222, 0.3333, 0.4444, 0.5555, 0.6666, 0.7777, 0.8888, 1.0001};

    Polynomial *R = monCubIn(x, yr, 10);
    Polynomial *G = monCubIn(x, ygg, 10);
    Polynomial *B = monCubIn(x, yb, 10);

    char* path;

    fractalRun runPNG = {
        .width = width,
        .height = height,
        .R = R,
        .B = B,
        .G = G,
        .it = mandelbrot,
        .maxIt = 800,
        .xmin = -1.5,
        .xmax = 1.5,
        .ymin = -1.5,
        .ymax = 1.5,
        .xs = &x[0],
        .length = 10};

    path = generateFractalPathMandelbrot(runPNG);
    clock_t begin = clock();

    image *test = compute(runPNG);
    saveToPNG(*test, path);
    
    clock_t end = clock();

    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    if (time_spent > 60) {
        printf("\nTime spent computing: %d minutes and %d seconds. \n", (((int)time_spent / 60)), ((int)time_spent % 60));
    } else {
        printf("\nTime spent computing: %f seconds. \n", time_spent);
    }
    free(test->pixels);
    free(test);
    freeSpline(R, 10);
    freeSpline(G, 10);
    freeSpline(B, 10);

    return 0;
}