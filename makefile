CC = gcc

CFLAGS = -Iinclude -Wall -Wextra -Werror

SRC = $(wildcard src/*.c)

OBJ = $(patsubst src/%.c,output/%.o,$(SRC))

TARGET = output/BASH_ir

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

output/%.o: src/%.c
	@mkdir -p output
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f output/*.o $(TARGET)

.PHONY: clean