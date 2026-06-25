#pragma once
#include <ApplicationServices/ApplicationServices.h>

struct application {
    AXUIElementRef ref;
    pid_t pid;
};

uint32_t    apk_main_window(struct application *apk);
uint32_t    apk_focused_window(struct application *apk);
CFArrayRef  apk_window_list(struct application *apk);
void        apk_destroy(struct application *apk);
// struct application *apk_create(struct process *process);
