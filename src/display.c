#include "display.h"
#include "layout.h"
#include "window.h"
#include "space.h"
#include <stdio.h>

struct space *display_space_at(struct display *display, int index) {
  if (!display) return NULL;
  if (index < 0 || index >= display->count) return NULL;

  return &display->spaces[index];
}

void display_focus_space(struct display *display, int space_index) {
    struct space *active_space = &display->spaces[display->active];
    struct space *target_space = display_space_at(display, space_index);
    if (!target_space) return;

    double x = display->frame.origin.x + display->frame.size.width - 1,
           y = display->frame.origin.y + display->frame.size.height - 1;

    for (int i = 0; i < active_space->count; i++) {
        struct window *window = active_space->windows[i];
        window_move(window, x, y);
    }

    for (int i = 0; i < target_space->count; i++) {
        struct window *window = target_space->windows[i];
        window_move(window, window->real_frame.origin.x, window->real_frame.origin.y);
    }

    display->active = space_index;
}

void display_move_window_to_space(struct display *display, int window_index, int space_index) {
  struct space *active_space = &display->spaces[display->active];
  struct space *target_space = display_space_at(display, space_index);
  if (!target_space) return;

  struct window *window = space_window_at(active_space, window_index);

  space_remove_window(active_space, window_index);
  space_add_window(target_space, window);

  double x = display->frame.origin.x + display->frame.size.width - 1,
         y = display->frame.origin.y + display->frame.size.height - 1;
  window_move(window, x, y);
}

void display_snap_window(struct display *display, int window_id, enum snap_direction dir) {
  struct space *space = &display->spaces[display->active];
  struct window *window = space_find_window(space, window_id);
  if (!window) return;

  CGRect target = layout_snap_rect(display->frame, dir);
  window_set_frame(window, target);
}

void display_center_window(struct display *display, int window_id) {
  struct space *space = &display->spaces[display->active];
  struct window *window = space_find_window(space, window_id);
  if (!window) return;

  CGRect target = layout_center_rect(display->frame, window->real_frame);
  window_set_frame(window, target);
}
