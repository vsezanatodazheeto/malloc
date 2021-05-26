#include "../include/malloc.h"

/*MAIN_PAGE-------------------------------------------------------------------*/

static void	main_page_update_extra(t_page **page_last, t_page *page_new)
{
	if (*page_last)
	{
		(*page_last)->next = page_new;
		page_new->prev = *page_last;
	}
	*page_last = page_new;
}

static void	main_page_update(t_page *page)
{
	t_main_page	*main_page;

	main_page = main_page_get();
	if (page->type == E_TINY)
	{
		if (!main_page->tiny_head)
			main_page->tiny_head = page;
		main_page_update_extra(&main_page->tiny_last, page);
	}
	else if (page->type == E_SMALL)
	{
		if (!main_page->small_head)
			main_page->small_head = page;
		main_page_update_extra(&main_page->small_last, page);
	}
	else
	{
		if (!main_page->large_head)
			main_page->large_head = page;
		main_page_update_extra(&main_page->large_last, page);
	}
}

/*
** Возвращает адрес статической структуры, которая хранит информацию
** о страницах разных типов
*/

t_main_page	*main_page_get(void)
{
	static t_main_page	main_page;

	return (&main_page);
}

/*PAGE-------------------------------------------------------------------------*/

static t_page_type	page_ident_type(const size_t area_size)
{
	if (area_size <= (BLOCK_TINY_LIMIT))
		return (E_TINY);
	else if (area_size <= (BLOCK_SMALL_LIMIT))
		return (E_SMALL);
	return (E_LARGE);
}

/*
** page_ident_size():
**
** возвращает размер страницы в зависимости от количества запрашиваемой памяти
** если это не TINY и не SMALL, то проверяем на переполнение
** tiny block	<= 128 		|		tiny page == 2 * getpagesize() (2 * 4096)
** small block	<= 1024		|		small page == 16 * getpagesize() (16 * 4096)
** large block	> 1024		|		large page == area_size + malloc meta data
*/

static size_t	page_ident_size(const size_t area_size)
{
	if (area_size <= BLOCK_TINY_LIMIT)
		return (PAGE_TINY_SIZE);
	else if (area_size <= BLOCK_SMALL_LIMIT)
		return (PAGE_SMALL_SIZE);
	else if (area_size + STRUCT_PAGE_SIZE + STRUCT_BLOCK_SIZE < area_size)
	{
		dprintf(2, "Error: overflow occured in [%s]\n", __func__);
		return (0);
	}
	return (area_size + STRUCT_PAGE_SIZE + STRUCT_BLOCK_SIZE);
}

static void	page_init(t_page *page, const size_t page_size, const size_t block_size)
{
	memset(page, 0, STRUCT_PAGE_SIZE);
	page->type = page_ident_type(block_size);
	page->size = page_size;
	page->avail_size = page_size - STRUCT_PAGE_SIZE - STRUCT_BLOCK_SIZE; // удалить потом
	page->block_head = block_add(PAGE_UNUSED_ADDR(page), page_size - STRUCT_PAGE_SIZE - STRUCT_BLOCK_SIZE);
	page->block_head->page_head = page;
	dbg_block(page->block_head);
}

/*
** page_create():
**
** 1. page_indent_size:
** определяем тип страницы в зависимости
** от размера запрашиваемого участка памяти
**
** 2. allocate_memory:
** выделяем область памяти под страницу
**
** 3. page_init:
** инициализируем страницу начальными параметрами
**
** 4. main_page_update:
** обновляем указатель в main_page на 'свежий' указатель
*/

t_page	*page_create(const size_t block_size)
{
	t_page	*page;
	size_t	page_size;

	page_size = page_ident_size(block_size);
	if (!page_size)
		return (NULL);
	page = (t_page *)allocate_memory(page_size);
	if (!page)
		return (NULL);
	page_init(page, page_size, block_size);
	main_page_update(page);
	return (page);
}

/*
** page_get_current_by_type():
**
** 1. main_page_get:
** получаем main_page (static)
**
** 2.
** функция возвращает указатель на тип страницы в зависимости
** от размера запрашиваемого участка памяти
** BLOCK_TINY_LIMIT <= 128
** BLOCK_SMALL_LIMIT <= 1024
** BLOCK_LARGE_LIMIT > 1024
** может вернуть NULL, если t_main_page только инициализировалась
** и до этого не было вызовов page_get_available
*/

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

/*
** page_get_available():
**
** 1. page_get_current_by_type:
** возвращает текущую страницу в зависимости
** от размера запрашиваемой памяти (area_size)
**
** 2. page_create:
** если страница не найдена - пытаемся создать
*/

t_page	*page_get_available(const size_t block_size)
{
	t_page	*page;

	page = page_get_current_by_type(block_size);
	if (!page)
	{
		page = page_create(block_size);
		if (!page)
			return (NULL);
	}
	return (page);
}

// page_init
// printf("--------------------------------\n");
// printf("in: %s\n", __func__);
// printf("created new page, type:   %s\n", page->type == E_LARGE? "LARGE" : page->type == E_SMALL? "SMALL" : "TINY");
// printf("page size:                %lu\n", page->size);
// printf("page struct size:         %lu\n", STRUCT_PAGE_SIZE);
// printf("first block struct size:  %lu\n", STRUCT_BLOCK_SIZE);
// printf("first block size:         %lu\n", page->block_head->size);
// printf("page avail size:          %lu\n", page->avail_size);
// printf("--------------------------------\n");