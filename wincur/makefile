.SUFFIXES       : .cpp .o

CC              = gcc
CXX             = $(CC)

################################################
# IPRON Source Directory & Environment Setting #
#----------------------------------------------#
ifdef IPRBASE
IPRON_BASE      = $(IPRBASE)
else
IPRON_BASE      = /bridgetec/ipron
endif

# CI build 환경 대응용
ifdef BUILD_PATH
IPRON_SRC       = $(BUILD_PATH)
else
IPRON_SRC       = $(IPRON_BASE)/src
endif

CO_INC					= $(CO_SRC)/inc
CO_LIB					= $(CO_SRC)/lib
IL_SRC          = $(IPRON_SRC)/LIB
TL_BIN          = $(IPRON_BASE)/tools
IL_INC          = $(IL_SRC)/inc
IL_LIB          = $(IL_SRC)/lib

#####################################
# Copy/Moving files when installing #
#-----------------------------------#
INC_FILES       = $(wildcard *.h)
INC_CPATH       = $(IL_INC)/iForm
LIB_FILES       = $(TARGET)
LIB_CPATH       = $(IL_LIB)
BIN_FILES       =
BIN_CPATH       =

###################################
# Include & Library Paths Setting #
#---------------------------------#
INC_PATHS       = -I$(CO_INC) -I$(CO_INC)/iCore -I$(IL_INC) -I$(IL_SRC)
LIB_PATHS       = -L$(CO_LIB) -L$(IL_LIB)

##########################################
# Define / Compile flags / Linking flags #
#----------------------------------------#
DEFINE					=
CFLAGS					= -g -O0 -fPIC -Wall -std=c++11
LFLAGS					= -lstdc++ -lncursesw

############################
# Unit Testing for library #
#--------------------------#
UTSRC           = iTest.cpp
UTOBJ           = $(UTSRC:.cpp=.o)
UTBIN           = iTest

############################
# Main Sources and Objects #
# (Edit your TARGET name.) #
#--------------------------#
SRCS            = $(subst $(UTSRC),,$(wildcard *.cpp))
OBJS            = $(SRCS:.cpp=.o)
TARGET          = libiForm.a
ifdef IRELEASE
INSTALLS				= $(TARGET)
else
DEFINE 					+= -DIDEBUG
INSTALLS				= $(TARGET) $(UTBIN)
endif

##################################################
# Linking Part                                   #
# (Select linking option on your TARGET purpose) #
#------------------------------------------------#
all					: $(INSTALLS)
$(TARGET)		: $(OBJS)
				@$(AR) -r $(TARGET) $(OBJS)
				@echo "==============================================================="
				@echo "[35m$(TARGET) Compile Complete !![0m"

##########################
# DON'T edit below lines #
#------------------------#
$(UTBIN)		: $(OBJS) $(UTOBJ)
				@$(CC) -o $(UTBIN) $(OBJS) $(UTOBJ) $(LFLAGS) $(LIB_PATHS)
				@echo "==============================================================="
				@echo "[35m$(UTBIN) Compile Complete !![0m"
.cpp.o			:
				@echo "[$(TARGET)] Compiling [33m$<[0m ..."
				@$(CC) $(CFLAGS) -c $< -o $@ $(INC_PATHS) $(DEFINE) $(PKGDEF)

install			: $(INSTALLS)
ifdef BIN_FILES
ifdef BIN_CPATH
				@mkdir -p $(BIN_CPATH)
				@mv $(BIN_FILES) $(BIN_CPATH)/
				@echo "[$(TARGET)] [33mMove Binary Files($(BIN_FILES)) to $(BIN_CPATH)[0m ..."
endif
endif
ifdef INC_FILES
ifdef INC_CPATH
				@mkdir -p $(INC_CPATH)
				@cp $(INC_FILES) $(INC_CPATH)/
				@echo "[$(TARGET)] [33mCopy Include Files($(INC_FILES)) to $(INC_CPATH)[0m ..."
endif
endif
ifdef LIB_FILES
ifdef LIB_CPATH
				@mkdir -p $(LIB_CPATH)
				@cp $(LIB_FILES) $(LIB_CPATH)/
				@echo "[$(TARGET)] [33mCopy Library Files($(LIB_FILES)) to $(LIB_CPATH)[0m ..."
endif
endif
				@echo "==============================================================="
				@echo "[34m$(TARGET) Install Complete !![0m"
dep				:
				@gccmakedep $(INC_PATHS) $(SRCS)
				@echo "# Make Source Dependencies Success !!"
clean			:
				@echo "[$(TARGET)] Delete Object Files !!"
				@$(RM) $(OBJS) $(TARGET) $(UTOBJ) $(UTBIN)
