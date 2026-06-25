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

// window_manager stuff
void wm_set_window_frame(struct window *window, float x, float y, float width, float height);

struct window *wm_focused_window(struct window_manager *wm);
struct application *window_manager_focused_application(struct window_manager *wm);

void wm_remove_managed_window(struct window_manager *wm, uint32_t wid);
void wm_add_managed_window(struct window_manager *wm, struct window *window, struct view *view);

struct window *window_manager_find_window(struct window_manager *wm, uint32_t window_id);
void window_manager_remove_window(struct window_manager *wm, uint32_t window_id);
void window_manager_add_window(struct window_manager *wm, struct window *window);
