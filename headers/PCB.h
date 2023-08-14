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

    // attributes for scheduling
    int burst_time;
};

// struct PCB* new_pcb();

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

#endif
