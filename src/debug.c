#include "../include/malloc.h"

void	dbg_page(t_page *page)
{
	printf("-------------------------------------------\n");
	printf("page addr: [%p]\n", (t_v)page);
	printf("page->allocated_blocks: [%ld]\n", page->allocated_blocks);
	printf("page->size: [%zu]\n", page->size);
	printf("page->type: [%s]\n", page->type == 0 ? "TINY" : page->type == 1 ? "SMALL" : "LARGE");
	printf("-------------------------------------------\n");
}

void				dbg_block(t_block *block)
{
	printf("---------------debug block-----------------\n");
	if (!block)
	{
		printf("-------------------------------------------\n");
		return ;
	}
	printf("block->addr: [%p]\n", (t_v)block);
	printf("block->prev: [%p]\n", (t_v)block->prev);
	printf("block->next: [%p]\n", (t_v)block->next);
	printf("block->avil: [%d]\n", block->is_avail);
	printf("block->size: [%zu]\n", block->size);
	printf("-------------------------------------------\n");
}

void				dbg_gfinfo(const t_page_type type)
{
	t_page			*page;
	int				block_size;

	if (type == E_TINY)
		block_size = BLOCK_TINY_LIMIT;
	else if (type == E_SMALL)
		block_size = BLOCK_SMALL_LIMIT;
	else
		block_size = BLOCK_SMALL_LIMIT + 1;
	page = page_get_current_by_type(block_size);
	if (!page)
		return ;
	printf("------------------%s--------------------\n", (type == E_TINY? "TINY PAGE" : type == E_SMALL? "SMALL PAGE" : "LARGE PAGE"));
	printf("t_page size: %lu\n", STRUCT_PAGE_SIZE);
	printf("t_block size: %lu\n", STRUCT_BLOCK_SIZE);
	for (int i = 1; page; ++i, page = page->next)
	{
		printf("P [%d] ", i);
		if (page->type == E_LARGE)
			printf("[%lu b]", page->size);
		else
			printf("[%lu]-[page size] = [%lu] b", page->size, page->size - STRUCT_PAGE_SIZE);
		printf("[%p]:\n", (void *)page);
		printf("\tallocated_blocks_count: [%ld]\n", page->allocated_blocks);
		dbg_count_blocks_in_page(page);
	}
}

void				dbg_count_blocks_in_page(const t_page *page)
{
	t_block			*block;
	uint32_t		i;

	if (!page)
		return ;
	if (!(block = page->block_head))
		dprintf(2, "\tNOT BLOCKS ON THE PAGE\n");
	for (i = 1; block; ++i)
	{
		printf("\tB [#%d] [%lu bytes + %lu == %lu] [%p]:\n", i, block->size, STRUCT_BLOCK_SIZE, block->size + STRUCT_BLOCK_SIZE, (void *)block);
		printf("\t\tis aviable:\t[%d]\n", block->is_avail);
		printf("\t\tarea:      \t[%lu]\n",block->size);
		printf("\t\tblock->prev\t%p\n", (t_v)block->prev);
		printf("\t\tblock->next\t%p\n", (t_v)block->next);
		block = block->next;
	}
}

void				dbg_count_pages(const t_page_type type)
{
	t_page			*page;
	uint64_t		i;
	int				block_size;

	i = 0;
	if (type == E_TINY)
		block_size = BLOCK_SMALL_LIMIT;
	else if (type == E_SMALL)
		block_size = BLOCK_SMALL_LIMIT;
	else
		block_size = BLOCK_SMALL_LIMIT + 1;
	page = page_get_current_by_type(block_size);
	if (!page)
		return ;
	while (page)
	{
		page = page->next;
		i++;
	}
	switch (type)
	{
	case (E_TINY):
		printf("TINY pages: %llu\n", i);
		break;
	case (E_SMALL):
		printf("SMALL pages: %llu\n", i);
		break;
	case (E_LARGE):
		printf("LARGE pages: %llu\n", i);
		break;
	default:
		;
	}
}
