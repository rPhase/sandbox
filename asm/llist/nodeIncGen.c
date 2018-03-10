#include <stdio.h>
#include "node.h"

int main(void)
{
  struct Node n;
  printf("Node_pNext = %u\n",(void*)&n.pNext - (void*)&n);
  printf("Node_value = %u\n",(void*)&n.value - (void*)&n);
  printf("Node_size = %u\n",sizeof(struct Node));
  return 0;
}
