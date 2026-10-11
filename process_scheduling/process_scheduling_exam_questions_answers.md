---
title: "Process Scheduling - Exam Questions and Answers"
---

## Question 1

Describe how round-robin, priority, and lottery scheduling work. Provide an example in which round-robin scheduling performs better than the other two.

<!-- answer:start -->

### Answer

Round-robin scheduling gives each ready process a fixed time quantum. Processes are placed in a queue. The scheduler runs the process at the front of the queue for at most one quantum, then moves it to the back of the queue if it is not finished or blocked.

Priority scheduling assigns a priority to each process and selects the process with the highest priority. It can be preemptive or non-preemptive. A common problem is starvation: low-priority processes may wait for a very long time if higher-priority processes keep arriving.

Lottery scheduling assigns lottery tickets to processes. When the scheduler must choose a process, it randomly selects a ticket, and the process holding that ticket gets the CPU. A process with more tickets has a higher probability of being selected.

Round-robin can perform better when processes are interactive and should all receive regular CPU time. For example, if several equally important interactive processes are ready, round-robin gives each one predictable service. Priority scheduling may starve low-priority processes, and lottery scheduling may delay a process for a long time by chance, even if the expected share is fair over time.

<!-- answer:end -->


## Question 2

Given the following table, and assuming Shortest Job First (non-preemptive), show how the CPU slots are allocated to processes and compute the average waiting time. All burst times are expressed in number of required CPU slots.

| Process | Arrival time | Burst time |
| --- | ---: | ---: |
| P1 | 0 | 10 |
| P2 | 1 | 3 |
| P3 | 3 | 5 |
| P4 | 11 | 2 |
| P5 | 12 | 3 |

<!-- answer:start -->

### Answer

Since the scheduler is non-preemptive, P1 goes first because it is the only process available at time 0.

The CPU allocation is:

| Time interval | Process |
| --- | --- |
| 0-10 | P1 |
| 10-13 | P2 |
| 13-15 | P4 |
| 15-18 | P5 |
| 18-23 | P3 |

Waiting times:

| Process | Start time | Arrival time | Waiting time |
| --- | ---: | ---: | ---: |
| P1 | 0 | 0 | 0 |
| P2 | 10 | 1 | 9 |
| P3 | 18 | 3 | 15 |
| P4 | 13 | 11 | 2 |
| P5 | 15 | 12 | 3 |

The average waiting time is:

```text
(0 + 9 + 15 + 2 + 3) / 5 = 29 / 5 = 5.8
```

<!-- answer:end -->


## Question 3

A variation of the round-robin scheduler is the regressive round-robin scheduler. This scheduler assigns each process a time quantum and a priority. The initial value of a time quantum is 50 milliseconds. However, every time a process has been allocated the CPU and uses its entire time quantum, that is, does not block for I/O, 10 milliseconds is added to its time quantum, and its priority level is boosted. The time quantum for a process can be increased to a maximum of 100 milliseconds. When a process blocks before using its entire time quantum, its time quantum is reduced by 5 milliseconds, but its priority remains the same.

What type of process, CPU-bound or I/O-bound, does the regressive round-robin scheduler favor? Explain.

<!-- answer:start -->

### Answer

The scheduler favors CPU-bound processes.

CPU-bound processes are likely to use their entire time quantum. When they do, they are rewarded with a longer time quantum and a priority boost.

I/O-bound processes are likely to block before using their entire time quantum. In that case, their time quantum is reduced by 5 milliseconds, although their priority remains the same. Therefore, I/O-bound processes are not directly penalized in priority, but they do not receive the same reward as CPU-bound processes.

<!-- answer:end -->


## Question 4

Consider the following set of processes, with the length of the CPU burst time given in milliseconds:

| Process | Burst time | Priority |
| --- | ---: | ---: |
| P1 | 2 | 2 |
| P2 | 1 | 1 |
| P3 | 8 | 4 |
| P4 | 4 | 2 |
| P5 | 5 | 3 |

The processes are assumed to have arrived in the order P1, P2, P3, P4, P5, all at time 0.

1. Draw four Gantt charts that illustrate the execution of these processes using the following scheduling algorithms: FCFS, SJF, non-preemptive priority (a smaller priority number implies a higher priority), and RR (quantum = 1).
2. What is the turnaround time of each process for each of the scheduling algorithms in part 1?
3. What is the waiting time of each process for each of these scheduling algorithms?
4. Which of the algorithms results in the minimum average waiting time, over all processes?

<!-- answer:start -->

### Answer

Gantt charts:

| Algorithm | Execution order |
| --- | --- |
| FCFS | P1 0-2, P2 2-3, P3 3-11, P4 11-15, P5 15-20 |
| RR, quantum = 1 | P1, P2, P3, P4, P5, P1, P3, P4, P5, P3, P4, P5, P3, P4, P5, P3, P5, P3, P3, P3 |
| SJF | P2 0-1, P1 1-3, P4 3-7, P5 7-12, P3 12-20 |
| Priority | P2 0-1, P1 1-3, P4 3-7, P5 7-12, P3 12-20 |

Turnaround times:

| Process | FCFS | RR | SJF | Priority |
| --- | ---: | ---: | ---: | ---: |
| P1 | 2 | 6 | 3 | 3 |
| P2 | 3 | 2 | 1 | 1 |
| P3 | 11 | 20 | 20 | 20 |
| P4 | 15 | 14 | 7 | 7 |
| P5 | 20 | 17 | 12 | 12 |

Waiting times, computed as turnaround time minus burst time:

| Process | FCFS | RR | SJF | Priority |
| --- | ---: | ---: | ---: | ---: |
| P1 | 0 | 4 | 1 | 1 |
| P2 | 2 | 1 | 0 | 0 |
| P3 | 3 | 12 | 12 | 12 |
| P4 | 11 | 10 | 3 | 3 |
| P5 | 15 | 12 | 7 | 7 |

Average waiting times:

| Algorithm | Average waiting time |
| --- | ---: |
| FCFS | 6.2 |
| RR | 7.8 |
| SJF | 4.6 |
| Priority | 4.6 |

SJF and Priority give the minimum average waiting time in this example, because the shortest jobs also have the highest priorities.

<!-- answer:end -->
