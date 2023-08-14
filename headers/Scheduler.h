#include <stdio.h>
#include <stdlib.h>
#include "../headers/PCB.h"

struct BinaryHeap {
    struct PCB* pcbs[50];
};

struct BinaryHeap* new_heap() {
    // READ ABOUT malloc and how to know what goes in parentheses
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
};

struct Scheduler* new_scheduler() {
    struct Scheduler* s = malloc(sizeof(struct Scheduler));
    // create new binary heap for actual implementation of PQ
    struct BinaryHeap* bh_pq = malloc(sizeof(struct BinaryHeap));
    s->pq = bh_pq;
    return s;
}

void heapify() {

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
            }

            if(sc->burst_time < bh->pcbs[i]->burst_time) {
                temp = bh->pcbs[i];
                bh->pcbs[i] = sc;
                bh->pcbs[sc_i] = temp;
            }
        }
        // compare to next lc and rc
        i++;
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

void sjf_insert(struct BinaryHeap* bh, struct PCB* p) {
    int bh_size = size(bh);
    int current_index = bh_size;
    bh->pcbs[current_index] = p;

    perc_up(bh,current_index);
}

// TODO: re-factor with helper display_level instead of hard-coding
void display_heap(struct BinaryHeap* bh) {
    struct PCB* root = bh->pcbs[0];
    if (root != NULL) {
        printf("         %d(%d)\n", root->pid, root->burst_time);
        printf("        /    \\ \n");
    }

    if (bh->pcbs[1] != NULL) {
        printf("     %d(%d)  ", bh->pcbs[1]->pid, bh->pcbs[1]->burst_time);
    }
    if (bh->pcbs[2] != NULL) {
        printf("   %d(%d)\n", bh->pcbs[2]->pid, bh->pcbs[2]->burst_time);
    }

    printf("     / \\ \n");

    if (bh->pcbs[3] != NULL) {
        printf("%d(%d)  ", bh->pcbs[3]->pid, bh->pcbs[3]->burst_time);
    }
    if (bh->pcbs[4] != NULL) {
        printf(" %d(%d)\n", bh->pcbs[4]->pid, bh->pcbs[4]->burst_time);
    }

    printf("\n");
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

struct PCB* get_min(struct BinaryHeap* pq) {
    return pq->pcbs[0];
}

void schedule_process(struct Scheduler* scheduler, struct PCB* p, int algorithm) {
    // insert process based algorithm
    if(algorithm == '1') {
        sjf_insert(scheduler->pq,p);
    // } else if(algorithm == '2') {
    //     ljf_insert(p);
    // } else if(algorithm == '3') {
    //     npps_insert(p);
    // } 
    }
}

struct PCB* select_next_process(struct BinaryHeap* pq) {
    struct PCB* next_process = get_min(pq);
    // remove process at root because it will be executed by CPU
    delete_min(pq);
    return next_process;
}
