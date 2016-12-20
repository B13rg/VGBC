CC = g++
FLAGS = -c 

BUILDDIR = ./
SRC_PATH = ./src

FILES = dmgcpu.cpp mem.cpp emulator.cpp gpu.cpp

SOURCE = $(FILES:%.cpp=$(SRC_PATH)/%.cpp)

all:
	${CC} ${FLAGS} -I${SRC_PATH}$(SOURCE) 
	