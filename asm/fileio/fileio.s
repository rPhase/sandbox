# uint32 result;
# uint8 ch;
#
# do
# {
#   result = read(0, &ch, 1);
#   if (result)
#   {
#     if (((ch >= '0') && (ch <= '9')) ||
#         ((ch >= 'a') && (ch <= 'f')))
#     {
#       write(1, &ch, 1);
#     }
#     else if (((ch >= 'A') && (ch <= 'Z')) ||
#              ((ch >= 'a') && (ch <= 'z')))
#     {
#       write(2, &ch, 1);
#     }
#     else
#     {
#       write(3, &ch, 1);
#     }
#   }
# } while (result);

.data
buffer: .fill 1

.text
.global _start
_start:

do_loop:
# result = read(0, &ch, 1);
		movl $3, %eax # system service 3, file read
		movl $0, %ebx # file descriptor 0, stdin
		movl $buffer, %ecx # where to store the characters read
		movl $1, %edx #request to read 1 byte
		int $0x80 #request to perform operation
  
#	if (!result) goto _endLoop;
  cmpl $0, %eax
  jz _endLoop
	
# if (ch < '0') goto next;
  cmpb $48, buffer
  jb next
#  if (ch > '9') goto next;
  cmpb $57, buffer
  ja next
# goto write1;
  jmp write1

  next:
# if (ch < 'a') goto elseIf1;
  cmpb $97, buffer
	jb elseIf1
# if (ch > 'f') goto elseIf1;
  cmpb $102, buffer
	ja elseIf1

  write1:
# write(1, &ch, 1);
		movl $4,%eax           # system call 4 
		movl $1,%ebx           # stdout 
		movl $buffer,%ecx      # where in memory to write from 
		movl $1,%edx           # the number of characters to write 
		int  $0x80             # request the OS to do it 
# goto endIf1;
  jmp endIf1

  elseIf1:
# if (ch < 'A') goto next2;
  cmpb $65, buffer
	jb next2
# if (ch > 'Z') goto next2;
  cmpb $90, buffer
	ja next2
# goto write2;
  jmp write2
  next2:
# if (ch < 'a') goto else2;
  cmpb $97, buffer
	jb else2
# if (ch > 'z') goto else2;
  cmpb $122, buffer
	ja else2

  write2:
# write(2, &ch, 1);
		movl $4,%eax           # system call 4 
		movl $2,%ebx           # stderr 
		movl $buffer,%ecx      # where in memory to write from 
		movl $1,%edx           # the number of characters to write 
		int  $0x80             # request the OS to do it 
# goto endIf1;
  jmp endIf1

  else2:
# write(3, &ch, 1);
		movl $4,%eax           # system call 4 
		movl $3,%ebx           # fd 3
		movl $buffer,%ecx      # where in memory to write from 
		movl $1,%edx           # the number of characters to write 
		int  $0x80             # request the OS to do it 
  
	endIf1:
	# if (result) goto do_loop;
  #cmpl $0, %eax
  #jnz do_loop
  jmp do_loop
 _endLoop:
  
  movl $1,%eax
  movl $0,%ebx
  int  $0x80
