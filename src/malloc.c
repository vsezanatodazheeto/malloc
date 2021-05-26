#include "../include/malloc.h"

// переменная для того, чтобы узнать, был ли блок перезаписан (пропали данные)
// пока что так
void	*g_e_rewrite;

void	*allocate_memory(const size_t page_size)
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
** делаем выравнивание area_size в зависимости от разрядности
** проверяем на переполнение
** формула выравнивания честно спизжена из интернетов
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

/*
** realloc() меняет размер блока памяти, на который указывает ptr,
** на размер, равный size байтов. 
** Содержание будет неизменным в пределах наименьшего из старых и новых размеров,
** а новая распределенная память будет неинициализирована.
** Если ptr равно NULL, то данный вызов эквивалентен malloc(size);
** если размер равен нулю, то данный вызов эквивалентен free(ptr).
** Если только ptr не равен NULL, он, по-видимому, возвращен более ранним
** вызовом malloc(), calloc() или realloc().   
*/

/*
** realloc() возвращает указатель на память,
** которая должным образом повторно распределена для каждого типа переменных
** и может отличаться от ptr, или возвращает NULL, если запрос завершился с
** ошибкой.
** Если size был равен нулю, то возвращается либо NULL, либо указатель,
** который может быть передан free().
** Если realloc() не выполнена, то блок памяти остается нетронутым: он
** не "очищается" и не перемещается.
*/

void	*m_realloc(void *ptr, size_t size)
{
	t_page	*page;
	t_block	*block;

	if (!ptr)
	{
		return (m_malloc(size));
		// тут почитать man, по-моему просто нужно вызвать malloc
	}
	// page = free_page_validation(ptr);
	// if (!page)
	// 	return ;
	// block = free_block_validation(page, ptr);
	// if (!block)
	// 	return ;
	return (NULL);
}

void	*m_calloc(size_t nmemb, size_t memb_size)
{
	void	*area;
	size_t	size;

	if (!nmemb || !memb_size)
		return (NULL);
	size = nmemb * memb_size;
	if (size / memb_size != nmemb)
	{
		dprintf(2, "Error: overflow occured in [%s]\n", __func__);
		return (NULL);
	}
	area = m_malloc(size);
	if (!area)
		return (NULL);
	memset(area, 0, size);
	return (area);
}

/*
** 1. area_size_align:
** выравнивание будущей области памяти (area_size)
**
** 2. page_get_available:
** получаем текущую страницу нужного типа
** с/без блоками/блоков для размешения нового блока
*/

void	*m_malloc(size_t area_size)
{
	t_page	*page;
	t_block	*block;

	// делаем выравнивание
	if (!(area_size = area_size_align(area_size)))
		return (NULL);
	// получаем страничку памяти для блоков типа t_page
	page = page_get_available(area_size);
	if (!(block = block_get_available(page, area_size)))
	{
		if (g_e_rewrite)
		{
			dprintf(2, "Error: block rewriting detected");
			dprintf(2, " at [%p], stop work\n", g_e_rewrite);
			return (NULL);
		}
		page = page_create(area_size);
		if (!(block = block_get_available(page, area_size)))
			return (NULL);
		// printf("СТРАНИЧКА ЗАКОНЧИЛАСЬ !!!!!!!\n");
	}
	return ((t_v)BLOCK_LAST_ADDR(block, 0));
}
