CC=gcc
CFLAGS=-Wall -Wextra -std=c99

SRC=main.c load.c select.c save.c crop.c functions.c rotate.c histogram.c
OBJ=$(SRC:.c=.o)
DEPS=types.h load.h select.h save.h crop.h functions.h rotate.h histogram.h

all: main

main: $(OBJ)
	$(CC) $(CFLAGS) -o main $(OBJ) -lm

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o main
