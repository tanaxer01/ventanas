#import <ApplicationServices/ApplicationServices.h>
#import <AppKit/AppKit.h>

#include "process.h"

void process_destroy(struct process *process) {
    free(process->name);
    free(process);
}

bool process_manager_begin() {



    return true;
}


void process_manager_add_running_processes(struct process_manager *pm) {
    for (NSRunningApplication *app in NSWorkspace.sharedWorkspace.runningApplications) {
        if (app.activationPolicy != NSApplicationActivationPolicyRegular) continue;

        AXUIElementRef axApp = AXUIElementCreateApplication(app.processIdentifier);
        if (!axApp) continue;

        struct process *p = malloc(sizeof(struct process));
        p->pid = app.processIdentifier;
        p->name = strdup(app.localizedName.UTF8String);
        pm->processes[pm->proc_count] = p;
        pm->proc_count++;

        CFRelease(axApp);
    }
}
