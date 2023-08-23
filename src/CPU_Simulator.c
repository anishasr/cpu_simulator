#include <stdio.h>
#include <unistd.h>
// for windows
// #include<windows.h>
#include "../headers/PCB.h"
#include "../headers/PCBQueue.h"
#include "../headers/Scheduler.h"

struct Simulator {
    int turnaround[50];
    int wait[50];
    int response[50];
};

struct Simulator* new_simulator() {
    struct Simulator* sim = malloc(sizeof(struct Simulator));
    if (sim != NULL) {
        // initialize arrays
        for (int i = 0; i < 50; i++) {
            sim->turnaround[i] = -1;
            sim->wait[i] = -1;
            sim->response[i] = -1;
        }
    }
    return sim;
}

void move_next_process(struct Scheduler* scheduler, struct PCBQueue* q, int a, int clock) {
    struct PCB* p = q->head;
    // update arrival time
    p->arrival_time = clock;
    q->head = q->head->next;
    // send p to scheduler
    schedule_process(scheduler,p,a);
}

// retrieve next process from the Scheduler
struct PCB* retrieve_process(struct Scheduler* scheduler, int a) {
    struct PCB* pcb;
    if(a == '1') {
        pcb = select_next_process_fcfs(scheduler);
    } else if(a == '2') {
        pcb = select_next_process_sjc(scheduler->pq);
    } else if(a == '3') {
        pcb = select_next_process_npp(scheduler->pq);
    }
    return pcb;
}

int calculate_average(int vals[]) {
    int i = 0;
    int sum = 0;
    for(int i=0;i<10;i++) {
        sum += vals[i];
    }
    return sum/10;
}

int main() {

    int clock = 0;

    // set up structures neede for simulation
    struct PCBQueue* q = new_queue();
    struct Scheduler* scheduler = new_scheduler();
    struct Simulator* simulator = new_simulator();


    printf("Pick a scheduling algorithm: (1) First Come First Serve (2) Shortest Job First, (3) Non-Preemptive Priority, or 's' to exit:\n");
    char a = getchar();

    for(int i=0;i<10;i++) {
        struct PCB* p = new_pcb();
        // set process state to ready for simulation
        p->p_state = READY;
        add_to_queue(q,p);
    }

    // begin sending process to scheduler's priority queue
    for(int i=0;i<10;i++) {
        clock++;
        simulator->wait[i] = clock;
        move_next_process(scheduler,q,a,clock);
        // sleep(1);
    }

    // show Scheduler's priority queue to view ordering of processes
    display_processes(scheduler,a);

    // begin executing processes
    struct PCB* p_next;
    for(int i=0;i<10;i++) {
        p_next = retrieve_process(scheduler, a);
        if(p_next!=NULL) {
            printf("\nCPU is executing Process %d\n", p_next->pid);
            while(p_next->burst_time > 0) {
                p_next->burst_time-=1;
                // printf("Time remaining %d\n", p_next->burst_time);
                // printf("%d\n", p_next->burst_time);
            }
            clock++;
            p_next->turnaround_time = clock - p_next->arrival_time;
            simulator->turnaround[i] = p_next->turnaround_time;
        }
        // sleep(1); 
    }
    printf("\n");

    int average_waiting = calculate_average(simulator->turnaround);
    printf("\nAverage waiting time for this waiting algorihm: %d", average_waiting);
}


/* Sources

Memory Mapping
https://www.tutorialspoint.com/unix_system_calls/mmap.htm
https://www.tutorialspoint.com/inter_process_communication/inter_process_communication_memory_mapping.htm
https://www.geeksforgeeks.org/loader-in-c-c/
https://www.ibm.com/docs/en/i/7.2?topic=ssw_ibm_i_72/apis/mmap.html

Files
https://www.geeksforgeeks.org/difference-between-file-descriptor-and-file-pointer/

Scheduling Algorithms
https://www.geeksforgeeks.org/cpu-scheduling-in-operating-systems/#sjf
https://www.baeldung.com/cs/cpu-scheduling

Other
PCB - geeksforgeeks.org/process-table-and-process-control-block-pcb/
perror - https://www.tutorialspoint.com/c_standard_library/c_function_perror.htm


*/ 

