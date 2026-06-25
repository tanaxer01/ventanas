#include <stdio.h>

#include "windows.h"
#include "ax_shim.h"
#include "wm.h"


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
