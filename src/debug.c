#include "../include/malloc.h"

#define DB_TINY "TINY:\n"
#define DB_SMALL "SMALL:\n"
#define DB_LARGE "LARGE:\n"

#define DB_PAGE "page: "
#define DB_BYTE " bytes\n"

static void	dbg_count_blocks_in_page(const t_page *page)
{
	t_block	*block;
	size_t	i = 1;

	for (block = page->block_head; block && block->magic_num == MAGIC_N ; block = block->next, i++)
	{
		write(1, "      ", 6);
		print_address_hex(1, BLOCK_JUMP(block, 0));
		write(1, " - ", 3);
		print_address_hex(1, BLOCK_JUMP(block, block->size));
		write(1, "\t", 1);
		if (block->avail)
			write(1, "AV   ", 5);
		else
			write(1, " 0   ", 5);
		print_num(1, block->size);
		write(1, DB_BYTE, sizeof(DB_BYTE) - 1);
	}
}

static void	show_alloc_mem_extra(const t_page *page)
{
	size_t	i = 0;

	switch (page->type)
	{
	case P_TINY :
		write(1, DB_TINY, sizeof(DB_TINY) - 1);
		break;
	case P_SMALL :
		write(1, DB_SMALL, sizeof(DB_SMALL) - 1);
		break;
	case P_LARGE :
		write(1, DB_LARGE, sizeof(DB_LARGE) - 1);
		break;
	}
	for (; page; i++, page = page->next)
	{
		write(1, DB_PAGE, sizeof(DB_PAGE) - 1);
		print_address_hex(1, (t_v)page);
		write(1, " ", 1);
		print_num(1, page->size);
		write(1, DB_BYTE, sizeof(DB_BYTE) - 1);
		dbg_count_blocks_in_page(page);
	}
}

void	show_alloc_mem(void)
{
	t_main_page	*main_page;

	main_page = main_page_get();
	if (main_page->tiny_head)
		show_alloc_mem_extra(main_page->tiny_head);
	if (main_page->small_head)
		show_alloc_mem_extra(main_page->small_head);
	if (main_page->large_head)
		show_alloc_mem_extra(main_page->large_head);
}
