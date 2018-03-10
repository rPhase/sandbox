# implement the code in flip.c
.text
.global _start

g:
  pushw $0
  #read(0, &ch, 1);
	movl $3, %eax # system service 3, file read
	movl $0, %ebx # file descriptor 0, stdin
	movl %esp, %ecx # where to store the characters read
	movl $1, %edx #request to read 1 byte
	int $0x80 #request to perform operation
  
	cmpl $0, %eax
  jz _endIf
	
	call g
	# write(1, &ch, 1);
	movl $4,%eax           # system call 4 
	movl $1,%ebx           # stdout 
	movl %esp,%ecx      # where in memory to write from 
	movl $1,%edx           # the number of characters to write 
	int  $0x80             # request the OS to do it 
	
	_endIf:
	popw %ax
	ret
	
_start:
  call g
	


  movl $1,%eax
  movl $0,%ebx
  int  $0x80
