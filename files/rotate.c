#include "rotate.h"
#include <stdlib.h>
#include <string.h>


void rotate_right_pat(int ***imagine, pixel ***imagine_rgb,
					  int linie, int coloana, int x1,
					  int y1, int x2, int y2)
{
	/* Suppress unused parameter warnings */
	(void)linie;
	(void)coloana;
	(void)x2;

	int n = y2 - y1;

	if (*imagine) {
		int **rot = malloc(n * sizeof(int *));
		for (int i = 0; i < n; ++i) {
			rot[i] = malloc(n * sizeof(int));
		}

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				rot[j][n - i - 1] = (*imagine)[y1 + i][x1 + j];
			}
		}

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				(*imagine)[y1 + i][x1 + j] = rot[i][j];
			}
		}

		for (int i = 0; i < n; ++i) {
			free(rot[i]);
		}
		free(rot);
	}

	if (*imagine_rgb) {
		pixel **rot = malloc(n * sizeof(pixel *));
		for (int i = 0; i < n; ++i) {
			rot[i] = malloc(n * sizeof(pixel));
		}

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				rot[j][n - i - 1] = (*imagine_rgb)[y1 + i][x1 + j];
			}
		}

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				(*imagine_rgb)[y1 + i][x1 + j] = rot[i][j];
			}
		}

		for (int i = 0; i < n; ++i) {
			free(rot[i]);
		}
		free(rot);
	}
}

void rotate_left_pat(int ***imagine, pixel ***imagine_rgb,
					 int linie, int coloana, int x1,
					 int y1, int x2, int y2)
{
	/* Suppress unused parameter warnings */
	(void)linie;
	(void)coloana;
	(void)x2;

	int n = y2 - y1;

	if (*imagine) {
		int **rot = malloc(n * sizeof(int *));
		for (int i = 0; i < n; ++i) {
			rot[i] = malloc(n * sizeof(int));
		}

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				rot[n - j - 1][i] = (*imagine)[y1 + i][x1 + j];
			}
		}

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				(*imagine)[y1 + i][x1 + j] = rot[i][j];
			}
		}

		for (int i = 0; i < n; ++i) {
			free(rot[i]);
		}
		free(rot);
	}

	if (*imagine_rgb) {
		pixel **rot = malloc(n * sizeof(pixel *));
		for (int i = 0; i < n; ++i) {
			rot[i] = malloc(n * sizeof(pixel));
		}

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				rot[n - j - 1][i] = (*imagine_rgb)[y1 + i][x1 + j];
			}
		}

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				(*imagine_rgb)[y1 + i][x1 + j] = rot[i][j];
			}
		}

		for (int i = 0; i < n; ++i) {
			free(rot[i]);
		}
		free(rot);
	}
}

void rotate_entire_matrix_right(int ***imagine,
								pixel ***imagine_rgb,
								int *linie, int *coloana)
{
	if (*imagine) {
		int new_linie = *coloana;
		int new_coloana = *linie;

		int **rot = malloc(new_linie * sizeof(int *));
		for (int i = 0; i < new_linie; ++i) {
			rot[i] = malloc(new_coloana * sizeof(int));
		}

		for (int i = 0; i < *linie; ++i) {
			for (int j = 0; j < *coloana; ++j) {
				rot[j][*linie - i - 1] = (*imagine)[i][j];
			}
		}

		for (int i = 0; i < *linie; ++i) {
			free((*imagine)[i]);
		}
		free(*imagine);

		*imagine = rot;
		*linie = new_linie;
		*coloana = new_coloana;
	}

	if (*imagine_rgb) {
		int new_linie = *coloana;
		int new_coloana = *linie;

		pixel **rot = malloc(new_linie * sizeof(pixel *));
		for (int i = 0; i < new_linie; ++i) {
			rot[i] = malloc(new_coloana * sizeof(pixel));
		}

		for (int i = 0; i < *linie; ++i) {
			for (int j = 0; j < *coloana; ++j) {
				rot[j][*linie - i - 1] = (*imagine_rgb)[i][j];
			}
		}

		for (int i = 0; i < *linie; ++i) {
			free((*imagine_rgb)[i]);
		}
		free(*imagine_rgb);

		*imagine_rgb = rot;
		*linie = new_linie;
		*coloana = new_coloana;
	}
}

void rotate_entire_matrix_left(int ***imagine,
							   pixel ***imagine_rgb,
							   int *linie, int *coloana)
{
	if (*imagine) {
		int new_linie = *coloana;
		int new_coloana = *linie;

		int **rot = malloc(new_linie * sizeof(int *));
		for (int i = 0; i < new_linie; ++i) {
			rot[i] = malloc(new_coloana * sizeof(int));
		}

		for (int i = 0; i < *linie; ++i) {
			for (int j = 0; j < *coloana; ++j) {
				rot[*coloana - j - 1][i] = (*imagine)[i][j];
			}
		}

		for (int i = 0; i < *linie; ++i) {
			free((*imagine)[i]);
		}
		free(*imagine);

		*imagine = rot;
		*linie = new_linie;
		*coloana = new_coloana;
	}

	if (*imagine_rgb) {
		int new_linie = *coloana;
		int new_coloana = *linie;

		pixel **rot = malloc(new_linie * sizeof(pixel *));
		for (int i = 0; i < new_linie; ++i) {
			rot[i] = malloc(new_coloana * sizeof(pixel));
		}

		for (int i = 0; i < *linie; ++i) {
			for (int j = 0; j < *coloana; ++j) {
				rot[*coloana - j - 1][i] = (*imagine_rgb)[i][j];
			}
		}

		for (int i = 0; i < *linie; ++i) {
			free((*imagine_rgb)[i]);
		}
		free(*imagine_rgb);

		*imagine_rgb = rot;
		*linie = new_linie;
		*coloana = new_coloana;
	}
}

void ROTATE(int ***imagine, pixel ***imagine_rgb, int *linie,
			int *coloana, int *select_x1, int *select_y1,
			int *select_x2, int *select_y2, int angle,
			int fileup)
{
	if (fileup == 0) {
		printf("No image loaded\n");
		return;
	}

	if (angle != 90 && angle != -90 && angle != 180 && angle != -180 &&
		angle != 270 && angle != -270 && angle != 360 && angle != -360 &&
		angle != 0) {
		printf("Unsupported rotation angle\n");
		return;
	}

	int n = *select_y2 - *select_y1;
	int m = *select_x2 - *select_x1;
	int full_image = (*select_x1 == 0 && *select_y1 == 0 &&
					  *select_x2 == *coloana && *select_y2 == *linie);

	if (n != m && !full_image) {
		printf("The selection must be square\n");
		return;
	}

	int steps;
	if (angle > 0) {
		steps = angle / 90;
	} else {
		steps = (-angle) / 90;
	}

	if (angle > 0) {
		if (!full_image) {
			for (int i = 0; i < steps; ++i) {
				rotate_right_pat(imagine, imagine_rgb, *linie, *coloana,
								 *select_x1, *select_y1,
								 *select_x2, *select_y2);
			}
		} else {
			for (int i = 0; i < steps; ++i) {
				rotate_entire_matrix_right(imagine, imagine_rgb,
										   linie, coloana);
			}
			*select_x1 = 0;
			*select_y1 = 0;
			*select_x2 = *coloana;
			*select_y2 = *linie;
		}
	} else if (angle < 0) {
		if (!full_image) {
			for (int i = 0; i < steps; ++i) {
				rotate_left_pat(imagine, imagine_rgb, *linie, *coloana,
								*select_x1, *select_y1, *select_x2, *select_y2);
			}
		} else {
			for (int i = 0; i < steps; ++i) {
				rotate_entire_matrix_left(imagine, imagine_rgb, linie, coloana);
			}
			*select_x1 = 0;
			*select_y1 = 0;
			*select_x2 = *coloana;
			*select_y2 = *linie;
		}
	}

	printf("Rotated %d\n", angle);
}
