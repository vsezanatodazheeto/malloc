#include "malloc.h"
// #include <stdio.h>

int main()
{
	void *p;

	p = malloc(100);
	p = malloc(100);
	p = malloc(100);
	p = malloc(100);
	p = malloc(100);
	p = malloc(100);
	p = malloc(10000);
	p = malloc(10000);
	p = malloc(10000);
	p = malloc(10000);
	p = malloc(10000);
	show_alloc_mem();
	return (0);
}
