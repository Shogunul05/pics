#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "types.h"
#include <stdio.h>
#include <math.h>

/**
 * Selects the appropriate convolution kernel based on operation type
 * @param op - operation name (EDGE, SHARPEN, BLUR, GAUSSIAN_BLUR)
 * @param ker - 3x3 kernel matrix to be filled
 */
void choose(char op[FNMAX], double ker[3][3]);

/**
 * Clamps a value to the range [0, 255]
 * @param value - input value to be clamped
 * @return clamped value between 0 and 255
 */
int clamp(int value);

/**
 * Applies convolution kernel to a pixel and its neighbors
 * @param imagine_rgb - RGB image matrix
 * @param i, j - pixel coordinates
 * @param ker - 3x3 convolution kernel
 * @return new pixel value after applying kernel
 */
pixel form(pixel **imagine_rgb, int i, int j, double ker[3][3]);

/**
 * Applies image filters (EDGE, SHARPEN, BLUR, GAUSSIAN_BLUR) to selected region
 * @param imagine - pointer to grayscale image matrix
 * @param imagine_rgb - pointer to RGB image matrix
 * @param linie - image height
 * @param coloana - image width
 * @param x1, y1, x2, y2 - selection coordinates
 * @param op - filter operation name
 */
void APPLY(int ***imagine, pixel ***imagine_rgb, int linie,
           int coloana, int x1, int y1, int x2, int y2,
           char op[FNMAX]);

/**
 * Performs histogram equalization on grayscale images
 * @param imagine - pointer to grayscale image matrix
 * @param linie - image height
 * @param coloana - image width
 * @param fileup - flag indicating if an image is loaded
 * @param imagine_rgb - pointer to RGB image matrix (must be NULL)
 * @param type - image type string (unused parameter)
 */
void EQUALIZE(int ***imagine, int linie, int coloana,
              int fileup, pixel ***imagine_rgb, char type[3]);

#endif
