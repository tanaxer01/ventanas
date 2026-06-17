#pragma once
#include <stdbool.h>

#include "ax_shim.h"

typedef struct {
  int padding;
  bool center_on_resize;
} WMConfig;

typedef struct {
    WMConfig config;
} WMContext;
