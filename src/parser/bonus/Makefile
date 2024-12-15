PLATFORM = linux

# Set up some generic variables
OBJ_EXT = .o
USE_COMPILER ?= gcc

NULL  :=
SPACE := $(NULL) $(NULL)

H_EXT      = .h
C_EXT      = .c
LEX_EXT    = .l
YACC_EXT   = .y
YACC_H_EXT = .h

LINKER_FLAGS = $(LINKER_OPTIONS)
C_FLAGS      = $(C_OPTIONS)
LEX_FLAGS    = $(LEX_OPTIONS) \
					--header-file=lexer.yy.h \
					--prefix=yy --full \
					--noline
YACC_FLAGS   = $(YACC_OPTIONS) \
					--verbose \
					--locations \
					--no-lines \
					--file-prefix=parser \
					--name-prefix=yy \
					--language=c \
					--defines

LINKER       = gcc
C_COMPILER   = gcc

LINKER_O_FLAG  = -o$(SPACE)

YACC_COMPILER = bison
LEX_COMPILER  = flex
LEX_O_FLAG = -o

# These variables hold the name (without extension)
ALL_C_FILES_IN_DIR   = $(basename $(wildcard ./*$(C_EXT)))

# Set up specific options

C_FILES			= DisplayStructure
YACC_FILES		= parser
LEX_FILES		= lexer
BUILD_LEX_YACC	= true

C_OPTIONS   +=

# Rules

all : build

YACC_INPUT_SOURCES  = $(addsuffix $(YACC_EXT), $(YACC_FILES))
YACC_OUTPUT_FILES   = $(addsuffix .tab,        $(YACC_FILES))
YACC_OUTPUT_SOURCES = $(addsuffix $(C_EXT),    $(YACC_OUTPUT_FILES))
YACC_OBJ            = $(addsuffix $(OBJ_EXT),  $(YACC_OUTPUT_FILES))
YACC_OBJ			+= $(YACC_FILES)-utils.o

LEX_INPUT_SOURCES   = $(addsuffix $(LEX_EXT),  $(LEX_FILES))
LEX_OUTPUT_FILES    = $(addsuffix .yy,         $(LEX_FILES))
LEX_OUTPUT_SOURCES  = $(addsuffix $(C_EXT),    $(LEX_OUTPUT_FILES))
LEX_OBJ             = $(addsuffix $(OBJ_EXT),  $(LEX_OUTPUT_FILES))
LEX_OBJ             += $(LEX_FILES).o

C_SOURCES   				= $(addsuffix $(C_EXT),   $(C_FILES))
C_OBJ       				= $(addsuffix $(OBJ_EXT), $(C_FILES))


C_OBJ_LIST   = $(C_OBJ) $(YACC_OBJ) $(LEX_OBJ)


EXE_NAMES    = $(C_FILES)

.PHONY: all build build_yacc build_lex build_exe re

ifeq ($(BUILD_LEX_YACC),true)
  build: pre_build build_yacc build_lex build_exe post_build
else
  build: pre_build build_exe post_build
endif

re: clean all

pre_build:

post_build:

build_yacc: $(YACC_OUTPUT_SOURCES)

build_lex: $(LEX_OUTPUT_SOURCES)

build_exe: $(EXE_NAMES)

build_lex: build_yacc

$(EXE_NAMES): % : %$(OBJ_EXT) $(YACC_OBJ) $(LEX_OBJ)
	$(LINE_CMD)
	$(LINKER) $(LINKER_FLAGS) $(LINKER_O_FLAG)$@ $^

ifneq ($(DONT_BUILD_LEX_YACC),true)

$(LEX_OBJ) : %.yy$(OBJ_EXT) : $(YACC_FILES).tab$(YACC_H_EXT)

$(YACC_OUTPUT_SOURCES) : %.tab$(C_EXT) : %$(YACC_EXT)
	$(YACC_COMPILER) $(YACC_FLAGS) $^

$(LEX_OUTPUT_SOURCES) : %.yy$(C_EXT) : %$(LEX_EXT)
	$(LEX_COMPILER) $(LEX_FLAGS) $(LEX_O_FLAG)$@ $^

endif

$(C_OBJ_LIST) : %$(OBJ_EXT) : %$(C_EXT)
	$(C_COMPILER) $(C_FLAGS) -c $(filter-out %.tab$(YACC_H_EXT),$(filter-out %$(H_EXT),$^))

.PHONY: clean junk_clean exe_clean obj_clean

clean: junk_clean exe_clean

clean_recompile: exe_clean obj_clean

exe_clean:
	rm -f $(EXE_NAMES) *.stackdump

junk_clean: obj_clean
ifeq ($(BUILD_LEX_YACC),true)
	rm -f $(LEX_OUTPUT_SOURCES) $(addsuffix $(YACC_H_EXT), $(LEX_OUTPUT_FILES)) \
		$(YACC_FILES).output \
		$(YACC_FILES).dot \
		$(YACC_OUTPUT_SOURCES) \
		$(addsuffix $(YACC_H_EXT), $(YACC_OUTPUT_FILES))
endif
	rm -f *~

obj_clean:
	rm -f *$(OBJ_EXT)
