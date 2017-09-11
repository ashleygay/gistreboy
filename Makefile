MAIN=src/main.cpp

GUI=include/gui
GUI_SRC=src/gui/*.cpp

DEBUG=include/debug

PROCESSOR=include/processor
PROCESSOR_SRC=src/processor/*.cpp

GAMEBOY=include/gameboy
GAMEBOY_SRC=src/gameboy/*.cpp

INTERFACE=include/interface
INTERFACE_SRC=src/interface/*.cpp


EXEC=emulator
SRC= $(MAIN) $(GUI_SRC) $(PROCESSOR_SRC) $(INTERFACE_SRC) $(GAMEBOY_SRC)
LIB= -lm -lSDL -lSDL_image -lSDL_ttf -lboost_system `pkg-config --cflags --libs gtk+-3.0`
INCLUDE_PATH= -I$(GUI) -I$(DEBUG) -I$(PROCESSOR) -I$(INTERFACE) -I$(GAMEBOY)
GCC_OPTIONS= -O0 -g -Wall -Wextra -pedantic -std=c++14 -D DEBUG_PRINT_ACTIVATED\
					-D BOOST_DATE_TIME_POSIX_TIME_STD_CONFIG
COMPILER=g++


all:
	 $(COMPILER) $(GCC_OPTIONS) $(INCLUDE_PATH) $(SRC) $(LIB) -o $(EXEC)

clean:
	rm $(EXEC)
