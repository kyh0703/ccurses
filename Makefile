.SUFFIXES       : .cpp .o

CC              = gcc
CXX             = $(CC)

IL_SRC = $(wildcard $(PWD)/include)

# Copy/Moving files when installing
INC_FILES       =
LIB_FILES       = $(TARGET)
LIB_CPATH       = ./lib

# Include & Library Paths Setting
INC_PATHS       = -I$(IL_SRC)
LIB_PATHS       =

# Define -D
DEFINE			=

#cCompile flags
CFLAGS			= -g -O0 -fPIC -Wall -std=c++11

# Linking flasgs
LFLAGS			= -lstdc++ -lncursesw

# Unit Testing for library
UTSRC           = $(PWD)/example/Test.cpp
UTOBJ           = $(UTSRC:.cpp=.o)
UTBIN           = $(PWD)/bin/Test

# Main Sources and Objects #
# (Edit your TARGET name.) #
SRCS            = $(subst $(UTSRC),,$(wildcard $(PWD)/src/*.cpp))
OBJS            = $(SRCS:.cpp=.o)
TARGET          = libccurses.a
INSTALLS		= $(TARGET)

# Linking Part
# (Select linking option on your TARGET purpose)
all				: $(INSTALLS) test install
$(TARGET)		: $(OBJS) $(UTOBJ)
				@$(AR) -r $(TARGET) $(OBJS) $(UTOBJ)
				@echo "==============================================================="
				@echo "[35m$(TARGET) Compile Complete !![0m"

# STOP! DON'T edit below lines
.cpp.o			:
				@echo "[$(TARGET)] Compiling [33m$<[0m ..."
				@$(CC) $(CFLAGS) -c $< -o $@ $(INC_PATHS) $(DEFINE)

.PHONY: test
test			: $(OBJS) $(UTOBJ)
				@$(CC) -o $(UTBIN) $(OBJS) $(UTOBJ) $(LFLAGS) $(LIB_PATHS)
				@echo "==============================================================="
				@echo "[35m$(UTBIN) Compile Complete !![0m"



install			: $(INSTALLS)
ifdef LIB_FILES
ifdef LIB_CPATH
				@mkdir -p $(LIB_CPATH)
				@mv $(LIB_FILES) $(LIB_CPATH)/
				@echo "[$(TARGET)] [33mCopy Library Files($(LIB_FILES)) to $(LIB_CPATH)[0m ..."
endif
endif
				@echo "==============================================================="
				@echo "[34m$(TARGET) Install Complete !![0m"
clean			:
				@echo "[$(TARGET)] Delete Object Files !!"
				@$(RM) $(OBJS) $(TARGET) $(UTOBJ) $(UTBIN)
