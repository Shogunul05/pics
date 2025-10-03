#ifndef ROTATE_H
#define ROTATE_H

#include "types.h"
#include <stdio.h>

/**
 * Rotates a square selection 90 degrees clockwise
 * @param imagine - pointer to grayscale image matrix
 * @param imagine_rgb - pointer to RGB image matrix
 * @param linie, coloana - image dimensions (unused)
 * @param x1, y1 - top-left corner of square selection
 * @param x2, y2 - bottom-right corner of square selection
 */
void rotate_right_pat(int ***imagine, pixel ***imagine_rgb,
                      int linie, int coloana, int x1,
                      int y1, int x2, int y2);

/**
 * Rotates a square selection 90 degrees counter-clockwise
 * @param imagine - pointer to grayscale image matrix
 * @param imagine_rgb - pointer to RGB image matrix
 * @param linie, coloana - image dimensions (unused)
 * @param x1, y1 - top-left corner of square selection
 * @param x2, y2 - bottom-right corner of square selection
 */
void rotate_left_pat(int ***imagine, pixel ***imagine_rgb,
                     int linie, int coloana, int x1,
                     int y1, int x2, int y2);

/**
 * Rotates the entire image 90 degrees clockwise
 * @param imagine - pointer to grayscale image matrix
 * @param imagine_rgb - pointer to RGB image matrix
 * @param linie - pointer to image height (swapped with width)
 * @param coloana - pointer to image width (swapped with height)
 */
void rotate_entire_matrix_right(int ***imagine,
                                pixel ***imagine_rgb,
                                int *linie, int *coloana);

/**
 * Rotates the entire image 90 degrees counter-clockwise
 * @param imagine - pointer to grayscale image matrix
 * @param imagine_rgb - pointer to RGB image matrix
 * @param linie - pointer to image height (swapped with width)
 * @param coloana - pointer to image width (swapped with height)
 */
void rotate_entire_matrix_left(int ***imagine,
                               pixel ***imagine_rgb,
                               int *linie, int *coloana);

/**
 * Main rotation function supporting multiple angles (90, -90, 180, etc.)
 * @param imagine - pointer to grayscale image matrix
 * @param imagine_rgb - pointer to RGB image matrix
 * @param linie - pointer to image height
 * @param coloana - pointer to image width
 * @param select_x1, select_y1, select_x2, select_y2 - pointers to selection coordinates
 * @param angle - rotation angle in degrees
 * @param fileup - flag indicating if an image is loaded
 */
void ROTATE(int ***imagine, pixel ***imagine_rgb, int *linie,
            int *coloana, int *select_x1, int *select_y1,
            int *select_x2, int *select_y2, int angle,
            int fileup);

#endif
