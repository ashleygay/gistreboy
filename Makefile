MAIN=src/main.cpp

GUI=include/gui
GUI_SRC=src/gui/*.cpp

DEBUG=include/debug

PROCESSOR=include/processor

GAMEBOY=include/gameboy
GAMEBOY_SRC=src/gameboy/*.cpp

INTERFACE=include/interface
INTERFACE_SRC=src/interface/*.cpp

EXEC=emulator
SRC= $(MAIN) $(GUI_SRC) $(INTERFACE_SRC) $(GAMEBOY_SRC)
LIB=`pkg-config --cflags --libs gtk+-3.0`
INCLUDE_PATH= -I$(GUI) -I$(DEBUG) -I$(INTERFACE) -I$(GAMEBOY)
GCC_OPTIONS= -O0 -g -Wall -Wextra -pedantic -std=c++14 -D DEBUG_STREAM_ACTIVATED
COMPILER=g++


all:
	 $(COMPILER) $(GCC_OPTIONS) $(INCLUDE_PATH) $(LIB) $(SRC) -o $(EXEC)

clean:
	rm $(EXEC)
