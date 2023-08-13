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

void delete(struct PCB* p) {

}

struct PCB* get_min(struct BinaryHeap* pq) {
    return pq->pcbs[0];
}

struct PCB* selct_next_process(struct BinaryHeap* pq) {
    struct PCB* next_process = get_min(pq);
    // remove process at root because it will be executed by CPU
    delete(next_process);
    return next_process;
}

int main() {
    struct BinaryHeap* bh = new_heap();

    // TESTING
    struct PCB* p = new_pcb();
    printf("%d\n", p->burst_time);

    sjf_insert(bh,p);

    struct PCB* p2 = new_pcb();
    printf("%d\n", p2->burst_time);

    sjf_insert(bh,p2);

    struct PCB* p3 = new_pcb();
    printf("%d\n", p3->burst_time);

    sjf_insert(bh,p3);

    struct PCB* p4 = new_pcb();
    printf("%d\n", p4->burst_time);

    sjf_insert(bh,p4);

    struct PCB* p5 = new_pcb();
    printf("%d\n", p5->burst_time);

    sjf_insert(bh,p5);

    printf("\n");
    // printf("%d\n",bh->pcbs[0]->burst_time);
    // printf("%d\n",bh->pcbs[1]->burst_time);
    // printf("%d\n",bh->pcbs[2]->burst_time);
    // printf("%d\n",bh->pcbs[3]->burst_time);
    // printf("%d\n",bh->pcbs[4]->burst_time);
    display_heap(bh);
}