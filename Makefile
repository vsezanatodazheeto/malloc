.PHONY: clean fclean re

ifeq ($(HOSTTYPE),)
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

$(NAME): $(D_OBJ) $(OBJ) Makefile
	$(CC) -shared -o $(NAME) $(OBJ)
	ln -sf $(NAME) $(LIB_NAME)
	@echo "--------------------------------"
	@echo "$(NAME) compiled"
	@echo "--------------------------------"

$(D_OBJ):
	@mkdir -p $(D_OBJ)

$(D_OBJ)%.o: $(D_SRC)%.c $(H)
	@echo $<
	@$(CC) $(CFLAGS) -fPIC -I $(D_H) -c $< -o $@

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

