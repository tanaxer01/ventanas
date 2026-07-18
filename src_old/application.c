#include "application.h"
#include "process.h"

struct application *application_create(struct process *process) {
    struct application *app = malloc(sizeof(struct application));
    memset(app, 0, sizeof(struct application));

    app->ref = AXUIElementCreateApplication(process->pid);
    app->pid = process->pid;
    app->name = process->name;

    return app;
}

void application_destroy(struct application *app) {
    CFRelease(app->ref);
    free(app);
}

CFArrayRef application_window_list(struct application *application) {
    CFTypeRef window_list_ref = NULL;
    AXUIElementCopyAttributeValue(application->ref, kAXWindowsAttribute, &window_list_ref);
    return window_list_ref;
}
