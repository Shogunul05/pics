#include "crop.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void CROP(int ***imagine, pixel ***imagine_rgb, int *linie,
		  int *coloana, int *select_x1, int *select_y1,
		  int *select_x2, int *select_y2, int fileup)
{
	if (fileup == 0) {
		printf("No image loaded\n");
		return;
	}

	int new_linie = *select_y2 - *select_y1;
	int new_coloana = *select_x2 - *select_x1;

	if (*imagine) {
		int **new_imagine = malloc(new_linie * sizeof(int *));
		for (int i = 0; i < new_linie; ++i) {
			new_imagine[i] = malloc(new_coloana * sizeof(int));
			for (int j = 0; j < new_coloana; ++j) {
				new_imagine[i][j] = (*imagine)[*select_y1 + i][*select_x1 + j];
			}
		}
		for (int i = 0; i < *linie; ++i) {
			free((*imagine)[i]);
		}
		free(*imagine);
		*imagine = new_imagine;
	}

	if (*imagine_rgb) {
		pixel **new = malloc(new_linie * sizeof(pixel *));
		for (int i = 0; i < new_linie; ++i) {
			new[i] = malloc(new_coloana * sizeof(pixel));
			for (int j = 0; j < new_coloana; ++j) {
				new[i][j] = (*imagine_rgb)[*select_y1 + i][*select_x1 + j];
			}
		}
		for (int i = 0; i < *linie; ++i) {
			free((*imagine_rgb)[i]);
		}
		free(*imagine_rgb);
		*imagine_rgb = new;
	}

	*linie = new_linie;
	*coloana = new_coloana;
	*select_x1 = 0;
	*select_y1 = 0;
	*select_x2 = *coloana;
	*select_y2 = *linie;

	printf("Image cropped\n");
}
