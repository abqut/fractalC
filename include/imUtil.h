#ifndef IMUTIL_H
#define IMUTIL_H
typedef struct {
    char *pixels;
    unsigned width;
    unsigned height;
} image;

int saveToPPM(image im, char *path);

int saveToPNG(image im, char *path);

void freeImage(image *im);
#endif // !IMUTIL_H



