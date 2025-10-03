#include "save.h"
#include <stdlib.h>
#include <string.h>




void save_binary(FILE *file2, int **imagine, pixel **imagine_rgb,
				 int linie, int coloana)
{
	if (imagine) {
		unsigned char *buffer = malloc(coloana * sizeof(unsigned char));
		/*if (buffer == NULL) {
			printf("Memory allocation failed.\n");
			fclose(file2);
			return;
		}*/
		for (int i = 0; i < linie; ++i) {
			for (int j = 0; j < coloana; ++j) {
				buffer[j] = (unsigned char)(imagine[i][j]);
			}
			fwrite(buffer, sizeof(unsigned char), coloana, file2);
		}
		free(buffer);
	} else if (imagine_rgb) {
		for (int i = 0; i < linie; ++i) {
			unsigned char rgb_buffer[coloana * 3];
			for (int j = 0; j < coloana; ++j) {
				rgb_buffer[j * 3] = (unsigned char)(imagine_rgb[i][j].r);
				rgb_buffer[j * 3 + 1] = (unsigned char)(imagine_rgb[i][j].g);
				rgb_buffer[j * 3 + 2] = (unsigned char)(imagine_rgb[i][j].b);
			}
			fwrite(rgb_buffer, sizeof(unsigned char), coloana * 3, file2);
		}
	}
}

void save_ascii(FILE *file2, int **imagine, pixel **imagine_rgb,
				int linie, int coloana)
{
	if (imagine) {
		for (int i = 0; i < linie; ++i) {
			for (int j = 0; j < coloana; ++j) {
				fprintf(file2, "%d ", imagine[i][j]);
			}
			fprintf(file2, "\n");
		}
	} else if (imagine_rgb) {
		for (int i = 0; i < linie; ++i) {
			for (int j = 0; j < coloana; ++j) {
				fprintf(file2, "%d %d %d ",
						imagine_rgb[i][j].r,
						imagine_rgb[i][j].g,
						imagine_rgb[i][j].b);
			}
			fprintf(file2, "\n");
		}
	}
}

void trim_trailing_spaces(char *str)
{
	int len = strlen(str);
	while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\n')) {
		str[--len] = '\0';
	}
}

void SAVE(const char *filename, const char *mode, int **imagine,
		  pixel **imagine_rgb, int linie, int coloana,
		  int color, int fileup, char type[3])
{
	if (fileup == 0) {
		printf("No image loaded\n");
		return;
	}

	char mode_clean[10];
	strcpy(mode_clean, mode);
	trim_trailing_spaces(mode_clean);

	FILE *file2;
	if (strcmp(mode_clean, "ascii") == 0) {
		file2 = fopen(filename, "wt");

		if (strcmp(type, "P5") == 0) {
			strcpy(type, "P2");
		}
		if (strcmp(type, "P4") == 0) {
			strcpy(type, "P1");
		}
		if (strcmp(type, "P6") == 0) {
			strcpy(type, "P3");
		}

		fprintf(file2, "%s\n%d %d\n%d\n", type, coloana, linie, color);
		save_ascii(file2, imagine, imagine_rgb, linie, coloana);
	} else {
		file2 = fopen(filename, "wb");

		if (strcmp(type, "P2") == 0) {
			strcpy(type, "P5");
		}
		if (strcmp(type, "P1") == 0) {
			strcpy(type, "P4");
		}
		if (strcmp(type, "P3") == 0) {
			strcpy(type, "P6");
		}

		fprintf(file2, "%s\n%d %d\n%d\n", type, coloana, linie, color);
		save_binary(file2, imagine, imagine_rgb, linie, coloana);
	}

	fclose(file2);
	printf("Saved %s\n", filename);
}
