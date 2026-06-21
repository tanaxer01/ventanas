#import <AppKit/AppKit.h>
#import <ApplicationServices/ApplicationServices.h>
#include "ax_shim.h"

WMWindow ax_get_focused_window(void) {
    AXUIElementRef app = AXUIElementCreateApplication(
        [NSWorkspace.sharedWorkspace frontmostApplication].processIdentifier
    );
    AXUIElementRef window = NULL;
    AXError err = AXUIElementCopyAttributeValue(app, kAXFocusedWindowAttribute, (CFTypeRef*)&window);
    CFRelease(app);
    if (err != kAXErrorSuccess) return NULL;
    return (void*)window;  // caller owns this
}

int ax_get_all_windows(WMWindow *windows, int max_windows) {
    if (max_windows <= 0) return 0;

    int count = 0;

    for (NSRunningApplication *app in NSWorkspace.sharedWorkspace.runningApplications) {
        if (app.activationPolicy != NSApplicationActivationPolicyRegular) continue;

        AXUIElementRef axApp = AXUIElementCreateApplication(app.processIdentifier);
        if (!axApp) continue;

        CFArrayRef axWindows = NULL;
        AXError err = AXUIElementCopyAttributeValue(
            axApp,
            kAXWindowsAttribute,
            (CFTypeRef *)&axWindows
        );

        if (err == kAXErrorSuccess && axWindows) {
            CFIndex n = CFArrayGetCount(axWindows);

            for (CFIndex i = 0; i < n && count < max_windows; i++) {
                AXUIElementRef win = (AXUIElementRef)CFArrayGetValueAtIndex(axWindows, i);
                if (!win) continue;

                CFRetain(win); // keep it alive after releasing axWindows
                windows[count++] = (WMWindow)win;
            }

            CFRelease(axWindows);
        }

        CFRelease(axApp);

        if (count >= max_windows) break;
    }

    return count;
}

void ax_move_window(WMWindow win, int x, int y) {
    CGPoint pos = CGPointMake(x, y);
    AXValueRef val = AXValueCreate(kAXValueCGPointType, &pos);
    if (!val) return;
    AXUIElementSetAttributeValue((AXUIElementRef)win, kAXPositionAttribute, val);
    CFRelease(val);
}

void ax_resize_window(WMWindow win, int width, int height) {
    CGSize size = CGSizeMake(width, height);
    AXValueRef val = AXValueCreate(kAXValueCGSizeType, &size);
    if (!val) return;
    AXUIElementSetAttributeValue((AXUIElementRef)win, kAXSizeAttribute, val);
    CFRelease(val);
}

WMRect ax_get_screen_frame(void) {
    NSScreen *screen = [NSScreen mainScreen];
    NSRect frame = screen.frame;
    NSRect visible = screen.visibleFrame;

    // AppKit screen rects are bottom-left based. AX window positions use a
    // top-based Y for window placement. Convert the usable frame so its Y is
    // the distance from the top of the screen to the top of the visible area.
    CGFloat topInset = NSMaxY(frame) - NSMaxY(visible);

    return (WMRect){
        (int)visible.origin.x,
        (int)topInset,
        (int)visible.size.width,
        (int)visible.size.height,
    };
}

WMRect ax_get_window_frame(WMWindow win) {
    CGPoint pos = CGPointZero;
    CGSize size = CGSizeZero;

    AXValueRef val = NULL;

    AXError err = AXUIElementCopyAttributeValue((AXUIElementRef)win, kAXPositionAttribute, (CFTypeRef*)&val);
    if (err != kAXErrorSuccess || !val) return (WMRect){0};
    if (!AXValueGetValue(val, kAXValueCGPointType, &pos)) {
        CFRelease(val);
        return (WMRect){0};
    }
    CFRelease(val);

    val = NULL;
    err = AXUIElementCopyAttributeValue((AXUIElementRef)win, kAXSizeAttribute, (CFTypeRef*)&val);
    if (err != kAXErrorSuccess || !val) return (WMRect){0};
    if (!AXValueGetValue(val, kAXValueCGSizeType, &size)) {
        CFRelease(val);
        return (WMRect){0};
    }
    CFRelease(val);

    return (WMRect){ pos.x, pos.y, size.width, size.height };
}

void ax_release_window(WMWindow win) {
    if (win) CFRelease((AXUIElementRef)win);
}
