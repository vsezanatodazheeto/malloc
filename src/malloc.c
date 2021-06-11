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

// calloc:
// overflow check
// call malloc
// fill by zero the memory area

void	*m_calloc(size_t nmemb, size_t memb_size)
{
	void	*area;
	size_t	size;

	area = NULL;
	if (nmemb && memb_size)
	{
		size = nmemb * memb_size;
		if (size / memb_size != nmemb)
			dprintf(2, "Error: overflow occurred, size is too big\n");
		else if ((area = m_malloc(size)))
			memset(area, 0, size);
	}
	return (area);
}

// malloc:
// overflow check
// get the current or create a page of the required type
// looking for a available block

void *m_malloc(size_t area_size)
{
	t_page *page;
	t_block	*block;

	if (area_size + STRUCT_PAGE_SIZE + STRUCT_BLOCK_SIZE < area_size)
		dprintf(2, "Error: overflow occurred, size is too big\n");
	else
	{
		if ((page = page_get_available(area_size)))
		{
			if ((block = block_get_available(page, area_size)))
				return ((t_v)BLOCK_LAST_ADDR(block, 0));
		}
	}
	return (NULL);
}

// realloc() меняет размер блока памяти, на который указывает ptr, на размер, равный size байтов.
// Содержание будет неизменным в пределах наименьшего из старых и новых размеров,
// а новая распределенная память будет неинициализирована.
// Если ptr равно NULL, то данный вызов эквивалентен malloc(size);
// если размер равен нулю, то данный вызов эквивалентен free(ptr).
// Если только ptr не равен NULL, он, по-видимому, возвращен более ранним вызовом malloc(), calloc() или realloc().  

// realloc() возвращает указатель на память, которая должным образом повторно
// распределена для каждого типа переменных и может отличаться от ptr,
// или возвращает NULL, если запрос завершился с ошибкой.
// Если size был равен нулю, то возвращается либо NULL, либо указатель, который может быть передан free().
// Если realloc() не выполнена, то блок памяти остается нетронутым: он не "очищается" и не перемещается.  










// size_t	area_size_align(size_t area_size)
// {
// 	if (((((area_size - 1) / BITW) * BITW) + BITW) < area_size)
// 	{
// 		dprintf(2, "Error: overflow occured in [%s]\n", __func__);
// 		return (0);
// 	}
// 	return ((((area_size - 1) / BITW) * BITW) + BITW);
// }
