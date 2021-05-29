#include "../include/malloc.h"

/*MAIN_PAGE-------------------------------------------------------------------*/


// ОСТАНОВИЛИСЬ ЗДЕСЬ
static void	main_page_deallocate_memory_extra(t_page **head, t_page **last, t_page *page)
{
	t_page	*tmp;

	if (*last == page)
		*last = page->prev;
	if (*head == page)
	{
		page->prev = NULL;
		*head = page->next;
		munmap((t_v)page, page->size);
		return ;
	}
	for (tmp = *head; tmp->next; tmp = tmp->next)
	{
		if (tmp->next == page)
		{
			tmp->next = page->next;
			if (page->next)
				page->next->prev = tmp;
			munmap((t_v)page, page->size);
			return ;
		}
	}
}

static void	dealloc_memory(t_page *page)
{
	t_main_page	*main_page;

	main_page = main_page_get();
	if (page->type == E_TINY)
		dealloc_memory_extra(&main_page->tiny_head, &main_page->tiny_last, page);
	else if (page->type == E_SMALL)
		dealloc_memory_extra(&main_page->small_head, &main_page->small_last, page);
	else
		dealloc_memory_extra(&main_page->large_head, &main_page->large_last, page);
}

/*PAGE------------------------------------------------------------------------*/

// разобрать эту функцию
static void	free_defragmentation(t_block *block)
{
	t_block	*head_block;
	int		count;

	head_block = block;
	count = 1;
	if (head_block->prev && head_block->prev->is_avail && \
		head_block->magic_num == MAGIC_N)
	{
		head_block = head_block->prev;
		count++;
	}
	if (block->next && block->next->is_avail && \
		block->next->magic_num == MAGIC_N)
	{
		block = block->next;
		count++;
	}
	if (block->next)
		block->next->prev = head_block;
	head_block->next = block->next;
	head_block->size = BLOCK_LAST_ADDR(block, block->size) - ((t_ch)head_block + STRUCT_BLOCK_SIZE);
	printf("free count blocks %d\n", count);
}

static t_block	*free_block_find(t_page *page, void *ptr)
{
	t_block	*block;

	for (block = page->block_head; block; block = block->next)
	{
		if (block == BLOCK_FIRST_ADDR(ptr))
			break ;
	}
	return (block);
}

static t_block	*free_block_validation(t_page *page, void *ptr)
{
	t_block		*block;

	block = free_block_find(page, ptr);
	if (!block)
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
			if (!(page = free_page_find(main_page->large_head, ptr)))
			{
				dprintf(2, "Error: invalid free pointer! in %s\n", __func__);
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

	if (!ptr)
		return ;
	if (!(page = free_page_validation(ptr)))
		return ;
	if (!(block = free_block_validation(page, ptr)))
		return ;
	else
		printf("BLOCK FOUNED!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	block->is_avail = AVAILABLE;
	block->magic_num = 0;
	if (--page->allocated_blocks < 1)
		dealloc_memory(page);
	else
		free_defragmentation(block);
}
