# OSLabWork

Operating Systems lab experiments in C and Linux command notes, forked from Mekkaden/OS_LAB_WORK.

## What it does

The files are the lab programs themselves. The same experiments appear in several folders and as loose files at the root, so some are in more than one version. What is included:

- Experiments 1 and 2: notes on Linux commands (`ps`, `strace`, `gdb`, `objdump`, `top` and others) and on the `/proc` filesystem.
- Experiment 3: a program that prints the system time and sleeps for 60 seconds, so it can be watched with process tools.
- Experiments 4 to 6: `fork`, `wait`, and `execvp` running a small `myadder` program.
- Experiment 7: threads that compute mean, median and standard deviation of a list.
- Experiment 8: interprocess communication with a pipe, a System V message queue, and shared memory.
- Experiment 9: CPU scheduling simulators for FCFS, priority (preemptive and non-preemptive), round robin and SRTF.
- Experiment 10: readers-writers with semaphores and a writer-priority gate.
- Experiment 11: Banker's algorithm, safety check and resource request.
- Experiment 12: dining philosophers with semaphores, limiting how many sit at the table.

## Status

Coursework, kept as submitted. Several compiled binaries and screenshots are committed alongside the source.

## Stack

C with POSIX threads, semaphores and System V IPC, for Linux.

## Run it

```bash
gcc exp9/expt9_fcfs.c -o fcfs && ./fcfs
gcc exp10/expt10.c -o rw -pthread && ./rw
```

## License

Coursework fork of Mekkaden/OS_LAB_WORK. No license is granted here beyond what the original repository allows.
