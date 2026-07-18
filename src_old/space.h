#ifndef SPACE_H
#define SPACE_H

#include <ApplicationServices/ApplicationServices.h>

struct space {
    struct window *windows[128];
    CGPoint saved_coords[128];
    int count;
};

struct space_manager {
    struct space *spaces[5];
    int count;
    int active;
};

void space_manager_focus_space(struct space_manager *sm, int space_id);

void space_manager_add_window_to_space(struct space *sm, struct window *window, int space_id);

#endif
