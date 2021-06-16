#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "malloc.h"

#define QT 3
#define SIZE 1024

void *p[QT];
size_t size = SIZE;

// malloc

int main()
{
	printf("-------------------------------------------------------------------------------------------------------\n");
	printf("Выделение памяти, реаллокация памяти\n");
	printf("-------------------------------------------------------------------------------------------------------\n\n\n");
	fflush(stdout);

	for (int i = 0; i < QT; i++)
	{
		if (!(p[i] = malloc(size)))
		{
			show_alloc_mem();
			printf("stopped on: %d\nmalloc returns NULL\n", i);
			fflush(stdout);
			exit(0);
		}
		else
			memset(p[i], 'a', size);
	}
	show_alloc_mem();
	exit(0);
}
