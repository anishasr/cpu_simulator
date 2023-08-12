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
