#include "node.inc"
.global makeNode
oldEbp = 0
retAddr = oldEbp + 4
v = retAddr + 4
ptr = oldEbp - 4
makeNode:
  pushl %ebp
  movl  %esp,%ebp
  addl  $ptr,%esp

  pushl $Node_size
  call  malloc
  addl  $4,%esp

  movl  %eax,ptr(%ebp)
  pushl v(%ebp)
  popl  Node_value(%eax)
  movl  $0,Node_pNext(%eax)

  movl  %ebp,%esp
  popl  %ebp
  ret
