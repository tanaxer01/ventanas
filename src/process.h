#ifndef PROCESS_H
#define PROCESS_H

#include <ApplicationServices/ApplicationServices.h>

struct process {
    AXUIElementRef ref;
    pid_t pid;
    char *name;
};

CFArrayRef process_window_list(struct process *process);
void process_destroy(struct process *process);

struct process_manager {
    struct process *processes[128];
    int count;
};

struct process *process_manager_focused_application(struct process_manager *pm);

void process_manager_add_running_processes(struct process_manager *pm);
void process_manager_init(struct process_manager *pm);

#endif
