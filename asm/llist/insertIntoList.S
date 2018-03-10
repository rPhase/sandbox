#include "node.inc"

oldEbp = 0
retAddr = oldEbp + 4
pList = retAddr + 4
u = pList + 4

.global insertIntoList
insertIntoList:
  pushl %ebp
  movl %esp, %ebp

# #if (*pList == 0)
  movl pList(%ebp), %eax ## **pList
  cmpl $0, (%eax)        ##*pList
  jnz _elseIf1

# #*pList = makeNode(u);
# # movl u(%ebp), %eax
  pushl u(%ebp)
  call makeNode
  addl $4, %esp
  pushl %eax
  movl pList(%ebp), %eax
  popl (%eax)
  jmp _endIf
_elseIf1:
# #if ((*pList)->value == u)
  movl (%eax), %eax
  movl Node_value(%eax), %eax
  cmpl %eax, u(%ebp)
  jnz _elseIf2
  jmp _endIf
_elseIf2:

# #if ((*pList)->value > u)
  cmpl u(%ebp), %eax
  jna _else
# #struct Node *tmp = (*pList);
  movl pList(%ebp), %eax
  pushl (%eax)

# #*pList = makeNode(u);
  pushl u(%ebp)
  call makeNode
  addl $4, %esp
  pushl %eax
  movl pList(%ebp), %eax
  popl (%eax)
  movl (%eax), %eax
  popl Node_pNext(%eax)
  jmp _endIf

_else:
# # insertIntoList(&((*pList)->pNext), u)
  pushl u(%ebp)
  movl pList(%ebp), %eax
  pushl (%eax)
  addl $Node_pNext, (%esp)
  call insertIntoList
  addl $8, %esp


_endIf:
  movl %ebp, %esp
  popl %ebp
  ret
