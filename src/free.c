#include "../include/malloc.h"

static void	free_defragmentation(t_block *block)
{
	t_block	*head_block;
	int		count;

	head_block = block;
	count = 1;
	if (head_block->prev && head_block->prev->is_avail && head_block->magic_num == MAGIC_N)
	{
		head_block = head_block->prev;
		count++;
	}
	if (block->next && block->next->is_avail && block->next->magic_num == MAGIC_N)
	{
		block = block->next;
		count++;
	}
	if (block->next)
		block->next->prev = head_block;
	head_block->next = block->next;
	head_block->size = BLOCK_LAST_ADDR(block, block->size) - ((t_ch)head_block + STRUCT_BLOCK_SIZE);
	if (count > 1)
	{
		head_block->page->avail_size += count * STRUCT_BLOCK_SIZE;
	}
	printf("free count blocks %d\n", count);
}

static t_block	*free_block_find(t_page *page, void *ptr)
{
	t_block	*block;

	block = page->block_head;

	for (; block; block = block->next)
	{
		if (block == BLOCK_FIRST_ADDR(ptr))
			break ;
	}
	return (block);
}

static t_block	*free_block_validation(t_page *page, void *ptr)
{
	t_block		*block;

	if (!(block = free_block_find(page, ptr)))
	{
		dprintf(2, "Error: invalid free pointer!\n");
		return (NULL);
	}
	if (block->magic_num != MAGIC_N)
	{
		dprintf(2, "Error: data overwrite detected!\n");
		return (NULL);
	}
	if (block->is_avail)
	{
		dprintf(2, "Error: double free detected!\n");
		return (NULL);
	}
	return (block);
}

static t_page	*free_page_find(t_page *page, void *ptr)
{
	for (; page; page = page->next)
	{
		if (ptr > (t_v)page && ptr < (t_v)PAGE_LAST_ADDR(page))
			break ;
	}
	return (page);
}

static t_page	*free_page_validation(void *ptr)
{
	t_main_page	*main_page;
	t_page		*page;

	main_page = main_page_get();
	if (!(page = free_page_find(main_page->tiny_head, ptr)))
	{
		if (!(page = free_page_find(main_page->small_head, ptr)))
		{
			if (!(page = free_page_find(main_page->small_head, ptr)))
			{
				dprintf(2, "Error: invalid free pointer!\n");
				return (NULL);
			}
		}
	}
	return (page);
}

void	m_free(void *ptr)
{
	t_page	*page;
	t_block	*block;
	// static int	i = 0;

	if (!ptr)
		return ;
	if (!(page = free_page_validation(ptr)))
		return ;
	if (!(block = free_block_validation(page, ptr)))
		return ;

	// зануление
	block->is_avail = AVAILABLE;
	block->magic_num = 0;

	// page = block->page;
	// page->avail_size = page->avail_size + block->size;
	page->allocated_blocks--;
	// if (page->allocated_blocks < 1)
		// deallocate_memory(page);
	free_defragmentation(block);
	// i++;
}


// остановились здесь
// static void		deallocate_memory(t_page *page)
// {
// 	t_main_page *main_page;

// 	main_page = main_page_get();
// 	if (page->type == E_TINY)
// 		main_page_remove_page(main_page->tiny_curr, page);
// 	else if (page->type == E_SMALL)
// 		main_page_remove_page(main_page->small_curr, page);
// 	else
// 		main_page_remove_page(main_page->large_curr, page);
// 	munmap((t_v)((t_ch)page - STRUCT_PAGE_SIZE), page->size);
// }
