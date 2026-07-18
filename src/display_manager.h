#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include "process.h"
#include "display.h"
#include "window.h"

#define MAX_DISPLAYS 32

struct display_manager {
    struct display displays[MAX_DISPLAYS];
    int count;
};

struct window *display_manager_focused_window(struct display_manager *dm, struct process_manager *pm);
struct display *display_manager_focused_display(struct display_manager *dm);

struct window *display_manager_find_window(struct display_manager *dm, uint32_t window_id);

void display_manager_init(struct display_manager *dm);
void display_manager_begin(struct display_manager *dm, struct process_manager *pm);

#endif
