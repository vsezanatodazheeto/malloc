#include "include/malloc.h"
#include <stdint.h>

// 8192
// 65536

int			main(int ac, char **kek)
{
	t_page *page;
	t_block *block;
	void	*p1 = NULL, *p2 = NULL, *p3 = NULL, *p4 = NULL, *p5 = NULL, \
			*p6 = NULL, *p7 = NULL, *p8 = NULL, *p9 = NULL, *p10 = NULL, \
			*p11 = NULL, *p12 = NULL, *p13 = NULL, *p14 = NULL, *p15 = NULL, \
			*p16 = NULL, *p17 = NULL;

	printf("new\n");
	if (!(p1 = m_malloc(1073741824L)))
	{
		printf("KEKEKE\n");
		exit(0);
	}
	else
		memset(p1, 'c', 1073741824L);

	sleep(10);
	printf("new\n");
	if (!(p2 = m_malloc(1073741824L)))
	{
		printf("KEKEKE\n");
		exit(0);
	}
	else
		memset(p2, 'c', 1073741824L);

	sleep(10);
	printf("new\n");
	if (!(p3 = m_malloc(1073741824L)))
	{
		printf("KEKEKE\n");
		exit(0);
	}
	else
		memset(p3, 'c', 1073741824L);

	sleep(10);
	printf("new\n");
	if (!(p4 = m_malloc(1073741824L)))
	{
		printf("KEKEKE\n");
		exit(0);
	}
	else
		memset(p4, 'c', 1073741824L);

	sleep(10);
	printf("new\n");
	if (!(p5 = m_malloc(1073741824L)))
	{
		printf("KEKEKE\n");
		exit(0);
	}
	else
		memset(p5, 'c', 1073741824L);

	sleep(10);
	printf("new\n");
	if (!(p6 = m_malloc(1073741824L)))
	{
		printf("KEKEKE\n");
		exit(0);
	}
	else
		memset(p6, 'c', 1073741824L);

	sleep(10);
	printf("new\n");
	if (!(p7 = m_malloc(1073741824L)))
	{
		printf("KEKEKE\n");
		exit(0);
	}
	else
		memset(p7, 'c', 1073741824L);

	sleep(10);
	printf("new\n");
	if (!(p8 = m_malloc(1073741824L)))
	{
		printf("KEKEKE\n");
		exit(0);
	}
	else
		memset(p8, 'c', 1073741824L);

	sleep(10);
	printf("new\n");
	if (!(p9 = m_malloc(1073741824L)))
	{
		printf("KEKEKE\n");
		exit(0);
	}
	else
		memset(p9, 'c', 1073741824L);

	sleep(10);
	printf("new\n");
	if (!(p10 = m_malloc(1073741824L)))
	{
		printf("KEKEKE\n");
		exit(0);
	}
	else
		memset(p10, 'c', 1073741824L);

	sleep(10);
	printf("new\n");
	if (!(p11 = m_malloc(1073741824L)))
	{
		printf("KEKEKE\n");
		exit(0);
	}
	else
		memset(p11, 'c', 1073741824L);


	sleep(10);
	printf("new\n");
	if (!(p12 = m_malloc(1073741824L)))
	{
		printf("KEKEKE\n");
		exit(0);
	}
	else
		memset(p12, 'c', 1073741824L);

	sleep(10);
	printf("new\n");
	if (!(p13 = m_malloc(1073741824L)))
	{
		printf("KEKEKE\n");
		exit(0);
	}
	else
		memset(p13, 'c', 1073741824L);

	sleep(10);
	printf("new\n");
	if (!(p14 = m_malloc(1073741824L)))
	{
		printf("KEKEKE\n");
		exit(0);
	}
	else
		memset(p14, 'c', 1073741824L);

	sleep(10);
	printf("new\n");
	if (!(p16 = m_malloc(1073741824L)))
	{
		printf("KEKEKE\n");
		exit(0);
	}
	else
		memset(p16, 'c', 1073741824L);

	sleep(10);
	printf("new\n");
	if (!(p17 = m_malloc(1073741824L)))
	{
		printf("KEKEKE\n");
		exit(0);
	}
	else
		memset(p17, 'c', 1073741824L);

	if (p1 && p2 && p3 && p4 && p5 && p6 && p7 && p8 && p9 && p10 && p11 && p12 && p13 && p14 && p15 && p16 && p17)
	{
		printf("suka\n");
	}

	dbg_gfinfo(E_LARGE);
	return (0);
}
