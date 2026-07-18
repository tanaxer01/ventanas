#ifndef PROCESS_H
#define PROCESS_H

#include <ApplicationServices/ApplicationServices.h>
#include <stdbool.h>

struct process {
    AXUIElementRef ref;
    pid_t pid;
    char *name;
};

void process_destroy(struct process *process);

struct process_manager {
    struct process *processes[128];
    int proc_count;
};

bool process_manager_begin();
void process_manager_add_running_processes(struct process_manager *pm);

#endif
