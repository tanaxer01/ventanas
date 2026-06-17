#pragma once

// opaque handle to a window
typedef void* WMWindow;
typedef struct { int x, y, w, h; } WMRect;


WMWindow ax_get_focused_window(void);
void     ax_move_window(WMWindow win, int x, int y);
void     ax_resize_window(WMWindow win, int width, int height);

WMRect ax_get_screen_frame(void);
WMRect ax_get_window_frame(WMWindow win);

bool ax_minimize_window(WMWindow win, bool minimized);
