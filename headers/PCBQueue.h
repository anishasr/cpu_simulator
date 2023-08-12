struct PCBQueue {
    // linked list
    struct PCB* head;
    struct PCB* last;
};

struct PCBQueue* new_queue();

struct PCBQueue* add_to_queue(struct PCBQueue* q, struct PCB* p);