Differences Between Processes and Threads (points:
30
As you know by now when fork() results in complete duplication of all process
memories, while pthread create() results only in partial. Your exercise is
to write a program where a global variable is initialized to a value of say 10.
At some point, the program fork()s and creates a child process. The parent
process increments the global variable linearly upto 100 (i.e. 11, 12, 13....,100).
The child process does the opposite, i.e. decrements linearly upto -90. Both
the parent and child processes should print the value of the variable.

Repeat the same using pthread create(), where the parent threat incre-
ments the global variable linearly upto 100 (i.e. 11, 12, 13....,100). The child

thread does the opposite, i.e. decrements linearly upto -90. Both the parent
and child threads should print the value of the variable.
Is there any difference in the value of the global variable as printed by the
parent and child process, versus when printed via the parent and child thread?
Either ways, please explain in detail the reason behind this difference.

What To Submit
• We have provided the git repository template for code submission.You
need to clone the template and use it as specified in README.md.
https://github.com/mayank18049/OS-Assignment-2
• The source code of the two programs with their Makefile(s).
• Write-up describing the reasons behind the difference that you observed.
