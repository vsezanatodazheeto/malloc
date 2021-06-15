#include "include/malloc.h"

int main()
{
    void *p1;
    t_block *block;

    p1 = malloc(1);

    block = BLOCK_FIRST_ADDR(p1);

    show_alloc_mem();
    for (; block; block = block->next)
        printf("%p\n", (t_v)block);
    return (0);
}