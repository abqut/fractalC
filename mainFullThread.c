#include <complex.h>
#include <math.h>
#include <omp.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// IDEA: Julia set of c * sin(z)

#include "functions\functions.h"
#include "polyLib\polynomial.h"

#define STB_IMAGE_IMPLEMENTATION
#include "lib\stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "lib\stb_image_write.h"

#define CHANNEL_NUM 3

typedef int (*iterator)(long double, long double, int);

typedef float (*logIterator)(long double, long double, int);

typedef struct {
    iterator it;
    int width;
    int height;
    double xmin;
    double xmax;
    double ymin;
    double ymax;
    int maxIt;
    char *path;
    Polynomial *R;
    Polynomial *G;
    Polynomial *B;
    float *xs;
    int length;
} fractalRun;

typedef struct {
    logIterator it;
    int width;
    int height;
    double xmin;
    double xmax;
    double ymin;
    double ymax;
    int maxIt;
    char *path;
    Polynomial *R;
    Polynomial *G;
    Polynomial *B;
    float *xs;
    int length;
} fractalLog;

typedef struct {
    char *pixels;
    unsigned width;
    unsigned height;
} image;

int saveToPPM(image im, char *path) {
    FILE *pgmimg;
    char tmp[200];
    snprintf(tmp, 200, "%s.ppm", path);
    pgmimg = fopen(tmp, "wb");
    //  Writing Magic Number to the File
    fprintf(pgmimg, "P6\n");
    fprintf(pgmimg, "%d %d\n", im.width, im.height);
    fprintf(pgmimg, "%d\n", 255);
    fwrite(im.pixels, 1, im.width * im.height * 3, pgmimg);
    fclose(pgmimg);
    return 0;
}

int saveToPNG(image im, char *path) {
    uint8_t *pixels = malloc(im.width * im.height * (CHANNEL_NUM) * sizeof(uint8_t));
    int j = 0;
    for (int i = 0; i < im.width * im.height; i++) {
        pixels[j] = (uint8_t)im.pixels[j];
        j++;
        pixels[j] = (uint8_t)im.pixels[j];
        j++;
        pixels[j] = (uint8_t)im.pixels[j];
        j++;
    }
    
    char tmp[200];
    snprintf(tmp, 200, "%s.png", path);
    if (!(stbi_write_png(tmp, im.width, im.height, CHANNEL_NUM, pixels, CHANNEL_NUM * im.width))) {
        fprintf(stderr, "ERROR: Writing Image failed.");
        free(pixels);
        return 1;
    }
    free(pixels);
    return 0;
}


image *createCanvas(unsigned width, unsigned height){
    image *im = malloc(sizeof(image));
    im->height = height;
    im->width = width;
    return im;
}

char *generateFractalPathJulia(fractalRun run){
    char* outPath = malloc(200 * sizeof(char));
    double x = (run.xmax + run.xmin) * 0.5;
    double y = (run.ymax + run.ymin) * 0.5;
    snprintf(outPath, 200, "C:/Users/noahb/Desktop/code/fractals/dump/julia%.2f_%.2f_%dx%d_%.2f_%.2f_%d",x,y, run.width, run.height, JSX, JSY, run.maxIt);
    return outPath;
}

char *generateFractalPathMandelbrot(fractalRun run){
    char* outPath = malloc(200 * sizeof(char));
    double x = (run.xmax + run.xmin) * 0.5;
    double y = (run.ymax + run.ymin) * 0.5;
    snprintf(outPath, 200, "C:/Users/noahb/Desktop/code/fractals/dump/mandel%.2f_%.2f_%dx%d_%d",x,y, run.width, run.height, run.maxIt);
    return outPath;
}

void freeImage(image * im){
    free(im->pixels);
    free(im);
}

image *compute(fractalRun run) {
    int *red = malloc((run.maxIt + 1) * (sizeof(int)));
    int *gre = malloc((run.maxIt + 1) * (sizeof(int)));
    int *blu = malloc((run.maxIt + 1) * (sizeof(int)));
    image *im = malloc(sizeof(image));
    im->height = run.height;
    im->width = run.width;
    im->pixels = malloc(im->height * im->width * 3);
    long tot = run.width * run.height;
    const double fx = (double)run.maxIt;
    for (int du = 0; du <= run.maxIt; du++) {
        float fd = (float)du;
        float val = fd / fx;
        red[du] = (int)(evalSpline(run.R, run.xs, val, run.length));
        gre[du] = (int)(evalSpline(run.G, run.xs, val, run.length));
        blu[du] = (int)(evalSpline(run.B, run.xs, val, run.length));
    }
    int i, j;
    long prog, tenth;
    const long double x_inc = (run.xmax - run.xmin) / run.width;
    const long double y_inc = (run.ymax - run.ymin) / run.height;
    j = 0;
    prog = 0;
    tenth = 1;
#pragma omp parallel for ordered
    for (i = 0; i < run.width * run.height; i++) {
        long double x = i % run.width;
        long double y = floor(i / run.width);
        long double u = x * x_inc + run.xmin;
        long double v = y * y_inc + run.ymin;
        int it = run.it(u, v, run.maxIt);
        if (prog > tenth * (tot / 100)) {
            int p = (int)((((float)prog) / ((float)tot)) * 100);
            printf("\rIn progress %d%", p);
            fflush(stdout);
            tenth++;
        }
        prog++;
#pragma omp ordered
        im->pixels[j] = (char)red[it];
        j++;
        im->pixels[j] = (char)gre[it];
        j++;
        im->pixels[j] = (char)blu[it];
        j++;
    }
    free(red);
    free(gre);
    free(blu);
    return im;
}

int main() {
    const int width = 4000;
    const int height = 4000;
    const double TPI = M_PI_2;

    float yr[10] = {0, 112, 160, 206, 239, 255, 255, 255, 255, 255};
    float ygg[10] = {0, 0, 0, 0, 52, 97, 140, 179, 255, 255};
    float yb[10] = {0, 136, 72, 0, 0, 0, 0, 0, 0, 255};
    float x[10] = {0, 0.1111, 0.2222, 0.3333, 0.4444, 0.5555, 0.6666, 0.7777, 0.8888, 1.0001};

    Polynomial *R = monCubIn(x, yr, 10);
    Polynomial *G = monCubIn(x, ygg, 10);
    Polynomial *B = monCubIn(x, yb, 10);

    fractalRun run = {
        .width = width,
        .height = height,
        .R = R,
        .B = B,
        .G = G,
        .it = weirdSinh,
        .path = "c:/Users/noahb/Desktop/weirdSinhbig.ppm",
        .maxIt = 1000,
        .xmin = -1.5,
        .xmax = 1.5,
        .ymin = -1.5,
        .ymax = 1.5,
        .xs = &x[0],
        .length = 10};

    fractalRun runPNG = {
        .width = width,
        .height = height,
        .R = R,
        .B = B,
        .G = G,
        .it = weirdExp,
        .path = NULL,//"c:/Users/noahb/Desktop/7kjulia0.285_0.01_500.PNG",
        .maxIt = 30,
        .xmin = -1.5,
        .xmax = 1.5,
        .ymin = -1.5,
        .ymax = 1.5,
        .xs = &x[0],
        .length = 10};

    runPNG.path = "c:/Users/noahb/Desktop/weirdmf.PNG";//generateFractalPathJulia(runPNG);
    clock_t begin = clock();

    image *test = compute(runPNG);
    saveToPNG(*test, runPNG.path);
    

    clock_t end = clock();

    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    if (time_spent > 60) {
        printf("\nTime spent computing: %d minutes and %d seconds. \n", (((int)time_spent / 60)), ((int)time_spent % 60));
    } else {
        printf("\nTime spent computing: %f seconds. \n", time_spent);
    }
    free(runPNG.path);
    free(test->pixels);
    free(test);
    freeSpline(R, 10);
    freeSpline(G, 10);
    freeSpline(B, 10);

    return 0;
}