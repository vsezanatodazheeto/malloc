.PHONY: clean fclean re

HOSTTYPE =
ifeq ($(HOSTTYPE = ), )
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

VERSION = 1
NAME = libft_malloc_$(HOSTTYPE).so.$(VERSION)
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
# @echo $(FILES)

all: $(NAME)

# gcc -g -shared -Wl,-soname,libhello.so.0 -o libhello.so.0.0 libhello.o -lc
# @echo $(NAME)

$(NAME): $(D_OBJ) $(OBJ) Makefile
	@$(CC) $(CFLAGS) -shared -Wl,-soname,$(NAME) -o $(LIB_NAME) $(OBJ) -lc
	@ln -sf $(NAME) $(LIB_NAME)
	@echo "--------------------------------------"
	@echo "$(NAME) compiled"
	@echo "--------------------------------------"

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

