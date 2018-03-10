.global _start
.data
L1:
  .word 0xabba
  .byte 0xaa
L2:
  .int  0xabbaaabb
L3:
  .byte 0xbb, 0xaa, 0xab, 0xba
.text
_start:
  movl L2+2,%eax
  movw L1+1,%ax
testHere:
  nop          # at this point, register eax should have a value of
               # 2864425643 as an unsigned decimal number
  movl $1,%eax
  movl $0,%ebx
  int  $0x80
