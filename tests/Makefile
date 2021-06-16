.PHONY: subsystem

all: subsystem
	$(CC) test_1.c -lft_malloc -L.. -I../include -I../libft_printf/include -o test_1
	$(CC) test_2.c -lft_malloc -L.. -I../include -I../libft_printf/include -o test_2
	$(CC) test_3.c -lft_malloc -L.. -I../include -I../libft_printf/include -o test_3

subsystem:
	@$(MAKE) -sC ../

clean:
	@rm test_1 test_2 test_3
