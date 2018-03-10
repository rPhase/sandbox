#include <stdio.h>
#include <stdlib.h>
#include "node.h"

struct Node *makeNode(unsigned int v);
#if 0
struct Node *makeNode(int v)
{
  struct Node *ptr;
  ptr = (struct Node *)malloc(sizeof(struct Node));
  ptr->value = v;
  ptr->pNext = 0;
  return ptr;
}
#endif

void printList(struct Node **pList);
#if 0
void printList(struct Node **pList)
{
  if (*pList == 0)
  {
  }
  else
  {
    printf("%u\n",(*pList)->value);
    printList(&((*pList)->pNext));
  }
}
#endif

void insertIntoList(struct Node **pList, unsigned int u);
#if 0
void insertIntoList(struct Node **pList, unsigned int u)
{
  if (*pList == 0)
  {
    *pList = makeNode(u);
  }
  else if ((*pList)->value == u)
  {
  }
  else if ((*pList)->value > u)
  {
    struct Node *tmp = (*pList);
    *pList = makeNode(u);
    (*pList)->pNext = tmp;
  }
  else
  {
    insertIntoList(&((*pList)->pNext),u);
  }
}
#endif

int main(void)
{
  struct Node *list;
  unsigned int u;
  list = 0;

  while (scanf("%u",&u) == 1)
  {
    insertIntoList(&list, u);
  }
  printList(&list);
  return 0;
}
