Writing Your Own System Call (points: 45)
As described in the class, the OS provides operations to users via system calls.
System calls are functions, natively available to users via C library functions,
provide access to almost all OS level functionality – viz. open(), write(),
fork() etc.
You have to create your own system call in C, called sh task info(), which

takes argument as PID. It would need to search out the task struct() corre-
sponding to the PID and print out all the fields corresponding to it and also

save it in a file. The file name also needs to be supplied as an argument to the
system call.

You also would require to handle errors in user inputs, such as incorrect ar-
guments, through appropriate errno and function return values (e.g. 0 signaling

correct input, while 1 signaling incorrect input).
You are supposed to use Linux/kernel v5.9 distribution for the assignment,
i.e. the system call should be written for the said version. You would need
to first download the kernel version from the official repository of the Linux
distribution that you are using (e.g. Ubuntu) and compile and boot that up.
The system call should be written and tested for this version.
What To Submit
• We have provided the git repository template for code submission.You
need to clone the template and use it as specified in README.md.
https://github.com/mayank18049/OS-Assignment-2
• You need to submit the diff, of the originally downloaded kernel source
tree and the one with your changes. This patched code MUST match the
one you have in our kernel source (running on a VM). We would verify
this at the time of the demos.
• Write-up describing the following:
– Description of your code and how you implemented the function –
the logical and implementation details.
– The inputs the user should give.
– Expected output (and how to interpret it).
– Error values and how to interpret them.
• A sample C program to test out your implementation of the system call.
