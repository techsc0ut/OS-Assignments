Process creation and termination
system calls (Total points: 50 ).

Due date: Sept 30, 2020. Time: 23:59 Hrs. (Hard Dead-
line)

The first exercise deals using process creation system call, fork(). You need to
write a program that spawns a child process, using the fork() system call. The
child process reads a CSV file, presented with the assignment, that has (fake)
student IDs and grades of various assignments. This child process computes the
average score of each student for section ‘A’, and thereafter prints the details of
these students (of section ‘A’, i.e.). The parent process does the same operation,
on the same CSV file but for students of section ‘B’.
The parent process must wait for the child process to terminate, by using
the system call waitpid(). The child process must call the exit() system call
once its execution ends.

You would require to refer to the manpages for various system calls men-
tioned.

What To Submit
• Program source code with Makefile to compile and pause the compilation
at each phase.
• Write-up describing the how your program works, with details of each
system call, the arguments passed and the expected outcomes and how
you handled error/corner cases.
