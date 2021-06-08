#include "../include/malloc.h"

static void	dealloc_memory_extra(t_page **head, t_page *page)
{
	t_page	*tmp;

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
	switch (page->type)
	{
	case E_TINY:
		dealloc_memory_extra(&main_page->tiny_head, page);
		break;
	case E_SMALL:
		dealloc_memory_extra(&main_page->small_head, page);
		break;
	case E_LARGE:
		dealloc_memory_extra(&main_page->large_head, page);
		break;
	}
}

// разобрать эту функцию
static void	free_defragmentation(t_block *block)
{
	t_block	*temp;

	temp = block;
	if (temp->prev && temp->prev->avail)
	{
		temp->magic_num = 0;
		temp = temp->prev;
	}
	if (block->next && block->next->avail)
	{
		block->next->magic_num = 0;
		block = block->next;
	}
	if (block->next)
		block->next->prev = temp;
	temp->next = block->next;
	temp->size = BLOCK_LAST_ADDR(block, block->size) - BLOCK_LAST_ADDR(temp, 0);
}

static t_block	*free_block_validation(t_page *page, void *ptr)
{
	t_block		*block;

	for (block = page->block_head; block; block = block->next)
	{
		if (block->magic_num != MAGIC_N)
		{
			dprintf(2, "Error: data overwrite detected!\n");
			return (NULL);
		}
		if (block == BLOCK_FIRST_ADDR(ptr))
			break ;
	}
	if (!block)
	{
		dprintf(2, "Error: invalid free pointer!\n");
		return (NULL);
	}
	if (block->avail)
	{
		dprintf(2, "Error: double free detected!\n");
		return (NULL);
	}
	if (block->next && block->next->magic_num != MAGIC_N)
		dprintf(2, "Error: data overwrite detected!\n");
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
				dprintf(2, "Error: invalid free pointer! in %s\n", __func__);
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
	block->avail = AVAILABLE;
	page->block_qt--;
	if (page->block_qt < 1)
		dealloc_memory(page);
	else
		free_defragmentation(block);
}
