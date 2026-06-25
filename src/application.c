#include "application.h"
#include <stdlib.h>

uint32_t apk_main_window(struct application *apk) {
    CFTypeRef window_ref = NULL;
    AXUIElementCopyAttributeValue(apk->ref, kAXMainWindowAttribute, &window_ref);
    if (!window_ref) return 0;

    uint32_t window_id = ax_window_id(window_ref);
    CFRelease(window_ref);

    return window_id;
}

uint32_t apk_focused_window(struct application *apk) {
    CFTypeRef window_ref = NULL;
        AXUIElementCopyAttributeValue(apk->ref, kAXFocusedWindowAttribute, &window_ref);
        if (!window_ref) return 0;

        uint32_t window_id = ax_window_id(window_ref);
        CFRelease(window_ref);

        return window_id;
}

CFArrayRef apk_windows(struct application *apk) {
    CFTypeRef window_list_ref = NULL;
    AXUIElementCopyAttributeValue(apk->ref, kAXWindowsAttribute, &window_list_ref);
    return window_list_ref;
}

void apk_destroy(struct application *apk) {
    CFRelease(apk->ref);
    free(apk);
}
