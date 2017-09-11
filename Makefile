MAIN=src/main.cpp

GUI=include/gui
GUI_SRC=src/gui/*.cpp

DEBUG=include/debug

PROCESSOR=src/processor

EXEC=emulator
SRC= $(MAIN) $(GUI_SRC)
LIB= -lm -lSDL -lSDL_image -lSDL_ttf `pkg-config --cflags --libs gtk+-3.0`
INCLUDE_PATH= -I$(GUI) -I$(DEBUG)
GCC_OPTIONS= -O0 -g -Wall -Wextra -pedantic -std=c++14 -D DEBUG_PRINT_ACTIVATED
COMPILER=g++


all:
	 $(COMPILER) $(GCC_OPTIONS) $(INCLUDE_PATH) $(SRC) $(LIB) -o $(EXEC)

clean:
	rm $(EXEC)
