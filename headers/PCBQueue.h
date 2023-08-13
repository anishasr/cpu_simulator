#ifndef PCBQUEUE_H
#define PCBQUEUE_H

#include <stdlib.h>
// #include "PCB.h"

struct PCBQueue {
    // linked list
    struct PCB* head;
    struct PCB* last;
};

// struct PCBQueue* new_queue();

// void add_to_queue(struct PCBQueue* q, struct PCB* p);

struct PCBQueue* new_queue() {
    struct PCBQueue* q = malloc(sizeof(struct PCBQueue));
    q->head = NULL;
    q->last = NULL;
    return q;
}

void add_to_queue(struct PCBQueue* q, struct PCB* p) {
    if(q->head == NULL) {
        q->head = p;
        q->last = p;
    } else {
        //  re-factor to insert based on scheduling policy
        q->last->next = p; 
        q->last = p;
    }
}

#endif