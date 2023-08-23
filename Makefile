.SUFFIXES: .cpp .o

CC        = gcc

LIB_FILES = $(TARGET)
LIB_CPATH = ./lib

IL_SRC    = $(wildcard $(PWD))
INC_PATHS = -I$(IL_SRC)
LIB_PATHS =

CFLAGS    = -g -O0 -fPIC -Wall -std=c++11
LFLAGS    = -lstdc++ -lncursesw

SRCS      = $(subst $(UTSRC),,$(wildcard $(PWD)/src/*.cpp))
OBJS      = $(SRCS:.cpp=.o)
TARGET    = libccurses.a
INSTALLS  = $(TARGET)

UTSRC     = $(PWD)/example/Test.cpp
UTOBJ	  = $(UTSRC:.cpp=.o)
UTBIN     = $(PWD)/bin/test

default: build

.PHONY: build
build: $(INSTALLS)
$(TARGET) : $(OBJS)
	@echo "build:"
	@$(AR) -r $(TARGET) $(OBJS)

.cpp.o:
	@echo "compile: $<"
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC_PATHS) $(DEFINE)

.PHONY: install
install: $(INSTALLS)
	@echo "install:"
	@mkdir -p $(LIB_CPATH)
	@mv $(LIB_FILES) $(LIB_CPATH)

.PHONY: test
test: $(OBJS) $(UTOBJ)
	@echo "test:"
	@$(CC) -o $(UTBIN) $(OBJS) $(UTOBJ) $(LFLAGS) $(LIB_PATHS)

.PHONY: clean
clean:
	@echo "clean:"
	@$(RM) $(OBJS) $(TARGET) $(UTOBJ) $(UTBIN)