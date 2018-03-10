#include <stdint.h>
#include <stdio.h>

extern int32_t link(int32_t);
int32_t main(void)
{
  printf("link returns %d\n",link(10)); 
  return 0;
}
