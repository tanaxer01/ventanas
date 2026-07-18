#ifndef SPACE_H
#define SPACE_H

#include <ApplicationServices/ApplicationServices.h>

#define MAX_WINDOWS 128

struct window;
struct space {
    struct window *windows[MAX_WINDOWS];
    int count;
};

// NOTE: This should die to allow the use of map instead of arr
struct window *space_window_at(struct space *space, int index);
struct window *space_find_window(struct space *space, uint32_t id);

void space_hide_window(struct space *space, int index);
void space_add_window(struct space *space, struct window *window);
struct window *space_remove_window(struct space *space, int window_id);



#endif
