#include "load.h"
#include <stdlib.h>
#include <string.h>


void free_memory(int ***imagine, pixel ***imagine_rgb, int linie)
{
	if (*imagine) {
		for (int i = 0; i < linie; ++i) {
			free((*imagine)[i]);
		}
		free(*imagine);
		*imagine = NULL;
	}
	if (*imagine_rgb) {
		for (int i = 0; i < linie; ++i) {
			free((*imagine_rgb)[i]);
		}
		free(*imagine_rgb);
		*imagine_rgb = NULL;
	}
}

void load_text_matrix(FILE *file, int ***imagine,
					  int linie, int coloana)
{
	*imagine = malloc(linie * sizeof(int *));
	for (int i = 0; i < linie; ++i) {
		(*imagine)[i] = malloc(coloana * sizeof(int));
	}

	for (int i = 0; i < linie; ++i) {
		for (int j = 0; j < coloana; ++j) {
			fscanf(file, "%d", &(*imagine)[i][j]);
		}
	}
}

void load_text_rgb_matrix(FILE *file, pixel ***imagine_rgb,
						  int linie, int coloana)
{
	*imagine_rgb = malloc(linie * sizeof(pixel *));
	for (int i = 0; i < linie; ++i) {
		(*imagine_rgb)[i] = malloc(coloana * sizeof(pixel));
	}

	for (int i = 0; i < linie; ++i) {
		for (int j = 0; j < coloana; ++j) {
			fscanf(file, "%d %d %d",
				   &(*imagine_rgb)[i][j].r,
				   &(*imagine_rgb)[i][j].g,
				   &(*imagine_rgb)[i][j].b);
		}
	}
}

void load_binary_matrix(FILE *file, int ***imagine,
						int linie, int coloana)
{
	*imagine = malloc(linie * sizeof(int *));
	for (int i = 0; i < linie; ++i) {
		(*imagine)[i] = malloc(coloana * sizeof(int));
	}

	unsigned char c = 0;
	fread(&c, sizeof(unsigned char), 1, file);

	for (int i = 0; i < linie; ++i) {
		for (int j = 0; j < coloana; ++j) {
			fread(&c, sizeof(unsigned char), 1, file);
			(*imagine)[i][j] = (int)c;
		}
	}
}

void load_binary_rgb_matrix(FILE *file, pixel ***imagine_rgb,
							int linie, int coloana)
{
	*imagine_rgb = malloc(linie * sizeof(pixel *));
	for (int i = 0; i < linie; ++i) {
		(*imagine_rgb)[i] = malloc(coloana * sizeof(pixel));
	}

	unsigned char c = 0;
	fread(&c, sizeof(unsigned char), 1, file);

	for (int i = 0; i < linie; ++i) {
		for (int j = 0; j < coloana; ++j) {
			fread(&c, sizeof(unsigned char), 1, file);
			(*imagine_rgb)[i][j].r = (int)c;
			fread(&c, sizeof(unsigned char), 1, file);
			(*imagine_rgb)[i][j].g = (int)c;
			fread(&c, sizeof(unsigned char), 1, file);
			(*imagine_rgb)[i][j].b = (int)c;
		}
	}
}

void LOAD(char filename[FNMAX], int ***imagine,
		  pixel ***imagine_rgb, int *fileup, int *linie,
		  int *coloana, int *color, char *type,
		  int *x1, int *y1, int *x2, int *y2)
{
	/* Suppress unused parameter warnings */
	(void)x1;
	(void)y1;
	(void)x2;
	(void)y2;

	if (*fileup == 1) {
		free_memory(imagine, imagine_rgb, *linie);
	}

	FILE *file = fopen(filename, "rt");
	if (!file) {
		printf("Failed to load %s\n", filename);
		*fileup = 0;
		return;
	}

	fscanf(file, "%2s %d %d %d", type, coloana, linie, color);

	if (strcmp(type, "P1") == 0 || strcmp(type, "P2") == 0) {
		load_text_matrix(file, imagine, *linie, *coloana);
	} else if (strcmp(type, "P3") == 0) {
		load_text_rgb_matrix(file, imagine_rgb, *linie, *coloana);
	} else if (strcmp(type, "P4") == 0 ||
			   strcmp(type, "P5") == 0 ||
			   strcmp(type, "P6") == 0) {
		long current_position = ftell(file);
		fclose(file);
		file = fopen(filename, "rb");
		fseek(file, current_position, SEEK_SET);
		if (strcmp(type, "P4") == 0 || strcmp(type, "P5") == 0) {
			load_binary_matrix(file, imagine, *linie, *coloana);
		} else if (strcmp(type, "P6") == 0) {
			load_binary_rgb_matrix(file, imagine_rgb, *linie, *coloana);
		}
	}

	fclose(file);
	*fileup = 1;
	printf("Loaded %s\n", filename);
}