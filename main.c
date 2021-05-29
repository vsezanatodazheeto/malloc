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

	t_main_page *mp = main_page_get();
	t_page *p;

	// if (!(p1 = m_malloc(0)))
		// ;
	if (!(p1 = m_malloc(5000)))
		;
	if (!(p2 = m_malloc(6001)))
		;
	if (!(p3 = m_malloc(7002)))
		;
	if (!(p4 = m_malloc(3002)))
		;
	if (!(p5 = m_malloc(17002)))
		;

	m_free((void*)p4);
	m_free((void*)p5);

	for (p = mp->large_head; p; p = p->next)
		printf("%lu\n", p->size);
	printf("------------------------\n");
	for (p = mp->large_last; p; p = p->prev)
		printf("%lu\n", p->size);

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
