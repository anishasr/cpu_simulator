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
};

int generate_pid() {
    static int last_val = 0;
    return last_val++;
}

struct PCB* new_pcb() {
    struct PCB* p = malloc(sizeof(struct PCB));
    if (p != NULL) {
        p->pid = generate_pid();
        p->p_state = NEW;
        p->next = NULL;
    }
    return p;
};


/* Sources:
https://www.geeksforgeeks.org/static-variables-in-c/
*/ 
