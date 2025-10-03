#include "functions.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>



void choose(char op[FNMAX], double ker[3][3])
{
	if (strcmp(op, "EDGE") == 0) {
		double edge[3][3] = {
			{-1, -1, -1},
			{-1, 8, -1},
			{-1, -1, -1}
		};
		memcpy(ker, edge, sizeof(edge));
	} else if (strcmp(op, "SHARPEN") == 0) {
		double sharpen[3][3] = {
			{0, -1, 0},
			{-1, 5, -1},
			{0, -1, 0}
		};
		memcpy(ker, sharpen, sizeof(sharpen));
	} else if (strcmp(op, "BLUR") == 0) {
		double blur[3][3] = {
			{1.0 / 9, 1.0 / 9, 1.0 / 9},
			{1.0 / 9, 1.0 / 9, 1.0 / 9},
			{1.0 / 9, 1.0 / 9, 1.0 / 9}
		};
		memcpy(ker, blur, sizeof(blur));
	} else if (strcmp(op, "GAUSSIAN_BLUR") == 0) {
		double gaussian_blur[3][3] = {
			{1.0 / 16, 2.0 / 16, 1.0 / 16},
			{2.0 / 16, 4.0 / 16, 2.0 / 16},
			{1.0 / 16, 2.0 / 16, 1.0 / 16}
		};
		memcpy(ker, gaussian_blur, sizeof(gaussian_blur));
	}
}

int clamp(int value)
{
	if (value < 0) {
		return 0;
	} else if (value > 255) {
		return 255;
	}
	return value;
}

pixel form(pixel **imagine_rgb, int i, int j,
		   double ker[3][3])
{
	double sum_r = 0, sum_g = 0, sum_b = 0;

	for (int u = -1; u <= 1; ++u) {
		for (int v = -1; v <= 1; ++v) {
			sum_r += imagine_rgb[i + u][j + v].r * ker[u + 1][v + 1];
			sum_g += imagine_rgb[i + u][j + v].g * ker[u + 1][v + 1];
			sum_b += imagine_rgb[i + u][j + v].b * ker[u + 1][v + 1];
		}
	}

	pixel new_pixel;
	new_pixel.r = clamp((int)(round(sum_r)));
	new_pixel.g = clamp((int)(round(sum_g)));
	new_pixel.b = clamp((int)(round(sum_b)));

	return new_pixel;
}

void APPLY(int ***imagine, pixel ***imagine_rgb, int linie,
		   int coloana, int x1, int y1, int x2, int y2,
		   char op[FNMAX])
{
	if (!*imagine && !*imagine_rgb) {
		printf("No image loaded\n");
		return;
	}

	if (*imagine) {
		printf("Easy, Charlie Chaplin\n");
		return;
	}

	if (strcmp(op, "EDGE") != 0 && strcmp(op, "SHARPEN") != 0 &&
		strcmp(op, "BLUR") != 0 && strcmp(op, "GAUSSIAN_BLUR") != 0) {
		printf("APPLY parameter invalid\n");
		return;
	}

	double ker[3][3];
	choose(op, ker);

	pixel **a = malloc(linie * sizeof(pixel *));
	for (int i = 0; i < linie; ++i) {
		a[i] = malloc(coloana * sizeof(pixel));
	}

	for (int i = y1; i < y2; ++i) {
		for (int j = x1; j < x2; ++j) {
			if (i - 1 < 0 || j - 1 < 0 || i + 1 >= linie || j + 1 >= coloana) {
				a[i][j] = (*imagine_rgb)[i][j];
			} else {
				a[i][j] = form(*imagine_rgb, i, j, ker);
			}
		}
	}

	for (int i = y1; i < y2; ++i) {
		for (int j = x1; j < x2; ++j) {
			(*imagine_rgb)[i][j] = a[i][j];
		}
	}

	for (int i = 0; i < linie; ++i) {
		free(a[i]);
	}
	free(a);

	printf("APPLY %s done\n", op);
}

void EQUALIZE(int ***imagine, int linie, int coloana,
			  int fileup, pixel ***imagine_rgb, char type[3])
{
	/* Suppress unused parameter warning */
	(void)type;

	if (fileup == 0) {
		printf("No image loaded\n");
		return;
	}

	if (*imagine_rgb) {
		printf("Black and white image needed\n");
		return;
	}

	int histogram[256] = {0};
	int total_pixels = linie * coloana;

	for (int i = 0; i < linie; ++i) {
		for (int j = 0; j < coloana; ++j) {
			histogram[(*imagine)[i][j]]++;
		}
	}

	int f[256] = {0};
	f[0] = histogram[0];
	for (int i = 1; i < 256; ++i) {
		f[i] = f[i - 1] + histogram[i];
	}

	for (int i = 0; i < linie; ++i) {
		for (int j = 0; j < coloana; ++j) {
			int a = (*imagine)[i][j];
			(*imagine)[i][j] = (int)(round(255.0 * f[a] / total_pixels));
		}
	}

	printf("Equalize done\n");
}