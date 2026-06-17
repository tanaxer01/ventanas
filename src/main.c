#include <ApplicationServices/ApplicationServices.h>
#include <stdio.h>

#include "hotkeys.h"

int main() {
    printf("starting...\n");

    WMContext ctx = { .config = { .padding = 10, .center_on_resize = true } };

    hk_init(&ctx);
    CFRunLoopRun();

    return 0;
}
