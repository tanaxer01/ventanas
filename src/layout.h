#ifndef LAYOUT_H
#define LAYOUT_H

#include <ApplicationServices/ApplicationServices.h>

enum snap_direction {
  SNAP_LEFT,
  SNAP_RIGHT,
  SNAP_TOP,
  SNAP_BOTTOM,
  SNAP_FULLSCREEN,
};

CGRect layout_snap_rect(CGRect bounds, enum snap_direction dir);
CGRect layout_center_rect(CGRect bounds, CGRect frame);



#endif
