#include "../include/malloc.h"

// ЭТУ ВОЗМОЖНО ТОЖЕ
t_block	*block_add(void *area, const size_t area_size)
{
	t_block	*block = (t_block *)area;

	*block = (t_block){.magic_num = MAGIC_N, .size = area_size, .avail = AVAILABLE};
	return (block);
}

// ПЕРЕИМЕНОВАТЬ ЭТУ ФУНКЦИЮ
static void block_reserve_possible(t_block *block, const size_t area_size, const size_t rest_size)
{
	t_block *block_possible;

	if (rest_size > STRUCT_BLOCK_SIZE)
	{
		block_possible = block_add(BLOCK_LAST_ADDR(block, area_size), rest_size - STRUCT_BLOCK_SIZE);
		block_possible->prev = block;
		block->next = block_possible;
	}
	else
		block->size = block->size + rest_size;
}

// block_reserve:
// if a avaiable matching block >= of the right size is found, we get here
// check if a new potential avaiable block can be placed behind the block
// (there may be the end of the page or another block)

void	block_reserve(t_page *page, t_block *block, const size_t area_size)
{
	size_t	rest_size;

	page->block_qt++;
	block->avail = UNAVAILABLE;
	block->size = area_size;
	if (block->next)
		rest_size = (t_ch)block->next - BLOCK_LAST_ADDR(block, area_size);
	else
		rest_size = PAGE_LAST_ADDR(page) - BLOCK_LAST_ADDR(block, area_size);
	block_reserve_possible(block, area_size, rest_size);
}

// block_get_available:
// look for a free block on pages, check for data overwriting (magic_num)
// if the pages are over, then create

t_block	*block_get_available(const t_page *page, const size_t area_size)
{
	t_block	*block = NULL;

	if (!page && !(page = page_create(area_size)))
		return (NULL);
	for (block = page->block_head; block; block = block->next)
	{
		// printf("ищем блок\n");
		if (block->magic_num != MAGIC_N)
		{
			dprintf(2, "Error: data overwrite detected at [%p]\n", (t_v)block);
			return (NULL);
		}
		else if (block->avail && block->size >= area_size)
		{
			// printf("нашли подходящий\n");
			block_reserve((t_page *)page, block, area_size);
			return (block);
		}
	}
	return (block_get_available(page->next, area_size));
}
