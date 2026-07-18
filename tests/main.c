#include <stdio.h>

#include "../src/space.h"
#include "../src/window.h"
#include "../src/display.h"

#define CHECK(cond) do { \
    if (!(cond)) { \
        fprintf(stderr, "FAIL: %s:%d: %s\n", __FILE__, __LINE__, #cond); \
        exit(1); \
    } \
} while (0)

#define CHECK_INT(actual, expected) do { \
    if ((actual) != (expected)) { \
        fprintf(stderr, "FAIL: %s:%d: got %d expected %d\n", \
            __FILE__, __LINE__, (actual), (expected)); \
        exit(1); \
    } \
} while (0)

#define CHECK_DOUBLE(actual, expected) do { \
    if ((actual) != (expected)) { \
        fprintf(stderr, "FAIL: %s:%d: got %f expected %f\n", \
            __FILE__, __LINE__, (actual), (expected)); \
        exit(1); \
    } \
} while (0)

static void test_space_add_window(void) {
    struct space space = {0};

    struct window window_a = {0};
    struct window window_b = {0};

    space_add_window(&space, &window_a);
    space_add_window(&space, &window_b);

    CHECK_INT(space.count, 2);
    CHECK(space.windows[0] == &window_a);
    CHECK(space.windows[1] == &window_b);
}

static void test_space_remove_window(void) {
    struct space space = {0};

    struct window window_a = {0};
    struct window window_b = {0};
    struct window window_c = {0};

    space_add_window(&space, &window_a);
    space_add_window(&space, &window_b);
    space_add_window(&space, &window_c);

    struct window *resp;

    resp = space_remove_window(&space, 10);
    CHECK_INT(space.count, 3);
    CHECK(resp == NULL);

    resp = space_remove_window(&space, 0);
    CHECK_INT(space.count, 2);
    CHECK(space.windows[0] = &window_c);

    resp = space_remove_window(&space, 1);
    CHECK_INT(space.count, 1);
    CHECK(space.windows[0] = &window_c);
}

// LAYOUT
static void test_layout(void) {
  CGRect rect;
  CGRect display = CGRectMake(0, 0, 1000, 1000);

  rect = layout_snap_rect(display, SNAP_LEFT);

  CHECK_DOUBLE(rect.origin.x, 0.);
  CHECK_DOUBLE(rect.origin.y, 0.);
  CHECK_DOUBLE(rect.size.width, 500.);
  CHECK_DOUBLE(rect.size.height, 1000.);

  rect = layout_snap_rect(display, SNAP_RIGHT);

  CHECK_DOUBLE(rect.origin.x, 500.);
  CHECK_DOUBLE(rect.origin.y, 0.);
  CHECK_DOUBLE(rect.size.width, 500.);
  CHECK_DOUBLE(rect.size.height, 1000.);

  rect = layout_snap_rect(display, SNAP_TOP);

  CHECK_DOUBLE(rect.origin.x, 0.);
  CHECK_DOUBLE(rect.origin.y, 0.);
  CHECK_DOUBLE(rect.size.width, 1000.);
  CHECK_DOUBLE(rect.size.height, 500.);

  rect = layout_snap_rect(display, SNAP_BOTTOM);

  CHECK_DOUBLE(rect.origin.x, 0.);
  CHECK_DOUBLE(rect.origin.y, 500.);
  CHECK_DOUBLE(rect.size.width, 1000.);
  CHECK_DOUBLE(rect.size.height, 500.);

  rect = layout_snap_rect(display, SNAP_FULLSCREEN);

  CHECK_DOUBLE(rect.origin.x, 0.);
  CHECK_DOUBLE(rect.origin.y, 0.);
  CHECK_DOUBLE(rect.size.width, 1000.);
  CHECK_DOUBLE(rect.size.height, 1000.);

  CGRect win = CGRectMake(10, 10, 200, 200);
  rect = layout_center_rect(display, win);

  CHECK_DOUBLE(rect.origin.x, 400.);
  CHECK_DOUBLE(rect.origin.y, 400.);
  CHECK_DOUBLE(rect.size.width, 200.);
  CHECK_DOUBLE(rect.size.height, 200.);
}

// DISPLAY
static void test_display_focus_space(void) {
  struct display display = { .count = 5 };
  struct window window = {0};

  space_add_window(&display.spaces[0], &window);
  display_focus_space(&display, 1);

  // TODO: Check window is visible
}

static void test_display_move_window_to_space(void) {
  struct display display = { .count = 5 };
  struct window window = {0};

  space_add_window(&display.spaces[0], &window);
  CHECK_INT(display.spaces[0].count, 1);
  CHECK_INT(display.spaces[1].count, 0);
  CHECK(display.spaces[0].windows[0] == &window);

  display_move_window_to_space(&display, 0, 1);
  CHECK_INT(display.spaces[0].count, 0);
  CHECK_INT(display.spaces[1].count, 1);
  CHECK(display.spaces[1].windows[0] == &window);

  // TODO: check that window is hidden
}

int main(void) {
    test_space_add_window();
    test_space_remove_window();

    test_layout();
    test_display_move_window_to_space();

    printf("all tests passed\n");
    return 0;
}
