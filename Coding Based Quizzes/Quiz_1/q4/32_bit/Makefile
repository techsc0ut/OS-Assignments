all : C_Compilation Asm_Compilation1 
	gcc -no-pie -m32 P4.o add.o -o a.out
	./a.out

C_Compilation: Object

Object:
	gcc -c -m32 P4.c -o P4.o

Asm_Compilation1: 
	nasm -f elf32 P4_1.asm -o add.o

	
	
	
	
	
	
	
	
	
	
	
	


 
