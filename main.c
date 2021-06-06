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

	p1 = m_malloc(300);
	p2 = m_malloc(400);
	p3 = m_malloc(500);
	p4 = m_malloc(600);
	p5 = m_malloc(700);
	// p6 = m_malloc(800);
	// p7 = m_malloc(900);
	// p8 = m_malloc(1000);
	// p9 = m_malloc(2000);

	m_free(p4);

	page = page_get_current_by_type(300);
		page = page_get_current_by_type(300);
	for (block = page->block_head; block; block = block->next)
		printf("%d: %p %zu\n", block->avail ? 1:0, (void *)block, block->size);
	printf("-----------------------\n");
	m_free(p5);

	page = page_get_current_by_type(300);
	for (block = page->block_head; block; block = block->next)
		printf("%d: %p %zu\n", block->avail ? 1:0, (void *)block, block->size);
	printf("-----------------------\n");

	// dbg_gfinfo(E_SMALL);

	return (0);
}
