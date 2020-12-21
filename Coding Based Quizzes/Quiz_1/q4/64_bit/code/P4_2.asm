global extended_add

section .text

extended_add:		
	mov rax,[rsp+16]
	add rax,[rsp+24]
	add rax,[rsp+32]
	add rax,[rsp+40] 	
	ret
