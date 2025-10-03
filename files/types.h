#ifndef TYPES_H
#define TYPES_H

/* Maximum command length */
#define CMAX 50
/* Maximum filename length */
#define FNMAX 100

#include <math.h>

/**
 * Structure representing an RGB pixel
 * @param r - red component (0-255)
 * @param g - green component (0-255)
 * @param b - blue component (0-255)
 */
typedef struct {
    int r, g, b;
} pixel;

#endif
