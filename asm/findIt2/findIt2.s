.data
L1: .int 0x01101
    .byte 0x01,0x10
    .word 0x10,0x101
L2: .int L2
L3: .byte 0x10, 0x11
.text
.global _start
_start:

  movl L2,%eax    # replace _ (cannot change operand type)
  movl $-2,%ebx   # replace _ (cannot change operand type)
  movl -4(%eax,%ebx,2),%ecx
  movb L3-4(%ebx),%ch

testHere: # ecx should be 0x10010100 at this point

  movl $1,%eax
  movl $0,%ebx
  int  $0x80
