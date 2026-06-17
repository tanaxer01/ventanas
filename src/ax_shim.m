#import <AppKit/AppKit.h>
#import <ApplicationServices/ApplicationServices.h>
#include "ax_shim.h"

WMWindow ax_get_focused_window(void) {
    AXUIElementRef app = AXUIElementCreateApplication(
        [NSWorkspace.sharedWorkspace frontmostApplication].processIdentifier
    );
    AXUIElementRef window = NULL;
    AXUIElementCopyAttributeValue(app, kAXFocusedWindowAttribute, (CFTypeRef*)&window);
    CFRelease(app);
    return (void*)window;  // caller owns this
}

void ax_move_window(WMWindow win, int x, int y) {
    CGPoint pos = CGPointMake(x, y);
    AXValueRef val = AXValueCreate(kAXValueCGPointType, &pos);
    AXUIElementSetAttributeValue((AXUIElementRef)win, kAXPositionAttribute, val);
    CFRelease(val);
}

void ax_resize_window(WMWindow win, int width, int height) {
    CGSize size = CGSizeMake(width, height);
    AXValueRef val = AXValueCreate(kAXValueCGSizeType, &size);
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
    CGPoint pos;
    CGSize size;

    AXValueRef val;

    AXUIElementCopyAttributeValue((AXUIElementRef)win, kAXPositionAttribute, (CFTypeRef*)&val);
    AXValueGetValue(val, kAXValueCGPointType, &pos);
    CFRelease(val);

    AXUIElementCopyAttributeValue((AXUIElementRef)win, kAXSizeAttribute, (CFTypeRef*)&val);
    AXValueGetValue(val, kAXValueCGSizeType, &size);
    CFRelease(val);

    return (WMRect){ pos.x, pos.y, size.width, size.height };
}

bool ax_minimize_window(WMWindow win, bool minimized) {
    CFBooleanRef value = minimized ? kCFBooleanTrue : kCFBooleanFalse;
    AXError err = AXUIElementSetAttributeValue(
        (AXUIElementRef)win,
        kAXMinimizedAttribute,
        value
    );

    return err == kAXErrorSuccess;
}
