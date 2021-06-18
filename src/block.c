#include "malloc.h"

t_block	*block_place(void *area, const size_t area_size)
{
	t_block	*block;

	block = (t_block *)area;
	*block = (t_block){.magic_num = MAGIC_N, .size = area_size, .avail = AVAILABLE};
	return (block);
}

// if block added, need to update page->block_last, returns 1

static void	block_check_rest_size(t_block *block, const size_t area_size, const size_t rest_size)
{
	t_block	*block_possible;

	if (rest_size > STRUCT_BLOCK_SIZE)
	{
		block_possible = block_place(BLOCK_JUMP(block, area_size), rest_size - STRUCT_BLOCK_SIZE);
		block_possible->prev = block;
		block_possible->next = block->next;
		block->next = block_possible;
	}
	else
		block->size = block->size + rest_size;
}

// if (block->next)
	// rest_size = (t_ch)block->next - BLOCK_JUMP(block, area_size);
// else
	// rest_size = PAGE_LAST_ADDR(page) - BLOCK_JUMP(block, area_size);

// block_reserve:
// if a avaiable matching block >= of the right size is found, we get here
// check if a new potential avaiable block can be placed behind the block
// (there may be the end of the page or another block)

void	block_reserve(t_block *block, const size_t area_size)
{
	size_t	rest_size;

	rest_size = BLOCK_JUMP(block, block->size) - BLOCK_JUMP(block, area_size);
	block->avail = UNAVAILABLE;
	block->size = area_size;
	block_check_rest_size(block, area_size, rest_size);
}

// block_get_available:
// look for a free block on pages, check for data overwriting (magic_num)
// if the pages are over, then create

t_block	*block_get_available(t_page *page, const size_t area_size)
{
	t_block	*block;

	if (!page && !(page = page_create(area_size)))
		return (NULL);
	for (block = page->block_head; block; block = block->next)
	{
		if (block->magic_num != MAGIC_N)
		{
			error_malloc(block, E_DATA, sizeof(E_DATA));
			return (NULL);
		}
		else if (block->avail && block->size >= area_size)
		{
			block_reserve(block, area_size);
			page->block_unvail_qt++;
			return (block);
		}
	}
	return (block_get_available(page->next, area_size));
}
