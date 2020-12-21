all:Exec
	./Exec

#Final Executable File
Exec:main.o
	gcc main.o -o Exec

#Object File (Not Human Readable)
main.o:main.s
	gcc -c main.s 

#Compiled File
main.s:main.i
	gcc -S main.i 

#Preprocessed File
main.i:main.c
	gcc -E main.c > main.i

