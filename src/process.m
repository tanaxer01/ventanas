#include "helpers.h"
#include "window.h"
#include <AppKit/AppKit.h>
#import <ApplicationServices/ApplicationServices.h>
#include <Foundation/Foundation.h>

#include "process.h"

CFArrayRef process_window_list(struct process *process) {
  CFTypeRef window_list_ref = NULL;
  AXUIElementCopyAttributeValue(process->ref, kAXWindowsAttribute,
                                &window_list_ref);
  return window_list_ref;
}

void process_destroy(struct process *process) {
  CFRelease(process->ref);
  free(process->name);
  free(process);
}

struct process *
process_manager_focused_application(struct process_manager *pm) {
  NSRunningApplication *frontmost =
      NSWorkspace.sharedWorkspace.frontmostApplication;

  for (int i = 0; i < pm->count; i++) {
    if (frontmost.processIdentifier == pm->processes[i]->pid)
      return pm->processes[i];
  }

  return NULL;
}

void process_manager_add_running_processes(struct process_manager *pm) {
  for (NSRunningApplication *app in NSWorkspace.sharedWorkspace
           .runningApplications) {
    if (app.activationPolicy != NSApplicationActivationPolicyRegular)
      continue;

    AXUIElementRef axApp = AXUIElementCreateApplication(app.processIdentifier);
    if (!axApp)
      continue;

    struct process *p = malloc(sizeof(struct process));
    p->ref = axApp;
    p->pid = app.processIdentifier;
    p->name = strdup(app.localizedName.UTF8String);

    pm->processes[pm->count] = p;
    pm->count++;
  }
}

void process_manager_init(struct process_manager *pm) {
  process_manager_add_running_processes(pm);
}
