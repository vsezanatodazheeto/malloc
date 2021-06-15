#include "malloc.h"

#define PR_TINY "TINY:\n"
#define PR_SMALL "SMALL:\n"
#define PR_LARGE "LARGE:\n"
#define HEADER_1 "PAGE META      | INDEX   | BLOCK META     | BLOCK          | AVAIL | SIZE\n"
#define HEADER_2 "---------------|---------|----------------|----------------|-------|------------\n"

static void	dbg_count_blocks_in_page(const t_page *page)
{
	t_block	*block;
	size_t	i = 1;

	for (block = page->block_head; block && block->magic_num == MAGIC_N ; block = block->next, i++)
	{
		if (page->type != P_LARGE)
		{
			if (i > 1)
				printf("%-14c | ", ' ');
			printf("%-7zu | ", i);
		}
		printf("%-14p | ", (t_v)block);
		printf("%-14p | ", (t_v)BLOCK_JUMP(block, 0));
		printf("%-5s | ", block->avail ? "AV" : "0");
		printf("%zu\n", block->size);
	}
}

static void	show_alloc_mem_extra(const t_page *page)
{
	int	flag = 0;

	switch (page->type)
	{
	case P_TINY :
		printf(PR_TINY);
		break;
	case P_SMALL :
		printf(PR_SMALL);
		break;
	case P_LARGE :
		printf(PR_LARGE);
		break;
	}
	for (size_t i = 1; page; ++i, page = page->next)
	{
		if (page->block_head && flag == 0 && (flag = 1))
		{
			printf(HEADER_1);
			printf(HEADER_2);
		}
		printf("%-14p | ", (t_v)page);
		if (page->type == P_LARGE)
			printf("%-7zu | ", i);
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
