#ifndef LOAD_H
#define LOAD_H

#include <stdio.h>
#include "types.h" 

/**
 * Frees allocated memory for image matrices
 * @param imagine - pointer to grayscale image matrix
 * @param imagine_rgb - pointer to RGB image matrix
 * @param linie - number of rows in the image
 */
void free_memory(int ***imagine, pixel ***imagine_rgb, int linie);

/**
 * Loads a text-format grayscale image matrix from file
 * @param file - input file pointer
 * @param imagine - pointer to store the loaded grayscale matrix
 * @param linie - number of rows
 * @param coloana - number of columns
 */
void load_text_matrix(FILE *file, int ***imagine, int linie, int coloana);

/**
 * Loads a text-format RGB image matrix from file
 * @param file - input file pointer
 * @param imagine_rgb - pointer to store the loaded RGB matrix
 * @param linie - number of rows
 * @param coloana - number of columns
 */
void load_text_rgb_matrix(FILE *file, pixel ***imagine_rgb, int linie, int coloana);

/**
 * Loads a binary-format grayscale image matrix from file
 * @param file - input file pointer
 * @param imagine - pointer to store the loaded grayscale matrix
 * @param linie - number of rows
 * @param coloana - number of columns
 */
void load_binary_matrix(FILE *file, int ***imagine, int linie, int coloana);

/**
 * Loads a binary-format RGB image matrix from file
 * @param file - input file pointer
 * @param imagine_rgb - pointer to store the loaded RGB matrix
 * @param linie - number of rows
 * @param coloana - number of columns
 */
void load_binary_rgb_matrix(FILE *file, pixel ***imagine_rgb, int linie, int coloana);

/**
 * Main function to load an image from file (supports P1-P6 formats)
 * @param filename - name of the file to load
 * @param imagine - pointer to grayscale image matrix
 * @param imagine_rgb - pointer to RGB image matrix
 * @param fileup - flag indicating if an image is loaded
 * @param linie - pointer to number of rows
 * @param coloana - pointer to number of columns
 * @param color - pointer to maximum color value
 * @param type - string to store image type (P1-P6)
 * @param x1, y1, x2, y2 - selection coordinates (unused in this function)
 */
void LOAD(char filename[FNMAX], int ***imagine,
          pixel ***imagine_rgb, int *fileup, int *linie,
          int *coloana, int *color, char *type,
          int *x1, int *y1, int *x2, int *y2);

#endif
