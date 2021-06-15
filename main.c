#include "include/malloc.h"
#include <string.h>
#include <limits.h>

int main()
{
    void *p1, *p2, *p3;
    t_block *block;

    p1 = malloc(1);
    p2 = malloc(1);
    p3 = malloc(1);

    free(p3 + 400);
    memset(p1, 'a', 3);
    free(p3);
    show_alloc_mem();
    return (0);
}