#ifndef HELPERS_T
#define HELPERS_T

#import <ApplicationServices/ApplicationServices.h>

#include "extern.h"

#define array_count(a) (int)(sizeof(a) / sizeof(*(a)))

static inline bool ax_privilege(void) {
    const void *keys[] = { kAXTrustedCheckOptionPrompt };
    const void *values[] = { kCFBooleanTrue };

    CFDictionaryRef options = CFDictionaryCreate(NULL, keys, values, array_count(keys),  &kCFCopyStringDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
    bool result = AXIsProcessTrustedWithOptions(options);

    CFRelease(options);
    return result;
}

static inline uint32_t ax_window_id(AXUIElementRef ref)
{
    uint32_t wid = 0;
    _AXUIElementGetWindow(ref, &wid);
    return wid;
}

#endif
