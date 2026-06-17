#pragma once
#include "wm.h"

void wm_snap_left(WMContext *ctx);
void wm_snap_right(WMContext *ctx);

void wm_snap_top_left(WMContext *ctx);
void wm_snap_top_right(WMContext *ctx);
void wm_snap_bottom_left(WMContext *ctx);
void wm_snap_bottom_right(WMContext *ctx);

void wm_center_window();
void wm_minimize_window(WMContext *ctx);

void wm_shrink_window(WMContext *ctx);
void wm_expand_window(WMContext *ctx);
