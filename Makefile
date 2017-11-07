MAIN=src/main.cpp

GUI=include/gui
GUI_SRC=src/gui/*.cpp

PROCESSOR=include/processor
PROCESSOR_SRC=src/processor/*.cpp

GAMEBOY=include/gameboy
GAMEBOY_SRC=src/gameboy/*.cpp

INTERFACE=include/interface
INTERFACE_SRC=src/interface/*.cpp

HELPERS=include/helpers

EXEC=emulator
SRC= $(MAIN) $(GUI_SRC) $(INTERFACE_SRC) $(GAMEBOY_SRC)
LIB=`pkg-config --cflags --libs gtk+-3.0` -lboost_system
INCLUDE_PATH= -I$(GUI) -I$(INTERFACE) -I$(GAMEBOY) -I$(HELPERS)
GCC_OPTIONS= -O0 -g -Wall -Wextra -pedantic -std=c++14 -D DEBUG_STREAM_ACTIVATED\
	-D BOOST_DATE_TIME_POSIX_TIME_STD_CONFIG
COMPILER=g++


all:
	 $(COMPILER) $(GCC_OPTIONS) $(INCLUDE_PATH) $(LIB) $(SRC) -o $(EXEC)

clean:
	rm $(EXEC)
