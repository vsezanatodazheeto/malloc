#include "../include/malloc.h"

extern void *g_e_rewrite;

t_block		*block_add(void *area, const size_t area_size)
{
	t_block	*block;

	block = (t_block *)area;
	*block = (t_block){.magic_num = MAGIC_N, .is_avail = AVAILABLE, .size = area_size};
	return (block);
}

static void
block_reserve_possible
(t_page *page, t_block *block, const size_t area_size, const size_t unused_size)
{
	t_block *block_possible;

	if (unused_size >= (STRUCT_BLOCK_SIZE * 2))
	{
		block_possible = block_add(BLOCK_LAST_ADDR(block, area_size), unused_size - STRUCT_BLOCK_SIZE);
		block_possible->page = page;
		block_possible->prev = block;
		block->next = block_possible;
		page->avail_size = page->avail_size - STRUCT_BLOCK_SIZE;
	}
	else
	{
		block->size = block->size + unused_size;
		page->avail_size = page->avail_size - unused_size;
	}
}

/*
** если мы нашли свободный подходящий блок >= нужного размера, мы попадаем сюда
** если за этим блоком есть еще один блок, то мы должны узнать нужно ли
** м/д ними создавать еще один свободный(влезет ли он)
** если за этим блоком конец страницы, то аналогично
*/

void		block_reserve(t_page *page, t_block *block, const size_t area_size)
{
	size_t unused_size;

	block->is_avail = UNAVAILABLE;
	block->size = area_size;
	page->avail_size = page->avail_size - area_size;
	page->allocated_blocks++;
	if (block->next)
	{
		unused_size = (t_ch)block->next - BLOCK_LAST_ADDR(block, area_size);
		block_reserve_possible(page, block, area_size, unused_size);
	}
	else
	{
		unused_size = PAGE_LAST_ADDR(page) - BLOCK_LAST_ADDR(block, area_size);
		block_reserve_possible(page, block, area_size, unused_size);
	}
}

/*
** при создании страницы изначально создается блок,
** ищем свободный блок на страницах
** если находим, то возвращаем
** но перед тем как вернуть, нужно создать следующий,
** который будет хранить информацию об пока неиспользованным пространстве
*/

t_block		*block_get_available(const t_page *page, const size_t area_size)
{
	t_block	*block;

	block = NULL;
	printf("--------------------------------\n");
	printf("in: %s\n", __func__);
	for (; page; page = page->prev)
	{
		for (block = page->block_head; block; block = block->next)
		{
			if (block->magic_num != MAGIC_N)
			{
				g_e_rewrite = block;
				return (NULL);
			}
			if (block->is_avail == 1 && block->size >= area_size)
				break ;
		}
		if (block)
		{
			printf("found free block\n");
			block_reserve((t_page *)page, block, area_size);
			break;
		}
	}
	printf("--------------------------------\n");
	return (block);
}
