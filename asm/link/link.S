# # int32_t link(int32_t n)
# # {
# #   return n+n;
# # }
.global link
link:
  movl 4(%esp), %eax
  addl %eax, %eax
  ret

