#include <stdint.h>
#include <stdio.h>

extern int32_t factorial(int32_t);
int32_t main(void)
{
  printf("factorial returns %d\n",factorial(10)); 
  return 0;
}
