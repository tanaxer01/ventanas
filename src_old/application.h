#ifndef APPLICATION_H
#define APPLICATION_H

#include <ApplicationServices/ApplicationServices.h>

struct process;

struct application {
    AXUIElementRef ref;
    pid_t pid;
    char *name;
};

struct application *application_create(struct process *process);
void application_destroy(struct application *app);

CFArrayRef application_window_list(struct application *application);

#endif
