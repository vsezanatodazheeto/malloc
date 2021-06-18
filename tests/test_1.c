#include "test.h"
#include "malloc.h"

#define QT 25
#define SIZE 1024

void *p[QT];
size_t size = SIZE;

// malloc

int main()
{
	printf("-------------------------------------------------------------------------------------------------------\n");
	printf("Выделение памяти\n");
	printf("-------------------------------------------------------------------------------------------------------\n\n\n");

	for (int i = 0; i < QT; i++)
	{
		if (!(p[i] = malloc(size)))
		{
			show_alloc_mem();
			printf("stopped on: %d\nmalloc returns NULL\n", i);
			exit(0);
		}
		else
			memset(p[i], 'a', size);
	}

	show_alloc_mem();
	printf("\nЗаписываем в 3-й индекс больше, чем выделели, пытаемся аллоцировать новый блок после этого\n\n");
	fflush(stdout);
	memset(p[2], 'a', size * 2);
	p[1] = malloc(size);

	show_alloc_mem();
	exit(0);
}
