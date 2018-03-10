# implement the logic to find the maximum of eax, ebx and ecx, then store 
# it in edx
# # in case you need a refresher, one way to implement this logic is
# # if (eax >= ebx) and (eax >= ecx)
# #   edx = eax
# # else if (ebx >= eax) and (ebx >= ecx)
# #   edx = ebx
# # else
# #   edx = ecx
#
# # in case you need to know whether the numbers to be processed are signed or not, they are not

.text
.global _start
_start:
L1:
  nop  # you may remove this instruction 
	cmpl %eax, %ecx
	jnl _ELSE
	cmpl %eax, %ebx
	jnl _ELSE
	movl %eax, %edx
	jmp _OUT
	_ELSE:
	cmpl %ebx, %ecx
	jnl _ELSE2
	cmpl %ebx, %eax
	jnl _ELSE2
	movl %ebx, %edx
	jmp _OUT
	_ELSE2:
	movl %ecx, %edx
	_OUT:
# put your code here between L1 and L2, do not change the rest of the program!

L2:
  movl $1,%eax
  movl $0,%ebx
  int  $0x80
