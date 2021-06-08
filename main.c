#include "include/malloc.h"
#include <stdint.h>

// 8192
// 65536

int			main(int ac, char **kek)
{
	t_page *page;
	t_block *block;
	void	*p1 = NULL, *p2 = NULL, *p3 = NULL, *p4 = NULL, *p5 = NULL, \
			*p6 = NULL, *p7 = NULL, *p8 = NULL, *p9 = NULL;

	// p1 = m_malloc(18446744073709551615);
	// p1 = m_malloc(300);
	// p2 = m_malloc(400);
	// p3 = m_malloc(500);
	// p4 = m_malloc(600);
	// p5 = m_malloc(700);

	// p6 = m_malloc(8000);
	// p6 = m_malloc(8001);
	// p7 = m_malloc(9000);
	// p8 = m_malloc(10000);
	// p9 = m_malloc(20000);

	// m_free(p4);

	
	while (1)
	{
		if (!(p1 = m_malloc(1073741824 * 16)))
		{
			printf("KEKEKE\n");
			exit(0);
		}
		else
		{
			printf("ohuet\n");
		}
	}
	// for (page = page_get_current_by_type(3000) ;page; page = page->next)
	// 	printf("%zu\n", page->size);

	// for (page = page_get_current_by_type(3000) ;page; page = page->next)
	// 	printf("%zu\n", page->size);
	// 	page = page_get_current_by_type(300);
	// for (block = page->block_head; block; block = block->next)
	// 	printf("%d: %p %zu\n", block->avail ? 1:0, (void *)block, block->size);
	// printf("-----------------------\n");
	// m_free(p5);

	// page = page_get_current_by_type(300);
	// for (block = page->block_head; block; block = block->next)
	// 	printf("%d: %p %zu\n", block->avail ? 1:0, (void *)block, block->size);
	// printf("-----------------------\n");

	dbg_gfinfo(E_TINY);
	// dbg_gfinfo(E_SMALL);
	// dbg_gfinfo(E_LARGE);

	printf("%zu\n", sizeof(int));
	printf("%llu\n", UINTMAX_MAX);

	// malloc(sizeof(int) * 1);
	return (0);
}
