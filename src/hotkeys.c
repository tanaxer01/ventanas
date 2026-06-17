#include <ApplicationServices/ApplicationServices.h>
#include <Carbon/Carbon.h>

#include "hotkeys.h"
#include "windows.h"


static CGEventRef event_cb(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void *data) {
    if (type != kCGEventKeyDown) return event;

    CGKeyCode keycode = (CGKeyCode)CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);
    CGEventFlags flags = CGEventGetFlags(event);

    // TODO: Check for hk in data


    // > > > temp
    bool cmd = flags & kCGEventFlagMaskCommand;
    bool opt = flags & kCGEventFlagMaskAlternate;

    if (cmd && opt) {
        switch (keycode) {
            case kVK_LeftArrow: wm_snap_left(data);         return NULL;
            case kVK_RightArrow: wm_snap_right(data);       return NULL;
            case kVK_ANSI_U: wm_snap_top_left(data);        return NULL;
            case kVK_ANSI_I: wm_snap_top_right(data);       return NULL;
            case kVK_ANSI_J: wm_snap_bottom_left(data);     return NULL;
            case kVK_ANSI_K: wm_snap_bottom_right(data);    return NULL;
            case kVK_ANSI_C: wm_center_window();            return NULL;

            case kVK_ANSI_M: wm_minimize_window(data);     return NULL;

            case kVK_ANSI_Equal: wm_expand_window(data);    return NULL;
            case kVK_ANSI_Minus: wm_shrink_window(data);    return NULL;
        }
    }
    // < < <


    return event;
}

void hk_init(WMContext *ctx) {
    // TODO: Build the hk registry

    CFMachPortRef tap = CGEventTapCreate(
        kCGSessionEventTap,
        kCGHeadInsertEventTap,
        kCGEventTapOptionDefault,
        CGEventMaskBit(kCGEventKeyDown),
        event_cb,
        ctx
    );

    if (!tap) {
        fprintf(stderr, "CGEventTapCreate failed — grant Accessibility permission in System Settings\n");
        exit(1);
    }

    CFRunLoopSourceRef src = CFMachPortCreateRunLoopSource(NULL, tap, 0);
    CFRunLoopAddSource(CFRunLoopGetMain(), src, kCFRunLoopCommonModes);
    CGEventTapEnable(tap, true);
}
