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
	area_size = area_size_align(area_size);
	if (!area_size)
		return (NULL);

	// получаем страничку памяти для блоков типа t_page
	page = page_get_available(area_size);

	block = block_get_available(page, area_size);
	if (!block)
	{
		if (g_e_rewrite)
		{
			dprintf(2, "Error: block rewriting detected");
			dprintf(2, " at [%p], stop work\n", g_e_rewrite);
			return (NULL);
		}
		page = page_create(area_size);
		block = block_get_available(page, area_size);
		if (!block)
			return (NULL);
		// printf("СТРАНИЧКА ЗАКОНЧИЛАСЬ !!!!!!!\n");
	}
	return ((t_v)BLOCK_LAST_ADDR(block, 0));
}
