#ifndef SAVE_H
#define SAVE_H

#include <stdio.h>
#include "types.h"

/**
 * Saves image data in binary format to file
 * @param file2 - output file pointer
 * @param imagine - grayscale image matrix
 * @param imagine_rgb - RGB image matrix
 * @param linie - image height
 * @param coloana - image width
 */
void save_binary(FILE *file2, int **imagine, pixel **imagine_rgb,
                 int linie, int coloana);

/**
 * Saves image data in ASCII format to file
 * @param file2 - output file pointer
 * @param imagine - grayscale image matrix
 * @param imagine_rgb - RGB image matrix
 * @param linie - image height
 * @param coloana - image width
 */
void save_ascii(FILE *file2, int **imagine, pixel **imagine_rgb,
                int linie, int coloana);

/**
 * Removes trailing spaces and newlines from a string
 * @param str - string to be trimmed
 */
void trim_trailing_spaces(char *str);

/**
 * Main function to save an image to file
 * @param filename - name of the output file
 * @param mode - save mode ("ascii" or binary)
 * @param imagine - grayscale image matrix
 * @param imagine_rgb - RGB image matrix
 * @param linie - image height
 * @param coloana - image width
 * @param color - maximum color value
 * @param fileup - flag indicating if an image is loaded
 * @param type - image type string (P1-P6)
 */
void SAVE(const char *filename, const char *mode, int **imagine,
          pixel **imagine_rgb, int linie, int coloana,
          int color, int fileup, char type[3]);

#endif
