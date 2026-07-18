#include <ApplicationServices/ApplicationServices.h>
#include <stdlib.h>
#include <strings.h>

#include "display.h"
#include "helpers.h"
#include "process.h"
#include "space.h"
#include "window.h"
#include "display_manager.h"


struct window *display_manager_focused_window(struct display_manager *dm, struct process_manager *pm) {
  struct process *process = process_manager_focused_application(pm);

  CFTypeRef focused_window_ref = NULL;
  AXError error = AXUIElementCopyAttributeValue(
      process->ref, kAXFocusedWindowAttribute, &focused_window_ref);

  if (error != kAXErrorSuccess || !focused_window_ref)
    return NULL;

  AXUIElementRef ax_window = (AXUIElementRef)focused_window_ref;
  uint32_t window_id = ax_window_id(ax_window);

  CFRelease(focused_window_ref);

  return display_manager_find_window(dm, window_id);
}

struct window *display_manager_find_window(struct display_manager *dm, uint32_t window_id) {
  for (int i = 0; i < dm->count; i ++) {
    struct display *d = &dm->displays[i];
    struct space *s = &d->spaces[d->active];

    for (int j = 0; j < s->count; j++) {
      if (s->windows[j]->id == window_id) return s->windows[j];
    }
  }

  return NULL;
}

void display_manager_init(struct display_manager *dm) {
    uint32_t count = 0;
    CGGetActiveDisplayList(0, NULL, &count);
    // TODO: count > MAX_DISPLAY

    uint32_t *display_list = malloc(count * sizeof(*display_list));
    // TODO: !display_list

    CGGetActiveDisplayList(count, display_list, &count);

    dm->count = (int)count;
    for (uint32_t i = 0; i < count; i++) {
        dm->displays[i].id = display_list[i];
        dm->displays[i].frame = CGDisplayBounds(display_list[i]);
        dm->displays[i].count = 0;
        dm->displays[i].active = 0;
    }

    free(display_list);
}

void display_manager_begin(struct display_manager *dm, struct process_manager *pm) {
    for (int i = 0; i < pm->count; i++) {
        CFArrayRef arr = process_window_list(pm->processes[i]);
        if (!arr) continue;

        for (CFIndex j = 0; j < CFArrayGetCount(arr); j++) {
            AXUIElementRef window_ref = CFArrayGetValueAtIndex(arr, j);
            uint32_t window_id = ax_window_id(window_ref);

            if (!window_id) continue;

            struct window *window = window_create(pm->processes[i], window_ref, window_id);
            space_add_window(&dm->displays[0].spaces[0], window);
            printf("%ld %s %d\n", j, window->proc->name, window->id);
        }

        CFRelease(arr);
    }

}
