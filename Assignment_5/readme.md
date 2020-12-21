Modifying CFS Scheduler (Total points: 45).
Deadline: November 12, 2020 @ 2359hrs.

We spoke about the Linux CFS scheduler in class. It is however a non-
realtime scheduler, with non-realtime guarantees being given to processes. As

a part of this second assignment you need to add a soft real-time requirement
to a process – say something like each process, that requires soft real-time
guarantees must receive atleast x units of time-slice. Every time the scheduler

is called, you need to check if the real-time guarantees of process with soft-
realtime requirements are being met or not. You would give higher priority to a

processes soft-realtime requirement compared to the vruntime that is normally
considered.
You would thus need to modify the scheduler in such a way that when
everytime a process is selected through the RB-tree, you you need to compare
to all other process with soft-realtime requirements and see which one of those

require the CPU more urgently than the one selected through the regular RB-
tree. The one that urgently requires CPU time need to be scheduled before the

one selected through CFS.
You would additionally require a system call to modify the tasks soft-realtime
requirements – say rtnice, which takes argument the PID and the realtime
guarantees needed. rtnice can have a corresponding user program with the
same name which should actually do the system call rtnice to perform the said
operation with the supplied PID.
To test the correct functionality of the modified scheduler, you need to run
tasks requiring realtime guarantees. You would need to set the guarantees
through the rtnice program. You would need to show execution time of the
process with and without the soft realtime guarantees. This should demonstrate
to you if the modified scheduler is functioning or not.
What To Submit
• You need to submit the diff, of the originally downloaded kernel source
tree and the one with your changes. We would patch that diff with our
copy of the original source tree and compile the kernel.

1

• Write-up describing the following:
– We have provided the git repository template for code submission.You
need to clone the template and use it as specified in README.md.
https://github.com/mayank18049/OS-Assignment-3
– Description of your code and how you implemented the function –
the logical and implementation details.
– The inputs the user should give.
– Expected output (and how to interpret it).
– Error values and how to interpret them.
• Sample scripts/test cases on how to test the system.
