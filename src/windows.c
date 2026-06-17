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

void wm_minimize_window(WMContext *ctx) {
    WMWindow win = ax_get_focused_window();
    if (!win) return;

    ax_minimize_window(win, true);
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
