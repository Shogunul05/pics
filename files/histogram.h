#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include "types.h"
#include <stdio.h>

/**
 * Displays a histogram of pixel intensities for grayscale images
 * @param imagine - grayscale image matrix
 * @param imagine_rgb - RGB image matrix (must be NULL)
 * @param linie - image height
 * @param coloana - image width
 * @param fileup - flag indicating if an image is loaded
 * @param x - maximum width of histogram bars (in stars)
 * @param y - number of histogram bins (must be power of 2, between 2-256)
 */
void HISTOGRAM(int **imagine, pixel **imagine_rgb, int linie,
               int coloana, int fileup, int x, int y);

#endif