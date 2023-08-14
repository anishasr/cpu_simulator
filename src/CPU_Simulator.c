#include <stdio.h>
#include <unistd.h>
// for windows
// #include<windows.h>
#include "../headers/PCB.h"
#include "../headers/PCBQueue.h"
#include "../headers/Scheduler.h"

void move_next_process(struct Scheduler* scheduler, struct PCBQueue* q, int a) {
    struct PCB* p = q->head;
    q->head = q->head->next;
    // send p to scheduler
    schedule_process(scheduler,p,a);
}

// retrieve next process from the Scheduler
void retrieve_process(struct Scheduler* scheduler) {
    struct PCB* pcb = select_next_process(scheduler->pq);
}

int main() {
    // set up structures neede for simulation
    struct PCBQueue* q = new_queue();
    struct Scheduler* scheduler = new_scheduler();

    for(int i=0;i<10;i++) {
        struct PCB* p = new_pcb();
        // set process state to ready for simulation
        p->p_state = READY;
        add_to_queue(q,p);
    }

    // print pids of PCBs
    struct PCB* current = q->head;

    while (current != NULL) {
        printf("PID: %d\n", current->pid);
        current = current->next;
    }

    printf("Pick a scheduling algorithm: (1) First Come First Serve (2) Shortest Job First, (3) Longest Job First, (4) Priority Scheduling, (5) Round Robin, (6) Shortest Remaining Time, (7) Longest Remaining Time:\n");
    // char a = getchar();
    char a = '1';

    // begin sending process to scheduler's priority queue
    for(int i=0;i<10;i++) {
        move_next_process(scheduler,q,a);
        // sleep(1);
    }
    
    return 0;
}