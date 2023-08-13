#include <stdio.h>
#include "../headers/PCB.h"
#include "../headers/PCBQueue.h"

void run_scheduler(char algorithm, struct PCBQueue* q) {
    struct PCB* next_process;
    if(algorithm == '1') {
        next_process = sjf(q);
    } else if(algorithm == '2') {
        next_process = ljf(q);
    } else if(algorithm == '3') {
        next_process = npps(q);
    } else if(algorithm == '4') {
        next_process = rrs(q);
    } else if(algorithm == '5') {
        next_process = strf(q);
    } else if(algorithm == '6') {
        next_process = ltrf(q);
    }
}

int main() {
    struct PCBQueue* q = new_queue();

    for(int i=0;i<10;i++) {
        struct PCB* p = new_pcb();
        add_to_queue(q,p);
    }

    // print pids of PCBs
    struct PCB* current = q->head;

    while (current != NULL) {
        printf("PID: %d\n", current->pid);
        current = current->next;
    }

    printf("Which scheduling algorithm would you like to use? (1) to Shortest Job First, (2) Longest Job First, (3) Priority Scheduling, (4) Round Robin, (5) Shortest Remaining Time, (6) Longest Remaining Time:\n");
    char a = getchar();

    if(a != NULL) {
        run_scheduler(a, q);
    }
    
    return 0;
}
