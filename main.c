#include "include/malloc.h"

int main()
{
    void *p1;

    p1 = malloc(5000);
    show_alloc_mem();
    return (0);
}