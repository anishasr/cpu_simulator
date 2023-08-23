#ifndef PCB_H
#define PCB_H

#include <stdlib.h>

enum ProcessState {
    NEW,
    READY,
    RUNNING,
    WAITING,
    TERMNATING
};

struct PCB {
    int pid; 
    enum ProcessState p_state;
    struct PCB* next;

    // attributes for scheduling algorithms
    int burst_time;
    int priority;

    // attributes for scheduling metrics
    int arrival_time;
    int completion_time;
    int wait_time;
    int turnaround_time; 
    int response_time; 

};

// ADD I/O times to make comparison of algorithms clearer

// struct PCB* new_pcb();

int gen_priority() {
    return (rand() % 20) + 1;
}

int gen_burst_time() {
    return (rand() % 20) + 1;
}

int gen_pid() {
    static int last_val = 1;
    return last_val++;
}

struct PCB* new_pcb() {
    struct PCB* p = malloc(sizeof(struct PCB));
    if (p != NULL) {
        p->pid = gen_pid();
        p->burst_time = gen_burst_time();
        p->priority = gen_priority();
        p->p_state = NEW;
        p->next = NULL;
        p->arrival_time = 0;
        p->wait_time = 0;
        p->turnaround_time= 0;
        p->response_time = 0;
    }
    return p;
};

#endif


/* Sources:
https://www.geeksforgeeks.org/static-variables-in-c/
https://www.tutorialspoint.com/c_standard_library/c_function_rand.htm
https://stackoverflow.com/questions/3876635/how-to-randomly-print-1-to-10-in-c
*/ 
