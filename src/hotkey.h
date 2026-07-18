#ifndef HOTKEY_H
#define HOTKEY_H

#include "display_manager.h"
#include "process.h"
#include <ApplicationServices/ApplicationServices.h>

struct hotkey {
  CGKeyCode keycode;
  CGEventFlags modifiers;
  void (*cb)(void *ctx, void *data);
  void *data;
};

struct hotkey_manager {
  struct hotkey *hotkeys;
  int count;
  void *ctx;
};

// TEMP
struct app_state {
    struct display_manager *dm;
    struct process_manager *pm;
    struct hotkey_manager *hm;
};

void hotkey_manager_begin(struct hotkey_manager *hm);

#endif
