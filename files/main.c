#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "load.h"
#include "select.h"
#include "save.h"
#include "crop.h"
#include "functions.h"
#include "rotate.h"
#include "histogram.h"

void handle_load(char *command, int ***imagine, pixel ***imagine_rgb,
				 int *fileup,
				 int *linie, int *coloana, int *color, char *type,
				 int *select_x1, int *select_y1, int *select_x2, int *select_y2)
{
	char filename[FNMAX];
	strncpy(filename, command + 5, FNMAX - 1);
	LOAD(filename, imagine, imagine_rgb, fileup, linie, coloana,
		 color, type, select_x1, select_y1, select_x2, select_y2);
	SELECT_ALL2(*linie, *coloana, select_x1, select_y1,
				select_x2, select_y2, *fileup);
}

void handle_select(char *command, int linie, int coloana,
				   int *select_x1, int *select_y1,
				   int *select_x2, int *select_y2, int fileup)
{
	char buffer[100];
	int x1, y1, x2, y2;
	int num_values = 0;

	trim_trailing_spaces(command + 7);
	strcpy(buffer, command + 7);

	if (strncmp(buffer, "ALL", 3) == 0 && strlen(buffer) == 3) {
		SELECT_ALL(linie, coloana, select_x1,
				   select_y1, select_x2, select_y2, fileup);
	} else {
		num_values = sscanf(buffer, "%d %d %d %d", &x1, &y1, &x2, &y2);
		if (num_values != 4) {
			printf("Invalid command\n");
		} else {
			SELECT(x1, y1, x2, y2, linie, coloana, select_x1,
				   select_y1, select_x2, select_y2, fileup);
		}
	}
}

void handle_save(char *command, int **imagine, pixel **imagine_rgb,
				 int linie, int coloana, int color, int fileup, char *type)
{
	char filename[FNMAX];
	char mode[10] = "notascii";
	if (sscanf(command + 5, "%s", filename) != 1) {
		printf("Failed to read filename\n");
	}

	char *space_pos = strchr(command + 5, ' ');
	if (space_pos) {
		if (sscanf(space_pos + 1, "%s", mode) != 1) {
			strcpy(mode, "notascii");
		}
	}

	trim_trailing_spaces(mode);
	SAVE(filename, mode, imagine, imagine_rgb,
		 linie, coloana, color, fileup, type);
}

void handle_histogram(char *command, int **imagine, pixel **imagine_rgb,
					  int linie, int coloana, int fileup)
{
	int x, y;
	char extra[CMAX];
	int num_values = sscanf(command + 10, "%d %d %s", &x, &y, extra);

	if (num_values != 2) {
		printf("Invalid command\n");
	} else {
		HISTOGRAM(imagine, imagine_rgb, linie, coloana, fileup, x, y);
	}
}

void handle_rotate(char *command, int ***imagine, pixel ***imagine_rgb,
				   int *linie, int *coloana,
				   int *select_x1, int *select_y1, int *select_x2,
				   int *select_y2, int fileup)
{
	int angle;
	char extra[CMAX];
	int num_values = sscanf(command + 7, "%d %s", &angle, extra);

	if (num_values != 1) {
		printf("Invalid command\n");
	} else {
		ROTATE(imagine, imagine_rgb, linie, coloana, select_x1,
			   select_y1, select_x2, select_y2, angle, fileup);
	}
}

int main(void)
{
	char command[CMAX];
	int linie = 0, coloana = 0, color = 0;
	int fileup = 0;
	int **imagine = NULL;
	pixel **imagine_rgb = NULL;
	char type[3] = {0};

	int select_x1 = 0, select_y1 = 0, select_x2 = 0, select_y2 = 0;

	while (1) {
		fgets(command, CMAX, stdin);
		int len = strlen(command);
		if (len > 0 && command[len - 1] == '\n') {
			command[len - 1] = '\0';
		}

		if (strncmp(command, "LOAD", 4) == 0) {
			handle_load(command, &imagine, &imagine_rgb, &fileup, &linie,
						&coloana, &color, type,
						&select_x1, &select_y1, &select_x2, &select_y2);
		} else if (strncmp(command, "SELECT", 6) == 0) {
			handle_select(command, linie, coloana,
						  &select_x1, &select_y1, &select_x2,
						  &select_y2, fileup);
		} else if (strncmp(command, "SAVE", 4) == 0) {
			handle_save(command, imagine, imagine_rgb,
						linie, coloana, color, fileup, type);
		} else if (strncmp(command, "CROP", 4) == 0) {
			CROP(&imagine, &imagine_rgb, &linie, &coloana,
				 &select_x1, &select_y1, &select_x2, &select_y2, fileup);
		} else if (strncmp(command, "APPLY", 5) == 0) {
			if (fileup == 0) {
				printf("No image loaded\n");
			} else if (strlen(command) <= 6) {
				printf("Invalid command\n");
			} else {
				char op[FNMAX];
				if (sscanf(command + 6, "%s", op) != 1) {
					printf("Invalid command\n");
				}
				APPLY(&imagine, &imagine_rgb, linie, coloana,
					  select_x1, select_y1, select_x2, select_y2, op);
			}
		} else if (strncmp(command, "HISTOGRAM", 9) == 0) {
			if (fileup == 0) {
				printf("No image loaded\n");
			} else {
				handle_histogram(command, imagine, imagine_rgb,
								 linie, coloana, fileup);
			}
		} else if (strncmp(command, "EXIT", 4) == 0) {
			free_memory(&imagine, &imagine_rgb, linie);
			if (fileup == 0)
				printf("No image loaded");
			break;
		} else if (strncmp(command, "EQUALIZE", 8) == 0) {
			EQUALIZE(&imagine, linie, coloana,
					 fileup, &imagine_rgb, type);
		} else if (strncmp(command, "ROTATE", 6) == 0) {
			if (fileup == 0) {
				printf("No image loaded\n");
			} else {
				handle_rotate(command, &imagine, &imagine_rgb, &linie,
							  &coloana, &select_x1, &select_y1,
							  &select_x2, &select_y2, fileup);
			}
		} else {
			printf("Invalid command\n");
		}
	}
	return 0;
}
