CC := $(shell command -v clang >/dev/null 2>&1 && echo clang || echo gcc)
CFLAGS = -Wall -Wextra -O2 -Iinclude
SRC = src/main.c src/display.c src/color.c src/utils.c
OBJ = $(SRC:.c=.o)
BIN = supertree

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJ)

clean:
	rm -f $(OBJ) $(BIN)
