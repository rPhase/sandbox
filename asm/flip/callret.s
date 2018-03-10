.global _start
# void f(void)
# {
# }
f: 
  nop
  nop
  ret


# void g(void)
# {
#   f();
# }

g:
  call f
  nop
  nop
  ret

#  int main(void)
#  {
#    g();
#  }
_start:
  call g
  nop
  nop
  
  movl $1,%eax
  movl $0,%ebx
  int $0x80
