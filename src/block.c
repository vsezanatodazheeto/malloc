#include "../include/malloc.h"

extern void *g_e_rewrite;

// typedef struct		s_block
// {
// 	size_t			magic_num;
// 	size_t			size;
// 	struct s_block	*prev;
// 	struct s_block	*next;
// 	struct s_block	*avail_prev;
// 	struct s_block	*avail_next;
// 	int				is_avail;
// }					t_block;

// разобрать эту функцию
t_block	*block_add(void *area, const size_t area_size)
{
	t_block	*block = (t_block *)area;

	*block = (t_block){.magic_num = MAGIC_N, .size = area_size, .avail = AVAILABLE};
	return (block);
}

// разобрать эту функцию
static void block_reserve_possible(t_page *page, t_block *block, const size_t area_size, const size_t residual_size)
{
	t_block *block_possible;

	if (residual_size > STRUCT_BLOCK_SIZE)
	{
		block_possible = block_add(BLOCK_LAST_ADDR(block, area_size), residual_size - STRUCT_BLOCK_SIZE);
		block_possible->prev = block;
		block->next = block_possible;
	}
	else
	{
		block->size = block->size + residual_size;
	}
}

/*
** если мы нашли свободный подходящий блок >= нужного размера, мы попадаем сюда
** если за этим блоком есть еще один блок, то мы должны узнать нужно ли
** м/д ними создавать еще один свободный(влезет ли он)
** если за этим блоком конец страницы, то аналогично
*/

// разобрать эту функцию

void	block_reserve(t_page *page, t_block *block, const size_t area_size)
{
	size_t	residual_size;

	page->allocated_blocks++;
	block->avail = UNAVAILABLE;
	block->size = area_size;
	if (block->next)
		residual_size = (t_ch)block->next - BLOCK_LAST_ADDR(block, area_size);
	else
		residual_size = PAGE_LAST_ADDR(page) - BLOCK_LAST_ADDR(block, area_size);
	block_reserve_possible(page, block, area_size, residual_size);
}

/*
** при создании страницы изначально создается блок,
** ищем свободный блок на страницах
** если находим, то возвращаем
** но перед тем как вернуть, нужно создать следующий,
** который будет хранить информацию об пока неиспользованном пространстве
*/

// разобрать эту функцию
t_block	*block_get_available(const t_page *page, const size_t area_size)
{
	t_block	*block = NULL;

	for (; page; page = page->next)
	{
		for (block = page->block_head; block; block = block->next)
		{
			if (block->magic_num != MAGIC_N)
			{
				g_e_rewrite = block;
				return (NULL);
			}
			else if (block->size >= area_size)
				break ;
		}
		if (block)
		{
			block_reserve((t_page *)page, block, area_size);
			break;
		}
	}
	return (block);
}

// t_block	*block_get_available(const t_page *page, const size_t area_size)
// {
// 	t_block	*block;

// 	for (; page; page = page->next)
// 	{
// 		for (block = page->block_avail_head; block; block = block->avail_next)
// 		{
// 			if (block->magic_num != MAGIC_N)
// 			{
// 				g_e_rewrite = block;
// 				return (NULL);
// 			}
// 			else if (block->is_avail == 1 && block->size >= area_size)
// 				break ;
// 		}
// 		if (block)
// 		{
// 			block_reserve((t_page *)page, block, area_size);
// 			break;
// 		}
// 	}
// 	return (block);
// }
