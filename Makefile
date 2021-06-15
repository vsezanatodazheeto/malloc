.PHONY: subsystem clean fclean re

HOSTTYPE =
ifeq ($(HOSTTYPE = ), )
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
NAME_BASE = libft_malloc.so
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -g

#-------------------------------------------------------------------------------
D_H = include/
H = malloc.h
H := $(addprefix $(D_H), $(H))

#-------------------------------------------------------------------------------
D_SRC = src/
SRC = malloc.c page.c main_page.c block.c free.c debug.c extra.c
SRC := $(addprefix $(D_SRC), $(SRC))

#-------------------------------------------------------------------------------
D_OBJ = obj/
OBJ := $(patsubst $(D_SRC)%.c, $(D_OBJ)%.o, $(SRC))

#-------------------------------------------------------------------------------
LIB_NAME = ft_printf
LIB_DIR = libft_printf/
LIB_H = $(LIB_DIR)include/

#-------------------------------------------------------------------------------

all: subsystem $(NAME)

$(NAME): $(D_OBJ) $(OBJ) Makefile
	@$(CC) $(CFLAGS) -l$(LIB_NAME) -L$(LIB_DIR) -shared -o $(NAME) $(OBJ) -lc -g
	@echo "--------------------------------------"
	@echo "$(NAME) compiled"
	ln -sf $(NAME) $(NAME_BASE)
	@echo "--------------------------------------"

$(D_OBJ):
	@mkdir -p $(D_OBJ)

$(D_OBJ)%.o: $(D_SRC)%.c $(H)
	@echo $<
	@$(CC) $(CFLAGS) -fPIC -I$(D_H) -I$(LIB_H) -c $< -o $@ -g

subsystem:
	@$(MAKE) -sC $(LIB_DIR)

clean:
	@rm -rf $(D_OBJ)
	@$(MAKE) -sC $(LIB_DIR) clean

fclean: clean
	@rm -rf $(NAME) $(NAME_BASE)
	@$(MAKE) -sC $(LIB_DIR) fclean

re: fclean all

# $(CC) -shared -o $(NAME) $(OBJ)
# @$(CC) $(CFLAGS) -shared -Wl,-soname,$(NAME) -o $(LIB_NAME) $(OBJ) -lc