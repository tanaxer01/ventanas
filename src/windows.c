#include <stdio.h>

#include "windows.h"
#include "application.h"
#include "ax_shim.h"
#include "wm.h"

// WINDOW

struct window *window_create(struct application *application, AXUIElementRef window_ref, uint32_t window_id) {
    struct window *window = malloc(sizeof(struct window));
    memset(window, 0, sizeof(struct window));

    window->application = application;
    window->ref = window_ref;
    window->id = window_id;
    window->frame = window_ax_frame(window);

   return window;
}

void window_destroy(struct window *window) {
    window->id = 0;

    CFRelease(window->ref);
    free(window);
}

// WM ----

void wm_move_window(struct window *window, float x, float y) {
    CGPoint position = CGPointMake(x, y);
    CFTypeRef position_ref = AXValueCreate(kAXValueTypeCGPoint, (void *) &position);
    if (!position_ref) return;

    AXUIElementSetAttributeValue(window->ref, kAXPositionAttribute, position_ref);
    CFRelease(position_ref);
}

void wm_resize_window(struct window *window, float width, float height) {
    CGSize size = CGSizeMake(width, height);
    CFTypeRef size_ref = AXValueCreate(kAXValueCGSizeType, (void *) &size);
    if (!size_ref) return;

    AXUIElementSetAttributeValue(window->ref, kAXSizeAttribute, size_ref);
    CFRelease(size_ref);
}

struct window *wm_focused_window(struct window_manager *wm) {
    struct application *apk = wm_focused_application(wm);
    if (!apk) return NULL;

    uint32_t win_id = apk_focused_window(apk);
    return wm_find_window(wm, win_id);
}

// TODO: Alternative to SLS needed
struct application *wm_focused_application(struct window_manager *wm) {
    return NULL;
}


// TODO: Use hashtable or wat ?
// > > >
struct window *wm_find_window(struct window_manager *wm, uint32_t window_id) {
    return NULL;
}

void wm_remove_window(struct window_manager *wm, uint32_t window_id) {
}

void wm_add_window(struct window_manager *wm, struct window *window) {
}

struct application *wm_find_application(struct window_manager *wm, pid_t pid) {
    return NULL;
}

void wm_remove_application(struct window_manager *wm, pid_t pid) {
}

void wm_add_application(struct window_manager *wm, struct application *application) {
}

struct window **window_manager_find_application_windows(struct window_manager *wm, struct application *application, int *window_count) {
    return NULL;
}
// < < <

void wm_init(struct window_manager *wm) {
    // wm->system_element = AXUIElementCreateSystemWide();
    // AXUIElementSetMessagingTimeout(wm->system_element, 1.0);



}



// OLD

// TODO: handle errors

void wm_snap_left(WMContext *ctx) {
    WMWindow win = ax_get_focused_window();
    if (!win) return;

    WMRect screen_frame = ax_get_screen_frame();
    int padding = ctx->config.padding;

    ax_move_window(win, screen_frame.x + padding, screen_frame.y + padding);
    ax_resize_window(win, (screen_frame.w / 2) - padding*2, screen_frame.h - padding*2);
}

void wm_snap_right(WMContext *ctx) {
    WMWindow win = ax_get_focused_window();
    if (!win) return;

    WMRect screen_frame = ax_get_screen_frame();
    int padding = ctx->config.padding;

    ax_move_window(win, screen_frame.x + (screen_frame.w / 2) + padding, screen_frame.y + padding);
    ax_resize_window(win, (screen_frame.w / 2) - padding*2, screen_frame.h - padding*2);
}

void wm_snap_top_left(WMContext *ctx) {
    WMWindow win = ax_get_focused_window();
    if (!win) return;

    WMRect screen_frame = ax_get_screen_frame();
    int padding = ctx->config.padding;

    ax_move_window(win, screen_frame.x + padding, screen_frame.y + padding);
    ax_resize_window(win, (screen_frame.w / 2) - padding*2, (screen_frame.h / 2) - padding*2);
}

void wm_snap_top_right(WMContext *ctx) {
    WMWindow win = ax_get_focused_window();
    if (!win) return;

    WMRect screen_frame = ax_get_screen_frame();
    int padding = ctx->config.padding;

    ax_move_window(win, screen_frame.x + (screen_frame.w / 2) + padding, screen_frame.y + padding);
    ax_resize_window(win, (screen_frame.w / 2) - padding*2, (screen_frame.h / 2) - padding*2);
}

void wm_snap_bottom_left(WMContext *ctx) {
    WMWindow win = ax_get_focused_window();
    if (!win) return;

    WMRect screen_frame = ax_get_screen_frame();
    int padding = ctx->config.padding;

    ax_move_window(win, screen_frame.x + padding, screen_frame.y + (screen_frame.h / 2) + padding);
    ax_resize_window(win, (screen_frame.w / 2) - padding*2, (screen_frame.h / 2) - padding*2);
}

void wm_snap_bottom_right(WMContext *ctx) {
    WMWindow win = ax_get_focused_window();
    if (!win) return;

    WMRect screen_frame = ax_get_screen_frame();
    int padding = ctx->config.padding;

    ax_move_window(win, screen_frame.x + (screen_frame.w / 2) + padding, screen_frame.y + (screen_frame.h / 2) + padding);
    ax_resize_window(win, (screen_frame.w / 2) - padding*2, (screen_frame.h / 2) - padding*2);
}

void wm_center_window() {
    WMWindow win = ax_get_focused_window();
    if (!win) return;

    WMRect screen_frame = ax_get_screen_frame();
    WMRect window_frame = ax_get_window_frame(win);

    int a = (screen_frame.w - window_frame.w) / 2;
    int b = (screen_frame.h - window_frame.h) / 2;

    ax_move_window(win, screen_frame.x + a, screen_frame.y + b);
}


// TODO: What about screen dimentions
// TODO: Let user choose step size ¿?

void wm_shrink_window(WMContext *ctx) {
    WMWindow win = ax_get_focused_window();
    if (!win) return;

    WMRect window_frame = ax_get_window_frame(win);
    ax_resize_window(win, window_frame.w - 20, window_frame.h - 20);

    if (ctx->config.center_on_resize) ax_move_window(win, window_frame.x + 10, window_frame.y + 10);
}

void wm_expand_window(WMContext *ctx) {
    WMWindow win = ax_get_focused_window();
    if (!win) return;

    WMRect window_frame = ax_get_window_frame(win);
    ax_resize_window(win, window_frame.w + 20, window_frame.h + 20);

    if (ctx->config.center_on_resize) ax_move_window(win, window_frame.x - 10, window_frame.y - 10);
}

// TODO: ...

void wm_change_space(WMContext *ctx, int target) {
    if (target > ctx->spaces.count) return;
    if (target == ctx->spaces.active) return;

    printf("[WM] change_space: %d -> %d\n", ctx->spaces.active, target);

    WMWindow focused = ax_get_focused_window();
    if (!focused) return;

    WMSpace *curr = &ctx->spaces.spaces[ctx->spaces.active];
    WMSpace *next = &ctx->spaces.spaces[target];

    int win_idx = -1;
    for (int i = 0; i < curr->count; i++) {
        if (CFEqual((CFTypeRef)curr->windows[i], (CFTypeRef)focused)) {
            win_idx = i;
            break;
        }
    }

    ax_release_window(focused);

    if (win_idx < 0) return;
    if (next->count >= WM_MAX_WINDOWS) return;

    WMWindow moved = curr->windows[win_idx];
    WMRect frame = ax_get_window_frame(moved);

    for (int i = 0; i < next->count; i++) {
        if (next->windows[i] == moved) return;
    }

    next->windows[next->count] = moved;
    next->saved_frames[next->count] = frame;
    next->count++;

    int last = curr->count - 1;
    curr->windows[win_idx] = curr->windows[last];
    curr->saved_frames[win_idx] = curr->saved_frames[last];
    curr->count--;

    curr->windows[curr->count] = 0;
    curr->saved_frames[curr->count] = (WMRect){0};

    for (int i = 0; i < curr->count; i++) {
        printf("%p ", curr->windows[i]);
    }
    printf("\n");

    for (int i = 0; i < next->count; i++) {
        printf("%p ", next->windows[i]);
    }

    // TODO: VISUAL EFECT
}
