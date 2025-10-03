# Image Editor Project - Module Organization

## Project Structure Overview

This document describes the modular organization of the Image Editor project, where functions have been separated into logical modules for better code maintainability and organization.

## Module Files Created/Updated

### 📁 **load.c / load.h** - Image Loading Module
- **LOAD()** - Main loading function for P1-P6 image formats
- **free_memory()** - Memory cleanup and deallocation
- **load_text_matrix()** - Text format grayscale image loading
- **load_text_rgb_matrix()** - Text format RGB image loading  
- **load_binary_matrix()** - Binary format grayscale image loading
- **load_binary_rgb_matrix()** - Binary format RGB image loading

### 📁 **select.c / select.h** - Image Selection Module
- **SELECT()** - Main selection function for rectangular regions
- **SELECT_ALL()** - Select entire image with output message
- **SELECT_ALL2()** - Helper function for selecting all without output

### 📁 **save.c / save.h** - Image Saving Module
- **SAVE()** - Main saving function with format conversion
- **save_binary()** - Binary format image saving
- **save_ascii()** - ASCII format image saving
- **trim_trailing_spaces()** - String utility function

### 📁 **crop.c / crop.h** - Image Cropping Module
- **CROP()** - Image cropping function for selected regions

### 📁 **functions.c / functions.h** - Image Processing Module
- **APPLY()** - Image filter application (EDGE, SHARPEN, BLUR, GAUSSIAN_BLUR)
- **EQUALIZE()** - Histogram equalization for contrast enhancement
- **choose()** - Kernel selection for convolution filters
- **clamp()** - Value clamping to [0, 255] range
- **form()** - Convolution operation helper

### 📁 **rotate.c / rotate.h** - Image Rotation Module
- **ROTATE()** - Main rotation function (supports 90°, 180°, 270° rotations)
- **rotate_right_pat()** - 90° clockwise rotation for square selections
- **rotate_left_pat()** - 90° counter-clockwise rotation for square selections
- **rotate_entire_matrix_right()** - Full image 90° clockwise rotation
- **rotate_entire_matrix_left()** - Full image 90° counter-clockwise rotation

### 📁 **histogram.c / histogram.h** - Histogram Display Module
- **HISTOGRAM()** - Histogram display function for grayscale images

### 📁 **types.h** - Common Definitions Module
- **pixel struct** - RGB pixel structure definition
- **CMAX** - Maximum command length constant (50)
- **FNMAX** - Maximum filename length constant (100)
