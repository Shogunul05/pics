#include "histogram.h"
#include <stdlib.h>
#include <string.h>

void HISTOGRAM(int **imagine, pixel **imagine_rgb, int linie,
               int coloana, int fileup, int x, int y)
{
    if (fileup == 0) {
        printf("No image loaded\n");
        return;
    }

    if (imagine_rgb) {
        printf("Black and white image needed\n");
        return;
    }

    if (y < 2 || y > 256 || (y & (y - 1)) != 0) {
        printf("Invalid number of bins\n");
        return;
    }

    int bin_size = 256 / y;
    int bins[y];
    for (int i = 0; i < y; ++i) {
        bins[i] = 0;
    }

    for (int i = 0; i < linie; ++i) {
        for (int j = 0; j < coloana; ++j) {
            int bin_index = imagine[i][j] / bin_size;
            bins[bin_index]++;
        }
    }

    int max_freq = 0;
    for (int i = 0; i < y; ++i) {
        if (bins[i] > max_freq) {
            max_freq = bins[i];
        }
    }

    for (int i = 0; i < y; ++i) {
        int num_stars = bins[i] * 1.0 / max_freq * x;
        printf("%d\t|\t", num_stars);
        for (int j = 0; j < num_stars; ++j) {
            printf("*");
        }
        printf("\n");
    }
}