# README - Program Code Explanation

This document explains how the program works and describes each function used for image processing.

## Introduction
The program is designed to load, save, select, rotate, crop, apply filters and equalize images in various formats. The program supports both grayscale and color RGB images.

### Data Structures Used
1. `typedef struct { int r, g, b; } pixel;`
   - The `pixel` structure represents a color pixel, having three components: red (`r`), green (`g`) and blue (`b`).

### Macro Definitions
1. `#define CMAX 50` - Maximum size of the command read from keyboard.
2. `#define FNMAX 100` - Maximum size of the file name.

### Main Functions

#### 1. `void free_memory(int ***imagine, pixel ***imagine_rgb, int linie)`
This function frees dynamically allocated memory for image matrices, whether grayscale or RGB.
- Traverses matrix rows and frees each row individually.
- Frees memory for main matrices and sets pointers to `NULL`.

#### 2. `void load_text_matrix(FILE *file, int ***imagine, int linie, int coloana)`
Loads a grayscale image from a text file.
- Allocates memory for the image matrix.
- Reads pixel values from file and stores them in the matrix.

#### 3. `void load_text_rgb_matrix(FILE *file, pixel ***imagine_rgb, int linie, int coloana)`
Loads a color (RGB) image from a text file.
- Allocates memory for the pixel matrix.
- Reads triplets of values (R, G, B) from file and stores them in the matrix.

#### 4. `void load_binary_matrix(FILE *file, int ***imagine, int linie, int coloana)`
Loads a grayscale image from a binary file.
- Allocates memory for the matrix.
- Reads pixel values as bytes and converts them to integers for storage.

#### 5. `void load_binary_rgb_matrix(FILE *file, pixel ***imagine_rgb, int linie, int coloana)`
Loads a color (RGB) image from a binary file.
- Allocates memory for the pixel matrix.
- Reads byte triplets and converts them to R, G, B components of each pixel.

#### 6. `void LOAD(...)`
Manages loading an image based on its type (text or binary, grayscale or RGB).
- If an image is already loaded, frees its memory.
- Opens the specified file and reads the header to determine image type.
- Calls corresponding functions for loading the image based on detected type.

#### 7. `void SELECT(...)`
Allows selection of a rectangular region from the image.
- Checks if the image is loaded.
- Corrects coordinates if they are entered in reverse order.
- Validates coordinates and saves them if they are valid.

#### 8. `void SELECT_ALL(...)`
Selects the entire image.
- Sets selection coordinates to image dimensions.
- There's also an auxiliary function `void SELECT_ALL2(...)` with the same functionality but without output. Used to select x1,x2,y1,y2 values after a LOAD.

#### 9. `void CROP(...)`
Crops the image to the selected region.
- Checks if an image is loaded.
- Creates a new matrix with smaller dimensions, copies pixel values from selected region and frees old matrix memory.

#### 10. `void save_binary(...)`
Saves an image in binary format.
- Writes pixel values as bytes to a binary file.

#### 11. `void save_ascii(...)`
Saves an image in text (ASCII) format.
- Writes pixel values to a text file, using spaces between values.

#### 12. `void SAVE(...)`
Manages saving an image based on specified mode (`ascii` or `binary`).
- Opens file in appropriate mode and calls the suitable save function.

#### 13. `void choose(char op[FNMAX], double ker[3][3])`
The choose function selects the kernel corresponding to the filter specified by the user.
- If the user chooses one of the predefined filters (EDGE, SHARPEN, BLUR, GAUSSIAN_BLUR), the function copies the corresponding kernel values into a 3x3 matrix using memcpy.
- The kernel is later used by the APPLY function to calculate new pixel values based on the applied filter.

#### 14. `int clamp(int value)`
The clamp function limits pixel values between 0 and 255.
- If the calculated value exceeds 255, it is set to 255.
- If the value is less than 0, it is set to 0.

#### 15. `pixel form(pixel **imagine_rgb, int i, int j, double ker[3][3])`
The form function calculates the new value of a color pixel using a filter kernel.
- Traverses the current pixel's neighbors in a 3x3 matrix and applies kernel values to the R, G, and B components of neighboring pixels.
- The resulting sums for each component are rounded and limited between 0 and 255 using the `clamp` function.
- Returns the filtered pixel.

#### 16. `void APPLY(...)`
Applies a filter to the selected region of the image.
- Checks if an image is loaded. If the image is grayscale, displays a message and exits the function.
- Validates the filter specified by the user.
- Creates a temporary matrix where filtered pixel values are stored.
- Uses the `form` function to calculate new pixel values in the selected region, avoiding image edges where kernel application would exceed boundaries.
- Copies filtered results back to the original matrix.
- Frees temporary matrix memory and displays confirmation message.

#### 17. `void EQUALIZE(...)`
The function applies histogram equalization on a grayscale image to improve contrast.
- If no image is loaded, displays an error message.
- If the image is color (RGB), displays a message indicating the function requires a grayscale image.
- Creates a histogram vector of 256 elements to count the frequency of each pixel value (between 0 and 255).
- Traverses each image pixel and updates corresponding frequency in the histogram vector.
- Creates an f vector that stores cumulative distribution of pixel values.
- Distributes each pixel value over the [0, 255] interval proportional to cumulative frequency.
- Traverses the image and replaces each pixel with the new calculated value using cumulative distribution.

#### 18. `void HISTOGRAM(...)`
The function displays a histogram of a grayscale image, using a specified number of bins.
- If no image is loaded, displays an error message.
- If the image is color (RGB), displays a message indicating the function requires a grayscale image.
- If the number of bins is not a power of 2 or is outside the [2, 256] range, displays an error message.
- Divides the value range [0, 255] into y equal intervals.
- Traverses the image and updates frequency of pixel values in corresponding interval.
- Determines maximum frequency and normalizes values to represent them graphically with * characters.
- Displays each interval with a proportional number of * characters.

#### 19. `void rotate_right_pat(...)`
The rotate_right_pat function rotates a selected square region from the image by 90 degrees clockwise.

##### For grayscale images:
- Allocates memory for a temporary rot matrix of size n x n.
- Copies pixel values from selected region to temporary matrix, applying rotation through pixel rearrangement.
- Copies rotated values back to original image.
- Frees temporary matrix memory.

##### For color (RGB) images:
- Proceeds similarly, but uses a temporary pixel-type matrix to store R, G, B value triplets of pixels.

#### 20. `void rotate_left_pat(...)`
The `rotate_left_pat` function rotates a selected square region from the image by 90 degrees counterclockwise.
- Follows the same principle as `void rotate_right_pat(...)` but in opposite direction.

#### 21. `void rotate_entire_matrix_right(...)`
The `rotate_entire_matrix_right` function rotates the entire image by 90 degrees clockwise.

##### For grayscale images:
- Allocates memory for a new rot matrix with inverted dimensions (columns x rows).
- Copies pixel values to new matrix, applying rotation.
- Frees old matrix memory and updates image pointer with rotated matrix.

##### For color (RGB) images:
- Proceeds similarly, but uses a temporary pixel-type matrix.

#### 22. `void rotate_entire_matrix_left(...)`
The `rotate_entire_matrix_left` function rotates the entire image by 90 degrees counterclockwise.
- Follows the same principle as `void rotate_entire_matrix_right(...)` but in opposite direction.

#### 23. `void ROTATE(...)`
The function is the main interface for image rotation and manages rotation based on the angle specified by the user.
- If no image is loaded, displays an error message.
- If the specified angle is not a multiple of 90, displays an error message.
- If the selected region is not square and doesn't represent the entire image, displays an error message.
- Calculates the number of steps needed to perform complete rotation, dividing specified angle by 90.
- If rotation applies to a square region, calls rotate_right_pat or rotate_left_pat functions, depending on rotation direction.
- If rotation applies to entire image, calls rotate_entire_matrix_right or rotate_entire_matrix_left functions.
- Updates selection coordinates to reflect new image orientation after rotation.

#### 24. `void handle_*` auxiliary functions
These functions (`handle_load`, `handle_select`, `handle_save`, etc.) manage commands entered by the user and call corresponding functions to execute desired actions.

#### 25. `int main()`
The main function that runs an infinite loop to read and execute commands entered by the user.
- Reads entered command.
- Checks command prefix to determine desired action and calls corresponding auxiliary functions.
- Allows the following commands:
  - `LOAD <file>` - Load an image.
  - `SELECT <x1> <y1> <x2> <y2>` - Select a region.
  - `SELECT ALL` - Select entire image.
  - `CROP` - Crop image to selected region.
  - `APPLY <filter>` - Apply filter to selected region.
  - `EQUALIZE` - Equalize image histogram.
  - `HISTOGRAM <x> <y>` - Display histogram with specified number of intervals.
  - `ROTATE <angle>` - Rotate image by specified angle.
  - `SAVE <file> [ascii]` - Save image.
  - `EXIT` - Exit program and free memory.