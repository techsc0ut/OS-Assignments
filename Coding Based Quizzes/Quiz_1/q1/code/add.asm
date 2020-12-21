section .text

	global _start
	global checkGreater

_start:
 	call checkGreater
	
	mov rax,60	 ;This is the structure for calling System_exit Call, where the ID is Pre-defined as 60.	  	
	mov rdi,0        ;0 conveys successful execution with no errors.		syscall
	ret


checkGreater:
	cmp rdi,rsi
	jg  print1
	call print0
	ret


print1:
	mov rax, 1        
  	mov rdi, 1        
  	mov rsi, msg1     
  	mov rdx, msg1len  
  	syscall 
  	ret


print0:
	mov rax, 1         
  	mov rdi, 1        
  	mov rsi, msg0      
  	mov rdx, msg0len   
  	syscall 
  	ret 


section .rodata
  msg1: db "1", 10
  msg1len: equ $ - msg1
  msg0: db "0", 10
  msg0len: equ $ -msg0




  

