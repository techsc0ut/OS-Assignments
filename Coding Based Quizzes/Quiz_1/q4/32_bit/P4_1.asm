global long_add

section .text

long_add:	
	mov eax,0	
	add eax,[esp+4]
	add eax,[esp+8]
	add eax,[esp+12]
	add eax,[esp+16]		
	ret
