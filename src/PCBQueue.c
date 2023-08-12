#include <stdio.h>
#include "../headers/PCB.h"
#include "../headers/PCBQueue.h"

struct PCBQueue {
    // linked list
    struct PCB* head;
    struct PCB* last;
};

struct PCBQueue* new_queue(struct PCB* head) {
    struct PCBQueue* q;
    q->head = head;
    q->last = head;
    return q;
}

struct PCBQueue* add_to_queue(struct PCBQueue* q, struct PCB* p) {
    //  re-factor to insert based on scheduling policy
    q->last->next = p; 
    q->last = p;
}
