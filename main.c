#include "include/malloc.h"
#include <stdint.h>

// 8192
// 65536

int			main(int ac, char **kek)
{
	void *p1 = NULL;
	void *p2 = NULL;
	void *p3 = NULL;
	void *p4 = NULL;
	void *p5 = NULL;
	void *p6 = NULL;
	void *p7 = NULL;
	void *p8 = NULL;
	void *p9 = NULL;

	t_main_page *mp = main_page_get();
	t_page *p;
	int i = 1;

	p1 = m_malloc(3000);
	p2 = m_malloc(4000);
	p3 = m_malloc(5000);
	p4 = m_malloc(6000);
	p5 = m_malloc(7000);
	p6 = m_malloc(8000);
	p7 = m_malloc(9000);
	p8 = m_malloc(10000);
	p9 = m_malloc(20000);

	for (p = mp->large_head; p; i++, p = p->next)
		printf("%d: %lu\n", i, p->size);
	i = 1;
	printf("------------------------\n");

	m_free((void*)p4);
	m_free((void*)p5);

	for (p = mp->large_head; p; i++, p = p->next)
		printf("%d: %lu\n", i, p->size);
	i = 1;
	printf("------------------------\n");

	// dbg_count_pages(E_LARGE);
	// m_free((void*)p2);
	// dbg_count_pages(E_LARGE);
	// m_free((void*)p3);
	// dbg_count_pages(E_LARGE);
	// dbg_gfinfo(E_TINY);
	// dbg_gfinfo(E_SMALL);
	// dbg_gfinfo(E_LARGE);
	return (0);
}
