CC = gcc
CFLAGS = -g -Wall -Werror -Wextra -std=c99

EXEC = tema1
SOURCES = main.c list.c hashTable_charKey.c
OBJECTS = $(SOURCES:.c=.o)

build: $(OBJECTS)
	$(CC) $^ -o $(EXEC)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -rf $(shell find . -maxdepth 1 -name "*.o") $(EXEC) &> /dev/null
