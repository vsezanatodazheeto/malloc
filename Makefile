.PHONY: clean fclean re

HOSTTYPE =
ifeq ($(HOSTTYPE = ), )
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
LIB_NAME = libft_malloc.so
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -g

#-------------------------------------------------------------------------------
D_H = include/
H = malloc.h
H := $(addprefix $(D_H), $(H))

#-------------------------------------------------------------------------------
D_SRC = src/
SRC = malloc.c page.c main_page.c block.c free.c debug.c
SRC := $(addprefix $(D_SRC), $(SRC))

#-------------------------------------------------------------------------------
D_OBJ = obj/
OBJ := $(patsubst $(D_SRC)%.c, $(D_OBJ)%.o, $(SRC))

#-------------------------------------------------------------------------------

all: $(NAME)

# $(CC) -shared -o $(NAME) $(OBJ)
# @$(CC) $(CFLAGS) -shared -Wl,-soname,$(NAME) -o $(LIB_NAME) $(OBJ) -lc

$(NAME): $(D_OBJ) $(OBJ) Makefile
	@$(CC) $(CFLAGS) -shared -o $(NAME) $(OBJ) -lc -g
	@ln -sf $(NAME) $(LIB_NAME)
	@echo "--------------------------------------"
	@echo "$(NAME) compiled"
	@echo "--------------------------------------"

$(D_OBJ):
	@mkdir -p $(D_OBJ)

$(D_OBJ)%.o: $(D_SRC)%.c $(H)
	@echo $<
	@$(CC) $(CFLAGS) -fPIC -I$(D_H) -c $< -o $@ -g

clean:
	@rm -rf $(D_OBJ)

fclean: clean
	@rm -rf $(NAME) $(LIB_NAME)

re: fclean all

