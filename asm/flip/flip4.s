.global _start
_start:
  pushw $0
  movl $3,%eax
  movl $0,%ebx
  movl %esp,%ecx
  movl $1,%edx
  int  $0x80
  
  pushw $0
  movl $3,%eax
  movl $0,%ebx
  movl %esp,%ecx
  movl $1,%edx
  int  $0x80

  pushw $0
  movl $3,%eax
  movl $0,%ebx
  movl %esp,%ecx
  movl $1,%edx
  int  $0x80

  pushw $0
  movl $3,%eax
  movl $0,%ebx
  movl %esp,%ecx
  movl $1,%edx
  int  $0x80

  movl $4,%eax
  movl $1,%ebx
  movl %esp,%ecx
  movl $1,%edx
  int  $0x80

  popw %ax
  movl $4,%eax
  movl $1,%ebx
  movl %esp,%ecx
  movl $1,%edx
  int  $0x80

  popw %ax
  movl $4,%eax
  movl $1,%ebx
  movl %esp,%ecx
  movl $1,%edx
  int  $0x80

  popw %ax
  movl $4,%eax
  movl $1,%ebx
  movl %esp,%ecx
  movl $1,%edx
  int  $0x80

  popw %ax

  movl $1,%eax
  movl $0,%ebx
  int $0x80
