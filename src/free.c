#include "../include/malloc.h"

static void			free_defragmentation(t_block *block)
{
	t_block			*head_block;
	int				count;

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

static t_block		*free_block_validation(void *ptr)
{
	t_block		*block;

	if (!ptr)
		return (NULL);
	block = BLOCK_FIRST_ADDR(ptr);
	if (block->magic_num != MAGIC_N)
	{
		dprintf(2, "Error: invalid free pointer!\n");
		return (NULL);
	}
	if (block->is_avail)
	{
		dprintf(2, "Error: double free detected!\n");
		return (NULL);
	}
	return (block);
}

// static void		main_page_remove_page(t_page *page_head, t_page *page_target)
// {
// 	t_page **ptr = &page_head;

// 	while ((*ptr) != page_target)
// 	{
// 		ptr = &(*ptr)->prev;
// 	}
// 	*ptr = page_target->prev;
// }

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

void			m_free(void *ptr)
{
	t_page		*page;
	t_block		*block;
	static int i = 0;

	if (!(block = free_block_validation(ptr)))
		return ;
	block->is_avail = AVAILABLE;
	page = block->page;
	page->avail_size = page->avail_size + block->size;
	page->allocated_blocks--;
	// if (page->allocated_blocks < 1)
		// deallocate_memory(page);
	free_defragmentation(block);
	i++;
}
