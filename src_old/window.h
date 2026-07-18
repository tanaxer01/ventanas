#ifndef WINDOW_H
#define WINDOW_H

#include <ApplicationServices/ApplicationServices.h>

struct application;
struct process_manager;
struct space_manager;

struct window {
    struct application *app;
    AXUIElementRef ref;
    uint32_t id;
};

CGPoint window_ax_origin(struct window* window);
// CGPoint window_ax_frame(struct window* window);

struct window *window_create(struct application *app, AXUIElementRef window_ref, uint32_t window_id);
void window_destroy(struct window *window);

struct window_manager {
    struct application *applications[128];
    int app_count;

    struct window *windows[128];
    int win_count;
};

void window_manager_move_window(struct window *window, float x, float y);
void window_manager_resize_window(struct window *window, float height, float width);

void window_manager_begin(struct process_manager *pm, struct space_manager *sm, struct window_manager *wm);
bool window_manager_add_existing_application_windows(struct space_manager *sm, struct window_manager *wm, struct application *application);

struct window *window_manager_create_and_add_window(struct window_manager *wm, struct application *application, AXUIElementRef window_ref, uint32_t window_id);

void window_manager_add_window(struct window_manager *wm, struct window *window);
struct window *window_manager_find_window(struct window_manager *wm, uint32_t window_id);

#endif
