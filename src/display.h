#ifndef DISPLAY_H
#define DISPLAY_H
#include <ApplicationServices/ApplicationServices.h>

#include "space.h"
#include "layout.h"

// TODO: VARIABLE AMOUNT OF SPACES

#define MAX_SPACES 5

struct display {
    CGDirectDisplayID id;
    CGRect frame;

    int count, active;
    struct space spaces[MAX_SPACES];
};

struct space *display_space_at(struct display *display, int index);

void display_focus_space(struct display *display, int space_index);
void display_move_window_to_space(struct display *display, int window_index, int space_index);

void display_snap_window(struct display *display, int window_id, enum snap_direction dir);
void display_center_window(struct display *display, int window_id);

#endif
