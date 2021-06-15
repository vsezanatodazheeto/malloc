#include <stdint.h>
#include "malloc.h"

#define QT 25
#define SIZE 1024

void *p[QT];
size_t size = SIZE;

// malloc

int main()
{
	printf("-------------------------------------------------------------------------------------------------------\n");
	printf("Выделение памяти, освобождение, 'дефрагментация', ошибки\n");
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

	printf("\nОсвобождаем каждый четный\n\n");

	for (int i = 0; i < QT; i++)
	{
		if (i % 2)
			free(p[i]);
	}
	show_alloc_mem();

	printf("\nОсвобождаем под индексом #3 (1024 * 3 + (2 * 40 (два пустых мета блока)) == 3152 \n\n");
	free(p[2]);
	show_alloc_mem();

	printf("\nОсвобождаем все, кроме первого\n\n");
	for (int i = 1; i < QT; i++)
	{
		if (!(i % 2) && i != 2) 
			free(p[i]);
	}
	show_alloc_mem();

	printf("\nПробуем освободить неаллоцированный указатель\n\n");
	free(p[1]);

	exit(0);
}
