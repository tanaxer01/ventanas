#pragma once
#include "wm.h"
#include "ax_shim.h"

void wm_space_select(WMSpace *space);
void wm_space_hide(WMSpace *space);
void ws_switch_to(WMContext *context, int index);

void ws_init(WMContext *context);
