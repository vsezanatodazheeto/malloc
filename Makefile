# DETERMINE THE BIT DEPTH FOR MEMORY ALIGNMENT----------------------------------
ifeq ($(shell uname -m), x86_64)
	BITW_RULE="BITW=8"
else
	BITW_RULE="BITW=4"
endif
#-------------------------------------------------------------------------------
NAME = libft_malloc.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic
#-------------------------------------------------------------------------------
DH = include/
H = malloc.h \
	malloc_errors.h
H := $(addprefix $(DH), $(H))
#-------------------------------------------------------------------------------
DSRC = src/
SRC = \
	malloc \
	page \
	main_page \
	block \
	free \
	debug
SRC := $(addprefix $(DSRC), $(addsuffix .c, $(SRC)))
#-------------------------------------------------------------------------------
DOBJ = obj/
OBJ = $(patsubst $(DSRC)%, $(DOBJ)%, $(SRC))
OBJ := $(patsubst %.c, %.o, $(OBJ))
#-------------------------------------------------------------------------------
all:
	@$(MAKE) -s $(NAME)

$(NAME): $(DOBJ) $(OBJ)
	gcc main.c $(OBJ) -I$(DH)
	# @ar -rc $(NAME) $(OBJ)
	@echo "--------------------------------"
	@echo "$(NAME) compiled"
	@echo "--------------------------------"

$(DOBJ):
	@mkdir -p $(DOBJ)

$(DOBJ)%.o: $(DSRC)%.c $(H) Makefile
	@echo $<
	@$(CC) $(CFLAGS) \
	-D BITW=8 \
	-I$(DH) -c $< -o $@

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
