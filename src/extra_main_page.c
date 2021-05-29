#include "../include/malloc.h"

void	*alloc_memory(const size_t page_size)
{
	void	*data_memory;

	data_memory = mmap(NULL, \
						page_size, \
						PROT_READ | PROT_WRITE, \
						MAP_PRIVATE | MAP_ANON, \
						-1, \
						0);
	if (data_memory == MAP_FAILED)
		return (NULL);
	return (data_memory);
}

/*
** area_size_align():
**
** делаем выравнивание area_size в зависимости от разрядности, проверяем на переполнение
*/

size_t	area_size_align(size_t area_size)
{
	if (((((area_size - 1) / BITW) * BITW) + BITW) < area_size)
	{
		dprintf(2, "Error: overflow occured in [%s]\n", __func__);
		return (0);
	}
	return ((((area_size - 1) / BITW) * BITW) + BITW);
}

static void	main_page_update_extra(t_page **page_last, t_page *page_new)
{
	if (*page_last)
	{
		(*page_last)->next = page_new;
		page_new->prev = *page_last;
	}
	*page_last = page_new;
}

void	main_page_update(t_page *page)
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
** main_page_get():
**
** Возвращает адрес статической структуры, которая хранит информацию о страницах разных типов
*/

t_main_page	*main_page_get(void)
{
	static t_main_page	main_page;

	return (&main_page);
}
