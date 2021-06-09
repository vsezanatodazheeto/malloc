#define _GNU_SOURCE

#include <stdio.h>
#include <dlfcn.h>

void f1(void) {
  printf("f1.");
}

void f2(void) {
  printf("f2.");
}

int main(void) {
	printf("main: f2() -> "); f2(); printf("\n");
	printf("main: f1() -> "); f1(); printf("\n");
	return 0;
}
