#include <Carbon/Carbon.h>
#include <stdio.h>
#include <unistd.h>

#include "display.h"
#include "display_manager.h"
#include "helpers.h"
#include "hotkey.h"
#include "layout.h"
#include "process.h"

struct display_manager dm;
struct process_manager pm;
struct hotkey_manager hm;

void print_string() {
  printf("hotkey pressed!\n");
}

void focus_space(void *ctx, void *data) {
    struct app_state *app = ctx;
    int *num = data;

    // TODO: Get active disp
    display_focus_space(&app->dm->displays[0], *num);
}

void snap_window_left_command(void *ctx, void *data) {
  struct app_state *app = ctx;
  enum snap_direction *dir = data;

  struct window *win = display_manager_focused_window(app->dm, app->pm);
  display_snap_window(&app->dm->displays[0], win->id, *dir);
}

int main() {
    printf("starting...\n");

    if (!ax_privilege()) {
        printf("FAILED: could not access accessibility features!");
        return 1;
    }

    process_manager_init(&pm);
    display_manager_init(&dm);

    for (int i = 0; i < dm.count; i++) {
        struct display d = dm.displays[i];
        CGRect bounds = CGDisplayBounds(d.id);

        printf("%u: id=%u bounds(%f,%f %fx%f)\n",
            i,
            d.id,
            bounds.origin.x,
            bounds.origin.y,
            bounds.size.width,
            bounds.size.height
        );

    }

    display_manager_begin(&dm, &pm);
    dm.displays[0].count = 5;

    struct app_state app = {
      .dm = &dm,
      .pm = &pm,
      .hm = &hm
    };

    enum snap_direction a = SNAP_LEFT;
    enum snap_direction b = SNAP_RIGHT;

    hm = (struct hotkey_manager){
        .hotkeys = (struct hotkey[]){
            { .keycode = kVK_ANSI_H, .modifiers = kCGEventFlagMaskControl | kCGEventFlagMaskAlternate, .cb = snap_window_left_command, .data = &a},
            { .keycode = kVK_ANSI_L, .modifiers = kCGEventFlagMaskControl | kCGEventFlagMaskAlternate , .cb = snap_window_left_command, .data = &b },
        },
        .count = 2,
        .ctx = &app
    };

    hotkey_manager_begin(&hm);

    struct window *w = display_manager_focused_window(&dm, &pm);
    printf("FOCUSED ON %s %d\n", w->proc->name, w->id);

    // NOTE: CF loop should be handled in hotkeys layer
    CFRunLoopRun();

    return 0;
}
