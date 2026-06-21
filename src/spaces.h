#pragma once
#include "wm.h"
#include "ax_shim.h"

void wm_space_select(WMSpace *space);
void wm_space_hide(WMSpace *space);
void wm_space_switch_to(WMContext *context, int index);

void wm_change_current_window_space(WMContext *context, int index);

void space_init(WMContext *context);
