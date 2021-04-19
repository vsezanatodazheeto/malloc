#include "malloc.h"
#include <stdint.h>

// 8192
// 65536

int			main()
{
	void *p1 = NULL;
	void *p2 = NULL;

	// if (!(p1 = m_malloc(-1)))
		// ;
		// exit(1);
	if (!(p1 = m_malloc(7)))
		;
		// exit(1);
	// dbg_gfinfo(E_TINY);
	// dbg_gfinfo(E_SMALL);
	// dbg_gfinfo(E_LARGE);
	return (0);
}
