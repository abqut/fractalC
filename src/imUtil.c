#include "imUtil.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define CHANNEL_NUM 3

int saveToPPM(image im, char *path) {
    FILE *pgmimg;
    char tmp[200];
    snprintf(tmp, 200, "%s.ppm", path);
    pgmimg = fopen(tmp, "wb");
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

void freeImage(image * im){
    free(im->pixels);
    free(im);
}

