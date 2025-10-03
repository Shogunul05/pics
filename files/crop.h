#ifndef CROP_H
#define CROP_H

#include "types.h"

/**
 * Crops the image to the selected rectangular region
 * @param imagine - pointer to grayscale image matrix
 * @param imagine_rgb - pointer to RGB image matrix
 * @param linie - pointer to image height (updated after cropping)
 * @param coloana - pointer to image width (updated after cropping)
 * @param select_x1, select_y1 - top-left corner of selection (updated to 0,0)
 * @param select_x2, select_y2 - bottom-right corner of selection (updated to new dimensions)
 * @param fileup - flag indicating if an image is loaded
 */
void CROP(int ***imagine, pixel ***imagine_rgb, int *linie,
          int *coloana, int *select_x1, int *select_y1,
          int *select_x2, int *select_y2, int fileup);

#endif
