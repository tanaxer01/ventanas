
#include <ApplicationServices/ApplicationServices.h>

#include "window.h"

void window_set_frame(struct window *window, CGRect frame) {
  window_move(window, frame.origin.x, frame.origin.y);
  window_resize(window, frame.size.width, frame.size.height);
  // window_move(window, frame.origin.x, frame.origin.y);


  window->real_frame.origin = frame.origin;
  window->real_frame.size = frame.size;
}

void window_move(struct window *window, float x, float y) {
  if (!window || !window->ref) return;

  CGPoint position = CGPointMake(x, y);
  CFTypeRef position_ref = AXValueCreate(kAXValueCGPointType, (void *) &position);
  if (!position_ref) return;

  AXError err = AXUIElementSetAttributeValue(window->ref, kAXPositionAttribute, position_ref);
  CFRelease(position_ref);

  printf("moving %d, (%f,%f)\n\n", window->id, x, y);
}

void window_resize(struct window *window, float width, float height) {
  if (!window || !window->ref) return;

  CGSize size = CGSizeMake(width, height);
  CFTypeRef size_ref = AXValueCreate(kAXValueCGSizeType, (void *) &size);
  if (!size_ref) return;

  AXError err = AXUIElementSetAttributeValue(window->ref, kAXSizeAttribute, size_ref);
  CFRelease(size_ref);


  printf("resizing %d, (%f,%f)\n", window->id, width, height);
}


struct window *window_create(struct process *proc, AXUIElementRef window_ref, uint32_t window_id) {
  struct window *window = malloc(sizeof(struct window));
  memset(window, 0, sizeof(struct window));

  window->proc = proc;
  window->ref = CFRetain(window_ref);
  window->id = window_id;

  CFTypeRef position_ref = NULL;
  AXUIElementCopyAttributeValue(window_ref, kAXPositionAttribute, &position_ref);
  AXValueGetValue(position_ref, kAXValueCGPointType, &window->real_frame.origin);

  CFRelease(position_ref);

  AXUIElementCopyAttributeValue(window_ref, kAXSizeAttribute, &position_ref);
  AXValueGetValue(position_ref, kAXValueCGSizeType, &window->real_frame.size);

  CFRelease(position_ref);

  return window;
}

void window_destroy(struct window *window) {
  window->id = 0;

  CFRelease(window->ref);
  free(window);
}
