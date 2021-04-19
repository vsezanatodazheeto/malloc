.PHONY: all clean fclean re
# COMPILER SETTINGS-------------------------------------------------------------
CC = clang
CFLAGS = -Wall -Wextra -Werror -pedantic -g

# DETERMINE THE BIT DEPTH FOR MEMORY ALIGNMENT----------------------------------
ifeq ($(shell uname -m), x86_64)
	BITW_RULE="BITW=8"
else
	BITW_RULE="BITW=4"
endif

# COLORS FOR OUTPUT (LINUX)-----------------------------------------------------
BLUE = "\e[38;5;69m"
EOC = "\e[0m"

# LIB (LIBFT, GET_NEXT_LINE, PRINTF)--------------------------------------------
# ПЕРЕДЕЛАТЬ ПОТОМ
L_DIR = lib/
L_NAME = lib.a
L_RULE = $(addsuffix .lib, $(L_DIR))

# MALLOC------------------------------------------------------------------------

## program name
PROG_NAME = a.out

## header dir
H_DIR = include/

## header name
H_NAME = malloc
H_NAME := $(addprefix $(H_DIR), $(addsuffix .h, $(H_NAME)))

## program dir
PROG_DIR := src/

## program srcs
PROG_SRC = malloc \
			free \
			page \
			block \
			debug \
			extra
PROG_SRC := $(addsuffix .c, $(PROG_SRC))

## file path to lib, program src/obj files
PROG_SRC := $(addprefix $(PROG_DIR), $(PROG_SRC))
L_NAME := $(addprefix $(L_DIR), $(L_NAME))

# RULES / DEPENDENCIES----------------------------------------------------------
all: $(L_RULE) $(PROG_NAME)

%.lib:
	@$(MAKE) -sC $(L_DIR)

$(PROG_NAME) : $(PROG_SRC) $(H_NAME) $(L_NAME) Makefile
	@$(CC) $(CFLAGS) $(PROG_SRC) $(L_NAME) -o $(PROG_NAME) -I $(H_DIR) -D $(BITW_RULE)
	@echo $(BLUE)"MALLOC COMPILED"$(EOC)

clean:
	@$(MAKE) -sC $(L_DIR) clean

fclean: clean
	@$(MAKE) -sC $(L_DIR) fclean
	@rm -f $(PROG_NAME)

re: fclean all
