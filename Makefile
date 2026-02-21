CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c99

SOURCES = $(wildcard src/*.c)

all: clean build

build: $(SOURCES)
	$(CC) $(CLFLAGS) $(SOURCES) -o steel

clean:
	rm -f steel

.PHONY: all build clean
