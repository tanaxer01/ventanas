#include "space.h"
#include "window.h"

struct window *space_window_at(struct space *space, int index) {
  if (!space) return NULL;
  if (index < 0 || index >= space->count) return NULL;

  return space->windows[index];
}

struct window *space_find_window(struct space *space, uint32_t window_id) {
  if (!space) return NULL;

  for (int i = 0; i < space->count; i++) {
    if (space->windows[i]->id == window_id)
      return space->windows[i];
  }

  return NULL;
}

void space_add_window(struct space *space, struct window *window) {
    space->windows[space->count] = window;
    space->count++;
    // TODO: count > MAX_WINDOWS
}

struct window *space_remove_window(struct space *space, int window_index) {
    if (window_index >= space->count) return NULL;

    struct window *win = space->windows[window_index];

    space->count--;
    if (space->count > 1 && space->count != window_index)
      space->windows[window_index] = space->windows[space->count];

  return win;
}
