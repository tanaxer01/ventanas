#pragma once
#include "wm.h"
#include <ApplicationServices/ApplicationServices.h>

void wm_snap_left(WMContext *ctx);
void wm_snap_right(WMContext *ctx);

void wm_snap_top_left(WMContext *ctx);
void wm_snap_top_right(WMContext *ctx);
void wm_snap_bottom_left(WMContext *ctx);
void wm_snap_bottom_right(WMContext *ctx);

void wm_center_window();
void wm_minimize_window(WMContext *ctx);

void wm_shrink_window(WMContext *ctx);
void wm_expand_window(WMContext *ctx);

void wm_change_space(WMContext *ctx, int target);

// ----

struct window {
    struct application *application;
    AXUIElementRef ref;
    uint32_t id;
    CGRect frame;
};


CGPoint window_ax_origin(struct window *window);
CGRect  window_ax_frame(struct window *window);

struct window *window_create(struct application *application, AXUIElementRef window_ref, uint32_t window_id);
void window_destroy(struct window *window);

// window_manager stuff

#define MAX_APPLICATIONS 64
#define MAX_WINDOWS 64

struct window_manager {
    struct application *applications[MAX_WINDOWS];
    int apk_count;

    struct window *windows[MAX_WINDOWS];
    int win_count;
};

void wm_move_window(struct window *window, float x, float y);
void wm_resize_window(struct window *window, float width, float height);

// NOTE: Check yabai impl
// void wm_set_window_frame(struct window *window, float x, float y, float width, float height);

struct window *wm_focused_window(struct window_manager *wm);
struct application *wm_focused_application(struct window_manager *wm);

void wm_remove_managed_window(struct window_manager *wm, uint32_t wid);
void wm_add_managed_window(struct window_manager *wm, struct window *window, struct view *view);

struct window *wm_find_window(struct window_manager *wm, uint32_t window_id);
void wm_remove_window(struct window_manager *wm, uint32_t window_id);
void wm_add_window(struct window_manager *wm, struct window *window);

struct application *wm_find_application(struct window_manager *wm, pid_t pid);
void wm_remove_application(struct window_manager *wm, pid_t pid);
void wm_add_application(struct window_manager *wm, struct application *application);
struct window **window_manager_find_application_windows(struct window_manager *wm, struct application *application, int *window_count);

// void window_manager_send_window_to_space(struct space_manager *sm, struct window_manager *wm, struct window *window, uint64_t sid, bool moved_by_rule);

void wm_init(struct window_manager *wm);
