#include "display.h"

CGRect display_manager_screen_frame() {
    NSScreen *screen = [NSScreen mainScreen];
    if (!screen) return CGRectZero;

    return NSRectToCGRect(screen.visibleFrame);
}
