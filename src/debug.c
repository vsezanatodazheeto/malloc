#include "../include/malloc.h"

#define PR_TINY "TINY"
#define PR_SMALL "SMALL"
#define PR_LARGE "LARGE"

void	dbg_count_blocks_in_page(const t_block *block)
{
	uint32_t	i;

	if (block)
		printf("INDEX | ADDRES      | AVAIL | SIZE\n");
		printf("------|-------------|-------|---------------------------\n");
	for (i = 1; block; ++i)
	{
		printf("%-5d | ", i);
		printf("%p | ", (t_v)block);
		printf("%-5d | ", block->avail);
		printf("%zu\n", block->size);
		block = block->next;
	}
}

static void show_alloc_mem_extra(const t_page *page)
{
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
	// 0x10fa470004136
	// 0x107700030
	for (int i = 1; page; ++i, page = page->next)
	{
		printf("\n");
		printf("%d\t", i);
		printf("%p\t", (t_v)page);
		printf("%lu bytes\n", page->size - STRUCT_PAGE_SIZE);
		// printf("\tallocated_blocks_count: [%ld]\n", page->block_qt);
		dbg_count_blocks_in_page(page->block_head);
	}
}

// 0x10cf52000

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

// void	dbg_gfinfo(const t_page_type type)
// {
// 	t_page	*page;
// 	int		block_size;

// 	switch (type)
// 	{
// 	case E_TINY:
// 		block_size = BLOCK_TINY_LIMIT;
// 		break;
// 	case E_SMALL:
// 		block_size = BLOCK_SMALL_LIMIT;
// 		break;
// 	case E_LARGE:
// 		block_size = BLOCK_SMALL_LIMIT + 1;
// 		break;
// 	}
// 	if (!(page = page_get_current_by_type(block_size)))
// 		return ;
// 	printf("------------------%s--------------------\n", (type == E_TINY? "TINY PAGE" : type == E_SMALL? "SMALL PAGE" : "LARGE PAGE"));
// 	printf("t_page size: %lu\n", STRUCT_PAGE_SIZE);
// 	printf("t_block size: %lu\n", STRUCT_BLOCK_SIZE);
// 	for (int i = 1; page; ++i, page = page->next)
// 	{
// 		printf("P [%d] ", i);
// 		if (page->type == E_LARGE)
// 			printf("[%lu b]", page->size);
// 		else
// 			printf("[%lu]-[page size] = [%lu] b", page->size, page->size - STRUCT_PAGE_SIZE);
// 		printf("[%p]:\n", (void *)page);
// 		printf("\tallocated_blocks_count: [%ld]\n", page->block_qt);
// 		dbg_count_blocks_in_page(page);
// 	}
// }
