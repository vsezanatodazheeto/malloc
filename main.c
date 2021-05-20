// #include "include/malloc.h"
// #include <stdint.h>

// // 8192
// // 65536

// int			main()
// {
// 	void *p1 = NULL;
// 	void *p2 = NULL;

// 	// if (!(p1 = m_malloc(-1)))
// 		// ;
// 		// exit(1);
// 	if (!(p1 = m_malloc(7)))
// 		;
// 		// exit(1);
// 	free(NULL);
// 	// m_free((void*)123);
// 	// m_free((void*)123);

// 	// dbg_gfinfo(E_TINY);
// 	// dbg_gfinfo(E_SMALL);
// 	// dbg_gfinfo(E_LARGE);
// 	return (0);
// }


#include <iostream>
#include <cmath>
using namespace std;
bool isMulOverflow(long long A, long long B) {
   if (A == 0 || B == 0)
      return false;
   long long result = A * B;
   if (A == result / B)
      return false;
   else
      return true;
}
int main() {
//    long long a = 10000000000 , b = -10000000000;
   long long a = 10000000000 , b = 10;
   if(isMulOverflow(a, b)){
      cout <<"It will overflow";
   }
   else{
      cout <<"It will not overflow";
   }
}


В противном случае, если произведение двух, разделенного на одно, равно другому, то оно не будет превышать 