#include "window.h"
#include "application.h"
#include "space.h"
#include "helpers.h"
#include "process.h"

CGPoint window_ax_origin(struct window *window) {
    CGPoint origin = {0};
    CFTypeRef position_ref = NULL;

    AXUIElementCopyAttributeValue(window->ref, kAXPositionAttribute, &position_ref);

    if (position_ref) {
        AXValueGetValue(position_ref, kAXValueTypeCGPoint, &origin);
        CFRelease(position_ref);
    }

    return origin;
}


void window_manager_move_window(struct window *window, float x, float y) {
    CGPoint position = CGPointMake(x, y);
    CFTypeRef position_ref = AXValueCreate(kAXValueCGPointType, (void *) &position);
    if (!position_ref) return;

    AXUIElementSetAttributeValue(window->ref, kAXPositionAttribute, position_ref);
    CFRelease(position_ref);
}

void window_manager_resize_window(struct window *window, float width, float height) {
    CGPoint size = CGPointMake(width, height);
    CFTypeRef size_ref = AXValueCreate(kAXValueCGPointType, (void *) &size);
    if (!size_ref) return;

    AXUIElementSetAttributeValue(window->ref, kAXSizeAttribute, size_ref);
    CFRelease(size_ref);
}


struct window *window_create(struct application *app, AXUIElementRef window_ref, uint32_t window_id) {
    struct window *window = malloc(sizeof(struct window));
    memset(window, 0, sizeof(struct window));

    window->app = app;
    window->ref = window_ref;
    window->id = window_id;

    return window;
}

void window_destroy(struct window *window) {
    window->id = 0;

    CFRelease(window->ref);
    free(window);
}

void window_manager_begin(struct process_manager *pm, struct space_manager *sm, struct window_manager *wm) {
    for (int i = 0; i < pm->proc_count; i++) {
        struct application *application = application_create(pm->processes[i]);

        // TODO: CHECK IF win_count == max
        wm->applications[wm->app_count] = application;
        wm->app_count++;
    }
}

bool window_manager_add_existing_application_windows(struct space_manager *sm, struct window_manager *wm, struct application *application) {
    bool result = false;

    CFArrayRef window_list_ref = application_window_list(application);
    int window_count = window_list_ref ? CFArrayGetCount(window_list_ref) : 0;

    for (CFIndex i = 0; i < window_count; i++) {
        AXUIElementRef window = CFArrayGetValueAtIndex(window_list_ref, i);
        uint32_t window_id = ax_window_id(window);

        if (!window_id) {
            printf("AAAAAA %s %ld-%d\n", application->name, i, window_count);
            continue;
        }

        if (!window_manager_find_window(wm, window_id)) {
            window_manager_create_and_add_window(wm, application, CFRetain(window), window_id);
        }
    }

    if (window_list_ref) CFRelease(window_list_ref);

    return result;
}

struct window *window_manager_create_and_add_window(struct window_manager *wm, struct application *application, AXUIElementRef window_ref, uint32_t window_id) {
    struct window *window = window_create(application, window_ref, window_id);

    // char *window_title =

    window_manager_add_window(wm, window);

    return window;
}

void window_manager_add_window(struct window_manager *wm, struct window *window) {
    // TODO: CHECK IF win_count == max
    wm->windows[wm->win_count] = window;
    wm->win_count++;

}

struct window *window_manager_find_window(struct window_manager *wm, uint32_t window_id) {
    for (int i = 0; i < wm->win_count; i++) {
        if (wm->windows[i]->id == window_id)
            return wm->windows[i];
    }

    return NULL;
}
