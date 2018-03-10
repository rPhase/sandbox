#include "node.inc"

oldEbp = 0
retAddr = oldEbp + 4
pList = retAddr + 4
fmt: .asciz "%u\n"
.global printList
printList:
  pushl %ebp
  movl %esp, %ebp
# #if (*pList == 0)
  movl pList(%ebp), %eax ## **pList
  cmpl $0, (%eax)        ##*pList
  jz _endIf

# #else
# #printf("u\n",(*pList)->value);

#  pushl (%eax)
#  popl %eax
  movl (%eax), %eax
  pushl Node_value(%eax)
  pushl $fmt
  call printf
  addl $8, %esp

# #printList(&((*pList)->pNext));
  movl pList(%ebp), %eax
  pushl (%eax)
  addl $Node_pNext, (%esp)
  call printList
  addl $4, %esp

_endIf:
  movl %ebp, %esp
  popl %ebp
  ret
