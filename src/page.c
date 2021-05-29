#include "../include/malloc.h"

static t_page_type	page_ident_type(const size_t area_size)
{
	if (area_size <= (BLOCK_TINY_LIMIT))
		return (E_TINY);
	else if (area_size <= (BLOCK_SMALL_LIMIT))
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

/*
** page_ident_size():
**
** возвращает размер страницы в зависимости от количества запрашиваемой памяти
** если это не TINY и не SMALL, то проверяем на переполнение
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

	if (!(page_size = page_ident_size(block_size)))
		return (NULL);
	if (!(page = (t_page *)alloc_memory(page_size)))
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
** возвращает текущую страницу в зависимости от размера запрашиваемой памяти (area_size)
**
** 2. page_create:
** если страница не найдена - пытаемся создать
*/

t_page	*page_get_available(const size_t block_size)
{
	t_page	*page;

	if (!(page = page_get_current_by_type(block_size)))
	{
		if (!(page = page_create(block_size)))
			return (NULL);
	}
	return (page);
}
