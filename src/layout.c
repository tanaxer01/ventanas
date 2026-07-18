#include "layout.h"

CGRect layout_snap_rect(CGRect bounds, enum snap_direction dir) {
  CGFloat x = bounds.origin.x,
          y = bounds.origin.y,
          w = bounds.size.width,
          h = bounds.size.height;

  switch (dir) {
    case SNAP_LEFT:
      return CGRectMake(x, y, w / 2.0, h);

    case SNAP_RIGHT:
      return CGRectMake(x + w / 2.0, y, w / 2.0, h);

    case SNAP_TOP:
      return CGRectMake(x, y, w, h / 2.0);

    case SNAP_BOTTOM:
      return CGRectMake(x, y + h / 2.0, w, h / 2.0);

    case SNAP_FULLSCREEN:
      return bounds;
  };

  return bounds;
}

CGRect layout_center_rect(CGRect bounds, CGRect frame) {
  CGFloat x = bounds.origin.x,
          y = bounds.origin.y;

  CGFloat a = (bounds.size.width - frame.size.width) / 2,
          b = (bounds.size.height - frame.size.height) / 2;

  return CGRectMake(x + a, y + b, frame.size.width, frame.size.height);
}
