#include <ApplicationServices/ApplicationServices.h>
#include <stddef.h>

#include "hotkey.h"

static CGEventRef event_cb(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void *data) {
  if (type != kCGEventKeyDown) return event;

  struct hotkey_manager *hm = (struct hotkey_manager *)data;
  if (!hm) return event;

  CGKeyCode keycode = CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);
  CGEventFlags flags = CGEventGetFlags(event) & (kCGEventFlagMaskShift | kCGEventFlagMaskControl | kCGEventFlagMaskAlternate | kCGEventFlagMaskCommand);

  for (int i = 0; i < hm->count; i++) {
    struct hotkey *hotkey = &hm->hotkeys[i];

    if (hotkey->keycode == keycode && hotkey->modifiers == flags && hotkey->cb) {
      hotkey->cb(hm->ctx, hotkey->data);
      break;
    }
  }

  return event;
}

void hotkey_manager_begin(struct hotkey_manager *hm) {

  CFMachPortRef tap = CGEventTapCreate(
      kCGSessionEventTap,
      kCGHeadInsertEventTap,
      kCGEventTapOptionDefault,
      CGEventMaskBit(kCGEventKeyDown),
      event_cb,
      (void *)hm
  );


  if (!tap) {
    fprintf(stderr, "CGEventTapCreate failed — grant Accessibility permission in System Settings\n");
    exit(1);
  }

  CFRunLoopSourceRef src = CFMachPortCreateRunLoopSource(NULL, tap, 0);
  CFRunLoopAddSource(CFRunLoopGetMain(), src, kCFRunLoopCommonModes);
  CGEventTapEnable(tap, true);
}
