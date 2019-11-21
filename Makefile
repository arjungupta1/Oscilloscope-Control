

CPP   := /usr/bin/g++
CC    := /usr/bin/gcc
CSTD  := -std=c++1y
OPT   := -O0
DEBUG := -g
WARN  := -Wall -Werror

CXX_FLAGS = $(CPP) $(CSTD) $(OPT) $(WARN)

LD_LIBS = -lvisa -lc -lpthread
INC_DIR = -I /usr/local/vxipnp/linux/include

LIB_FILE_NAME = libADC.so

.PHONY: all shared static clean

all:

shared:

static:

clean:



