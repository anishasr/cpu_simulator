#include <stdio.h>
#include <stdlib.h>
#include "../headers/PCB.h"

#define MAX_PROCESSES 50

struct BinaryHeap {
    struct PCB* pcbs[50];
};

struct BinaryHeap* new_heap() {
    struct BinaryHeap* bh = malloc(sizeof(struct BinaryHeap));
    if(bh != NULL) {
        for(int i=0;i<50;i++) {
            bh->pcbs[i] = NULL;
        }
    }
    return bh;
};

struct Scheduler {
    struct BinaryHeap* pq;
    struct PCB* fcfs_pcbs[MAX_PROCESSES];  
    int fcfs_size;
};

struct Scheduler* new_scheduler() {
    struct Scheduler* s = malloc(sizeof(struct Scheduler));
    // create new binary heap for actual implementation of PQ
    struct BinaryHeap* bh_pq = malloc(sizeof(struct BinaryHeap));
    s->pq = bh_pq;
    for (int i = 0; i < MAX_PROCESSES; i++) {
        s->fcfs_pcbs[i] = NULL;
    }
    s->fcfs_size = 0;
    return s;
}

// return int as boolean val
int isEmpty(struct BinaryHeap* bh) {
    return bh->pcbs[0] == NULL;
}

int size(struct BinaryHeap* bh) {
    int i = 0;
    int count = 0;
    while(bh->pcbs[i] != NULL) {
        count++;
        i++;
    }
    return count;
}

void perc_down(struct BinaryHeap* bh) {
    // start at root
    int i = 0;
    int bh_size = size(bh);
    struct PCB* temp;
    struct PCB* sc;
    int sc_i;
    while(i < bh_size) {
        int lc_i = (i * 2) + 1;
        int rc_i = (i * 2) + 2;
        
        if(bh->pcbs[lc_i] != NULL) {
            // find smaller child to swap with
            if(bh->pcbs[rc_i] == NULL) {
                sc = bh->pcbs[lc_i];
                sc_i = lc_i;
            } else if(bh->pcbs[lc_i]->burst_time < bh->pcbs[rc_i]->burst_time) {
                sc_i = lc_i;
                sc = bh->pcbs[lc_i];
            } else {
                sc_i = rc_i;
                sc = bh->pcbs[rc_i];
            }

            if(sc->burst_time < bh->pcbs[i]->burst_time) {
                temp = bh->pcbs[i];
                bh->pcbs[i] = sc;
                bh->pcbs[sc_i] = temp;
            }
        }
        // compare to next lc and rc
        i++;
        // sc = NULL;
    }
}

void perc_down_npp(struct BinaryHeap* bh) {
    // start at root
    int i = 0;
    int bh_size = size(bh);
    struct PCB* temp;
    struct PCB* sc;
    int sc_i;
    while(i < bh_size) {
        int lc_i = (i * 2) + 1;
        int rc_i = (i * 2) + 2;
        
        if(bh->pcbs[lc_i] != NULL) {
            // find smaller child to swap with
            if(bh->pcbs[rc_i] == NULL) {
                sc = bh->pcbs[lc_i];
                sc_i = lc_i;
            } else if(bh->pcbs[lc_i]->priority < bh->pcbs[rc_i]->priority) {
                sc_i = lc_i;
                sc = bh->pcbs[lc_i];
            } else {
                sc_i = rc_i;
                sc = bh->pcbs[rc_i];
            }

            if(sc->priority < bh->pcbs[i]->priority) {
                temp = bh->pcbs[i];
                bh->pcbs[i] = sc;
                bh->pcbs[sc_i] = temp;
            }
        }
        // compare to next lc and rc
        i++;
        // sc = NULL;
    }
}

void perc_up(struct BinaryHeap* bh, int i) {
    // if i = 0, that means only 1 element in heap (root)
    while(i>0) {
        int parent_index = (i - 1)/2;
        if(bh->pcbs[i]->burst_time < bh->pcbs[parent_index]->burst_time) {
            // swap
            struct PCB* temp = bh->pcbs[parent_index];
            bh->pcbs[parent_index] = bh->pcbs[i];
            bh->pcbs[i] = temp;
        }
        // move i to the new position of inserted pcb to continue comparisons
        i = parent_index;
    }
}

void perc_up_npp(struct BinaryHeap* bh, int i) {
    // if i = 0, that means only 1 element in heap (root)
    while(i>0) {
        int parent_index = (i - 1)/2;
        if(bh->pcbs[i]->priority < bh->pcbs[parent_index]->priority) {
            // swap
            struct PCB* temp = bh->pcbs[parent_index];
            bh->pcbs[parent_index] = bh->pcbs[i];
            bh->pcbs[i] = temp;
        }
        // move i to the new position of inserted pcb to continue comparisons
        i = parent_index;
    }
}

void sjf_insert(struct BinaryHeap* bh, struct PCB* p) {
    int bh_size = size(bh);
    int current_index = bh_size;
    bh->pcbs[current_index] = p;

    perc_up(bh,current_index);
}

void npp_insert(struct BinaryHeap* bh, struct PCB* p) {
    int bh_size = size(bh);
    int current_index = bh_size;
    bh->pcbs[current_index] = p;

    perc_up_npp(bh,current_index);
}

void display_heap(struct BinaryHeap* bh, char a) {
    printf("\n");
    for(int i=0;i<size(bh);i++) {
        printf("| P%d ", bh->pcbs[i]->pid);
        if(a == '2') {
            printf("(%d) ", bh->pcbs[i]->burst_time);
        } else if(a == '3') {
            printf("(%d) ", bh->pcbs[i]->priority);
        }
    }
    printf("|\n");
}

void display_fcfs(struct Scheduler* s) {
    printf("\n");
    for(int i=0;i<s->fcfs_size;i++) {
        printf("| P%d ", s->fcfs_pcbs[i]->pid);
        printf("(%d) ", s->fcfs_pcbs[i]->burst_time);
    }
    printf("|\n");
}

void display_processes(struct Scheduler* s, int a) {
    if(a == '1') {
        display_fcfs(s);
    } else if(a == '2' || a == '3')
        display_heap(s->pq, a);
}

void delete_min(struct BinaryHeap* pq) {
    // replace root with most recently added process
    int last_index = size(pq)-1;
    struct PCB* temp_root = pq->pcbs[last_index];
    // pq->pcbs[0] = temp_root;
    pq->pcbs[0]->pid = temp_root->pid;
    pq->pcbs[0]->burst_time = temp_root->burst_time;
    pq->pcbs[0]->p_state = temp_root->p_state;
    // should 'next' be nullified when process leaves the ready queue?
    pq->pcbs[0]->next = temp_root->next;
    pq->pcbs[last_index] = NULL;
    
    // percolate down to preserve heap order
    perc_down(pq);
}

void delete_min_npp(struct BinaryHeap* pq) {
    // replace root with most recently added process
    int last_index = size(pq)-1;
    struct PCB* temp_root = pq->pcbs[last_index];
    // pq->pcbs[0] = temp_root;
    pq->pcbs[0]->pid = temp_root->pid;
    pq->pcbs[0]->burst_time = temp_root->burst_time;
    pq->pcbs[0]->p_state = temp_root->p_state;
    // should 'next' be nullified when process leaves the ready queue?
    pq->pcbs[0]->next = temp_root->next;
    pq->pcbs[last_index] = NULL;
    
    // percolate down to preserve heap order
    perc_down_npp(pq);
}

struct PCB* get_min(struct BinaryHeap* pq) {
    return pq->pcbs[0];
}

void schedule_process(struct Scheduler* scheduler, struct PCB* p, char algorithm) {
    // insert process based algorithm
    if(algorithm=='1') {
        int insert_at = scheduler->fcfs_size;
        scheduler->fcfs_pcbs[insert_at] = p;
        scheduler->fcfs_size++;
    } else if(algorithm == '2') {
        sjf_insert(scheduler->pq,p);
    } else if(algorithm == '3') {
        npp_insert(scheduler->pq,p);
    } 
}

struct PCB* select_next_process_fcfs(struct Scheduler* scheduler) {
    // get PCB at 0
    struct PCB* next_process = scheduler->fcfs_pcbs[0];
    struct PCB* next_cp = new_pcb();
        // bug fix - copy values to new pcb instead of returning pointer to 0th element
    if(next_process != NULL) {
        next_cp->pid = next_process->pid;
        next_cp->burst_time = next_process->burst_time;
        next_cp->p_state = next_process->p_state;
        next_cp->next = NULL;

        int last = scheduler->fcfs_size-1;
        // shift all elements to the left
        for(int i=1; i<=last; i++) {
            scheduler->fcfs_pcbs[i-1] = scheduler->fcfs_pcbs[i];
        }
        scheduler->fcfs_size--; 
    }
    return next_cp;

}


struct PCB* select_next_process_sjc(struct BinaryHeap* pq) {
    struct PCB* next_process = get_min(pq);
    struct PCB* next_cp = new_pcb();
    // bug fix - copy values to new pcb instead of returning pointer to root
    if(next_process != NULL) {
        next_cp->pid = next_process->pid;
        next_cp->burst_time = next_process->burst_time;
        next_cp->p_state = next_process->p_state;
        next_cp->next = NULL;
    }
    // remove process at root because it will be executed by CPU
    delete_min(pq);
    return next_cp;
}

struct PCB* select_next_process_npp(struct BinaryHeap* pq) {
    struct PCB* next_process = get_min(pq);
    struct PCB* next_cp = new_pcb();
    // bug fix - copy values to new pcb instead of returning pointer to root
    if(next_process != NULL) {
        next_cp->pid = next_process->pid;
        next_cp->burst_time = next_process->burst_time;
        next_cp->p_state = next_process->p_state;
        next_cp->next = NULL;
    }
    // remove process at root because it will be executed by CPU
    delete_min_npp(pq);
    return next_cp;
}
