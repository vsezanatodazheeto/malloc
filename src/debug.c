#include "../include/malloc.h"

#define PR_TINY "TINY"
#define PR_SMALL "SMALL"
#define PR_LARGE "LARGE"

static void	dbg_count_blocks_in_page(const t_page *page)
{
	t_block *block;
	int flag = 0, i = 1;

	for (block = page->block_head; block; block = block->next)
	{
		if (page->type != E_LARGE && !flag)
		{
			printf("%-14p | ", (t_v)page);
			flag = 1;
		}
		else if (page->type == E_LARGE)
			printf("%-14p | ", (t_v)page);
		else
			printf("%-14c | ", ' ');
		printf("%-7d | ", i++);
		printf("%-14p | ", (t_v)block);
		printf("%-14p | ", (t_v)BLOCK_LAST_ADDR(block, 0));
		printf("%-5d | ", block->avail);
		printf("%zu\n", block->size);
	}
}

static void show_alloc_mem_extra(const t_page *page)
{
	int flag = 0;

	switch (page->type)
	{
	case E_TINY:
		printf("\n%s:\n", PR_TINY);
		break;
	case E_SMALL:
		printf("\n%s:\n", PR_SMALL);
		break;
	case E_LARGE:
		printf("\n%s:\n", PR_LARGE);
		break;
	}
	for (int i = 1; page; ++i, page = page->next)
	{
		if (page->block_last && flag == 0)
		{
			flag = 1;
			printf("PAGE META      | INDEX   | BLOCK META     | BLOCK          | AVAIL | SIZE\n");
			printf("---------------|---------|----------------|----------------|-------|------------\n");
		}
		dbg_count_blocks_in_page(page);
	}
}

void show_alloc_mem(void)
{
	t_main_page *main_page;

	main_page = main_page_get();
	if (main_page->tiny_head)
		show_alloc_mem_extra(main_page->tiny_head);
	if (main_page->small_head)
		show_alloc_mem_extra(main_page->small_head);
	if (main_page->large_head)
		show_alloc_mem_extra(main_page->large_head);
}
