MAIN=src/main.cpp

GUI=include/gui
_GUI_SRC += callback.cpp
_GUI_SRC += gui_setup.cpp
_GUI_SRC += open_button_helper.cpp
GUI_SRC = $(patsubst %,$(GUI)/%,$(_GUI_SRC))
GUI_SRC = $(patsubst %,$(subst include,src,$(GUI))/%,$(_GUI_SRC))


PROCESSOR=include/processor
_PROCESSOR_SRC += instruction.cpp
_PROCESSOR_SRC += instructionargs.cpp
_PROCESSOR_SRC += instructionset.cpp
_PROCESSOR_SRC += processor.cpp
_PROCESSOR_SRC += registers.cpp
PROCESSOR_SRC = $(patsubst %,$(subst include,src,$(PROCESSOR))/%,\
		$(_PROCESSOR_SRC))


GAMEBOY=include/gameboy
_GAMEBOY_SRC += gameboy.cpp
_GAMEBOY_SRC += interrupthandler.cpp
_GAMEBOY_SRC += keypress.cpp
GAMEBOY_SRC = $(patsubst %,$(subst include,src,$(GAMEBOY))/%,\
		$(_GAMEBOY_SRC))

INTERFACE=include/interface
_INTERFACE_SRC += emulator.cpp
INTERFACE_SRC = $(patsubst %,$(subst include,src,$(INTERFACE))/%,\
		$(_INTERFACE_SRC))

MEMORY=include/memory
_MEMORY_SRC += cartridge.cpp
_MEMORY_SRC += memory.cpp
_MEMORY_SRC += video.cpp
MEMORY_SRC = $(patsubst %,$(subst include,src,$(MEMORY))/%,\
		$(_MEMORY_SRC))

HELPERS=include/helpers

# SETUP BUILD DIRECTORY
OBJ_DIR=build

# ALL INCLUDES GO THERE
INCLUDES= -I$(GUI) -I$(INTERFACE) -I$(GAMEBOY)\
	  -I$(HELPERS) -I$(MEMORY) -I$(PROCESSOR)

# FIND ALL SOURCES AND PUTH THEM IN BUILD DIR
SRC= $(MAIN) $(GUI_SRC) $(INTERFACE_SRC) $(GAMEBOY_SRC)\
	$(MEMORY_SRC) $(PROCESSOR_SRC)

OBJS = $(SRC:.cpp=.o)

# SETUP ALL NECESSARY FLAGS
LIB=`pkg-config --cflags --libs gtk+-3.0` -lboost_system
INCLUDE_PATH= -I$(GUI) -I$(INTERFACE) -I$(GAMEBOY) -I$(HELPERS) -I$(MEMORY) -I$(PROCESSOR)

CC_OPTIONS= -O0 -g -Wall -Wextra -pedantic -std=c++14 \
	-D DEBUG_STREAM_ACTIVATED\
	-D BOOST_DATE_TIME_POSIX_TIME_STD_CONFIG

CXXFLAGS = $(CC_OPTIONS) $(INCLUDES) $(LIB)

emulator: $(OBJS)
	g++ -o $@ $^ $(CXXFLAGS)

.PHONY: clean

clean:
	rm emulator $(OBJS)
