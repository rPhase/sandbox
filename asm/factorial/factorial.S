# # int32_t factorial(int32_t n)
# # {
# #   return (n>0) ? (n*factorial(n-1)) : 1;
# # }

oldEbp = 0
retAddr = oldEbp + 4
n = retAddr + 4

.global factorial
factorial:
  #prologue
  pushl %ebp
  movl %esp, %ebp
  pushl n(%ebp)

  #check if current number is > 0
  cmpl $0, (%esp)
  jz _endCall
  subl $1, (%esp)
  call factorial
  mull n(%ebp)
  jmp _out
  _endCall:
  movl $1, %eax
  _out:
  addl $4, %esp
  movl %ebp, %esp
  popl %ebp
  ret
