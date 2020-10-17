CC = g++
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c++17 -I include/
C_DEBUG_FLAGS = -Wall -Wextra -Werror -pedantic -std=c++17 -I include/ -g
HEADERS = include/Dialog.h include/Field.h include/Game.h include/Player.h include/Point.h include/Screen.h
SRC = src/main.cpp src/Field.cpp src/Game.cpp src/Point.cpp

all: build
	./build/main.out

build: build/main.out

build-debug: build/mainDebug.out

clean:
	rm -rf build/*

build/main.out: $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) src/*.cpp -o $@

build/mainDebug.out: $(SRC) $(HEADERS)
	$(CC) $(C_DEBUG_FLAGS) src/*.cpp -o $@
