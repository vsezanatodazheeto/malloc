#include "malloc.h"

#define PR_TINY "TINY:\n"
#define PR_SMALL "SMALL:\n"
#define PR_LARGE "LARGE:\n"

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
		write(1, "\n", 1);
	}
}

static void	show_alloc_mem_extra(const t_page *page)
{
	switch (page->type)
	{
	case P_TINY :
		write(1, PR_TINY, sizeof(PR_TINY) - 1);
		break;
	case P_SMALL :
		write(1, PR_SMALL, sizeof(PR_SMALL) - 1);
		break;
	case P_LARGE :
		write(1, PR_LARGE, sizeof(PR_LARGE) - 1);
		break;
	}
	for (size_t i = 1; page; ++i, page = page->next)
	{
		write(1, "page: ", 6);
		print_address_hex(1, (t_v)page);
		write(1, "\n", 1);
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
