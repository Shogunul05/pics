
#include "select.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void SELECT(int x1, int y1, int x2, int y2, int linie,
			int coloana, int *select_x1, int *select_y1,
			int *select_x2, int *select_y2, int fileup)
{
	if (fileup == 0) {
		printf("No image loaded\n");
		return;
	}

	if (x1 > x2) {
		int temp = x1;
		x1 = x2;
		x2 = temp;
	}
	if (y1 > y2) {
		int temp = y1;
		y1 = y2;
		y2 = temp;
	}

	if (x1 < 0 || y1 < 0 || x2 > coloana || y2 > linie ||
		x1 >= x2 || y1 >= y2) {
		printf("Invalid set of coordinates\n");
		return;
	}

	*select_x1 = x1;
	*select_y1 = y1;
	*select_x2 = x2;
	*select_y2 = y2;
	printf("Selected %d %d %d %d\n", x1, y1, x2, y2);
}

void SELECT_ALL(int linie, int coloana, int *select_x1,
				int *select_y1, int *select_x2, int *select_y2,
				int fileup)
{
	if (fileup == 0) {
		printf("No image loaded\n");
		return;
	}

	*select_x1 = 0;
	*select_y1 = 0;
	*select_x2 = coloana;
	*select_y2 = linie;
	printf("Selected ALL\n");
}

void SELECT_ALL2(int linie, int coloana, int *select_x1,
				 int *select_y1, int *select_x2, int *select_y2,
				 int fileup)
{
	if (fileup == 0) {
		return;
	}

	*select_x1 = 0;
	*select_y1 = 0;
	*select_x2 = coloana;
	*select_y2 = linie;
}