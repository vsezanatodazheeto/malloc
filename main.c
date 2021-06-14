#include "include/malloc.h"
#include <stdint.h>

// 8192
// 65536
# define QT 25

int			main(int ac, char **kek)
{
	t_page *page;
	t_block *block;
	void	*p[QT] = {};
	size_t size;

	size = 1;
	for (int i = 0; i < QT; i++)
	{
		if (!(p[i] = m_malloc(size)))
		{
			printf("NO MEMES");
			break ;
		}
		else
			memset(p[i], 'c', size);
		size = size + size;
		// show_alloc_mem();
	}
	// m_free(p[2]);
	// m_malloc(32);
	show_alloc_mem();

	// 199 блоков tiny
	// 390 small

	// printf("%zu\n", STRUCT_BLOCK_SIZE); 
	// printf("%zu\n", PAGE_TINY_SIZE);
	// printf("%zu\n", PAGE_SMALL_SIZE);

	// printf("%zu\n", STRUCT_PAGE_SIZE);
	return (0);
}
