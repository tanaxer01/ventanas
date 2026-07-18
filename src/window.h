#ifndef WINDOW_H
#define WINDOW_H

#include <ApplicationServices/ApplicationServices.h>

struct window {
    struct process *proc;
    AXUIElementRef ref;
    uint32_t id;

    CGRect real_frame;
};

void window_set_frame(struct window *window, CGRect frame);

void window_move(struct window *window, float x, float y);
void window_resize(struct window *window, float width, float height);

struct window *window_create(struct process *proc, AXUIElementRef window_ref, uint32_t window_id);
void window_destroy(struct window *window);

#endif
