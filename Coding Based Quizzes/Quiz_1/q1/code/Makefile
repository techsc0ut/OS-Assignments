all : C_Compilation Asm_Compilation
	gcc -no-pie main.o add.o -o a.out
	./a.out

C_Compilation: Preprocessed Assembled Object

Preprocessed:
	gcc -E main.c -o main.i

Assembled:
	gcc -S main.i -o main.s

Object:
	gcc -c main.s -o main.o

Asm_Compilation: 
	nasm -f elf64 add.asm -o add.o
	
	
	
	
	
	
	
	
	
	
	
	


 
