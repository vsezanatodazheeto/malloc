#include "include/malloc.h"
#include <stdint.h>

// 8192
// 65536

int			main()
{
	void *p1 = NULL;
	void *p2 = NULL;
	void *p3 = NULL;

	if (!(p1 = m_malloc(0)))
		;
		// exit(1);
	if (!(p1 = m_malloc(7000)))
		;
	if (!(p2 = m_malloc(7000)))
		;
	if (!(p3 = m_malloc(7000)))
		;
		// exit(1);
	// m_free((void*)123);
	m_free((void*)p1);
	dbg_count_pages(E_LARGE);
	m_free((void*)p2);
	dbg_count_pages(E_LARGE);
	m_free((void*)p3);
	dbg_count_pages(E_LARGE);

	// dbg_gfinfo(E_TINY);
	// dbg_gfinfo(E_SMALL);
	// dbg_gfinfo(E_LARGE);
	return (0);
}

// int main()
// {
// 	int i = 4;

// 	if (--i < 4)
// 		printf("ono\n");
// 	else
// 		printf("ne ono\n");
// 	return (0);
// }