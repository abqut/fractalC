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
    const int width = 2500;
    const int height = 2200;

    //Wikipedia inspired color gradient
    float wikiRed[] = {0, 32, 237, 255, 0, 0};
    float wikiGreen[] = {7, 107, 255, 170, 2, 2};
    float wikiBlue[] = {100, 203, 255, 0, 0, 20};
    float wikiX[] = {0, 0.16, 0.42, 0.6425, 0.8575, 1.0001};

    Polynomial *wikiR = monCubIn(wikiX, wikiRed, 6);
    Polynomial *wikiG = monCubIn(wikiX, wikiGreen, 6);
    Polynomial *wikiB = monCubIn(wikiX, wikiBlue, 6);
    char* path;

    fractalRun runPNG = {
        .width = width,
        .height = height,
        .R = wikiR,
        .B = wikiB,
        .G = wikiG,
        .it = mandelbrot,
        .maxIt = 1024,
        .xmin = -1.9,
        .xmax = 0.6,
        .ymin = -1.1,
        .ymax = 1.1,
        .xs = &wikiX[0],
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
    freeSpline(wikiR, 6);
    freeSpline(wikiG, 6);
    freeSpline(wikiB, 6);   

    return 0;
}