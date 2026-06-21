#include <stdio.h>

#include "ax_shim.h"
#include "spaces.h"
#include "wm.h"


void wm_space_select(WMSpace *space) {
    for (int i = 0; i < space->count; i++) {
        WMRect curr = ax_get_window_frame(space->windows[i]);

        printf("Moving window %d from (%d, %d) to (%d, %d)\n", i, curr.x, curr.y, space->saved_frames[i].x, space->saved_frames[i].y);

        ax_move_window(space->windows[i], space->saved_frames[i].x, space->saved_frames[i].y);
        //ax_resize_window(space->windows[i], space->saved_frames[i].w, space->saved_frames[i].h);
    }
}

void wm_space_hide(WMSpace *space) {
    WMRect screen_frame = ax_get_screen_frame();

    // move windows offscreen
    int x = screen_frame.x + screen_frame.w - 1;
    int y = screen_frame.y + screen_frame.h - 1;

    for (int i = 0; i < space->count; i++) {
        ax_move_window(space->windows[i], x, y);
    }
}

void wm_space_switch_to(WMContext *context, int index) {
    if (index < 0 || index >= context->spaces.count) return;
    if (index == context->spaces.active) return;

    wm_space_hide(&context->spaces.spaces[context->spaces.active]);
    wm_space_select(&context->spaces.spaces[index]);

    context->spaces.active = index;
}

void wm_change_current_window_space(WMContext *context, int index) {

    // WMWindow current = ax_get_focused_window();

    WMWindow windows[64];
    int count = ax_get_all_windows(windows, 64);
    printf("------ %d\n", count);

    for (int i = 0; i < count; i++) {
        WMRect frame = ax_get_window_frame(windows[i]);
        printf("window %d: x=%d y=%d w=%d h=%d\n", i, frame.x, frame.y, frame.w, frame.h);

        ax_release_window(windows[i]);
    }


}

void space_init(WMContext *context) {
    WMWindow windows[64];
    int count = ax_get_all_windows(windows, 64);

    WMSpace *space = &context->spaces.spaces[0];
    context->spaces.count = 2;
    context->spaces.active = 0;
    space->count = count;

    for (int i = 0; i < count; i++) {
        space->windows[i] = windows[i];
        space->saved_frames[i] = ax_get_window_frame(windows[i]);
    }
}
