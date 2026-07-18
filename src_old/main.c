#include <stdio.h>

#include "application.h"
#include "helpers.h"
#include "space.h"
#include "process.h"
#include "window.h"

struct process_manager g_process_manager;
struct window_manager g_window_manager;
struct space_manager g_space_manager;

int main() {
    printf("[+] starting....\n");

    if (!ax_privilege()) {
        printf("FAILED: could not access accessibility features!");
        return 1;
    }

    process_manager_add_running_processes(&g_process_manager);
    window_manager_begin(&g_process_manager, &g_space_manager, &g_window_manager);

    for (int i = 0; i < g_window_manager.app_count; i++) {
        struct application *a = g_window_manager.applications[i];

        printf("-> %d %s\n", a->pid, a->name);
        window_manager_add_existing_application_windows(&g_space_manager, &g_window_manager, a);

        for (int j = 0; j < g_window_manager.win_count; j++) {
            struct window *w = g_window_manager.windows[j];

            if (w->app == a) {
                printf("\t %d\n", w->id);
            }
        }
    }

    return 0;
}
