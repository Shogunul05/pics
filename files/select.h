#ifndef SELECT_H
#define SELECT_H

/**
 * Selects a rectangular region of the image
 * @param x1, y1 - top-left corner coordinates
 * @param x2, y2 - bottom-right corner coordinates
 * @param linie - image height
 * @param coloana - image width
 * @param select_x1, select_y1, select_x2, select_y2 - pointers to store selection coordinates
 * @param fileup - flag indicating if an image is loaded
 */
void SELECT(int x1, int y1, int x2, int y2, int linie,
            int coloana, int *select_x1, int *select_y1,
            int *select_x2, int *select_y2, int fileup);

/**
 * Selects the entire image with output message
 * @param linie - image height
 * @param coloana - image width
 * @param select_x1, select_y1, select_x2, select_y2 - pointers to store selection coordinates
 * @param fileup - flag indicating if an image is loaded
 */
void SELECT_ALL(int linie, int coloana, int *select_x1,
                int *select_y1, int *select_x2, int *select_y2,
                int fileup);

/**
 * Selects the entire image without output message (helper function)
 * @param linie - image height
 * @param coloana - image width
 * @param select_x1, select_y1, select_x2, select_y2 - pointers to store selection coordinates
 * @param fileup - flag indicating if an image is loaded
 */
void SELECT_ALL2(int linie, int coloana, int *select_x1,
                 int *select_y1, int *select_x2, int *select_y2,
                 int fileup);

#endif
