#pragma once
#include <stdbool.h>

#include "ax_shim.h"

#define WM_MAX_WINDOWS 64
#define WM_MAX_SPACES 5

typedef struct {
    WMWindow windows[WM_MAX_WINDOWS];
    WMRect saved_frames[WM_MAX_WINDOWS];
    int count;
} WMSpace;

typedef struct {
    WMSpace spaces[WM_MAX_SPACES];
    int count;
    int active;
} WMSpaces;

typedef struct {
  int padding;
  bool center_on_resize;
} WMConfig;

typedef struct {
    WMConfig config;
    // temp
    WMSpaces spaces;
} WMContext;
