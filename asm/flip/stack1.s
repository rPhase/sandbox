.global _start
_start:
  pushl $0xabcd1234
  movl  $0,%eax
  popl  %eax

  movl  $1,%eax
  movl  $0,%ebx
  int   $0x80
