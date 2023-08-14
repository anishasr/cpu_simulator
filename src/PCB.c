#include <stdio.h>
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

    // attributes for scheduling
    int burst_time;
};

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
        p->p_state = NEW;
        p->next = NULL;
    }
    return p;
};


/* Sources:
https://www.geeksforgeeks.org/static-variables-in-c/
https://www.tutorialspoint.com/c_standard_library/c_function_rand.htm
https://stackoverflow.com/questions/3876635/how-to-randomly-print-1-to-10-in-c
*/ 
