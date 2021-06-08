#include "../include/malloc.h"

static t_page_type	page_ident_type(const size_t area_size)
{
	if (area_size <= BLOCK_TINY_LIMIT)
		return (E_TINY);
	else if (area_size <= BLOCK_SMALL_LIMIT)
		return (E_SMALL);
	return (E_LARGE);
}

static void	page_init(t_page *page, const size_t page_size, const size_t block_size)
{
	memset(page, 0, STRUCT_PAGE_SIZE);
	page->type = page_ident_type(block_size);
	page->size = page_size;
	page->block_head = block_add(PAGE_UNUSED_ADDR(page), page_size - STRUCT_PAGE_SIZE - STRUCT_BLOCK_SIZE);
}

// page_ident_size:
// returns the page size depending on the amount of memory requested

static size_t	page_ident_size(const size_t area_size)
{
	if (area_size <= BLOCK_TINY_LIMIT)
		return (PAGE_TINY_SIZE);
	else if (area_size <= BLOCK_SMALL_LIMIT)
		return (PAGE_SMALL_SIZE);
	return (area_size + STRUCT_PAGE_SIZE + STRUCT_BLOCK_SIZE);
}

// page_create:
// determine the type of page depending on the size of the requested memory area
// request a memory area for the page
// initialize the page with initial parameters
// update the current pointer in main_page to the 'fresh' pointer

t_page	*page_create(const size_t block_size)
{
	t_page	*page;
	size_t	page_size;

	if (!(page_size = page_ident_size(block_size)))
		return (NULL);
	if (!(page = (t_page *)alloc_memory(page_size)))
		return (NULL);
	page_init(page, page_size, block_size);
	main_page_update(page);
	return (page);
}

// page_get_current_by_type:
// get the main_page (static)
// return a pointer to the page type depending on the size of the requested memory area

t_page	*page_get_current_by_type(const size_t block_size)
{
	t_main_page	*main_page;

	main_page = main_page_get();
	if (block_size <= BLOCK_TINY_LIMIT)
		return (main_page->tiny_head);
	else if (block_size <= BLOCK_SMALL_LIMIT)
		return (main_page->small_head);
	return (main_page->large_head);
}

// page_get_available:
// returns the current page depending on the size of the requested memory
// if the page is not found, then create

t_page	*page_get_available(const size_t area_size)
{
	t_page	*page;

	if (!(page = page_get_current_by_type(area_size)))
		page = page_create(area_size);
	return (page);
}
