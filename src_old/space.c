#include "space.h"
#include "window.h"

#include <ApplicationServices/ApplicationServices.h>

void space_manager_focus_space(struct space_manager *sm, int space_id) {
    for (int i = 0; i < sm->spaces[sm->active]->count; i++) {
        int x = 0, y = 0;
        window_manager_move_window(sm->spaces[sm->active]->windows[i], x, y);
    }

    for (int i = 0; i < sm->spaces[sm->active]->count; i++) {
        int x = 0, y = 0;
        window_manager_move_window(sm->spaces[sm->active]->windows[i], x, y);
    }


}

void space_manager_add_window_to_space(struct space *sm, struct window *window, int space_id) {
    sm->windows[sm->count] = window;
    sm->saved_coords[sm->count] = window_ax_origin(window);
    sm->count++;
}
