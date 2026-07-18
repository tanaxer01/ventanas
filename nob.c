#define NOB_IMPLEMENTATION
#include "nob.h"

#define BUILD_FOLDER "build/"
#define SRC_FOLDER "src/"

int main(int argc, char **argv) {
    NOB_GO_REBUILD_URSELF(argc, argv);
    if (!nob_mkdir_if_not_exists(BUILD_FOLDER)) return 1;

    Nob_Cmd cmd = {0};

    if (argc > 1 && strcmp(argv[1], "test") == 0) {
        nob_cmd_append(&cmd,
            "cc", "-Wall", "-Wextra", "-o", BUILD_FOLDER"tests",
            "-framework", "ApplicationServices",
            SRC_FOLDER"space.c",
            SRC_FOLDER"display.c",
            SRC_FOLDER"window.c",
            SRC_FOLDER"layout.c",
            "tests/main.c"
        );

        if (!nob_cmd_run(&cmd)) return 1;

        cmd.count = 0;
        nob_cmd_append(&cmd, BUILD_FOLDER"tests");
        if (!nob_cmd_run(&cmd)) return 1;

        return 0;
    }

    nob_cmd_append(&cmd, "cc", "-Wall", "-Wextra", "-o", BUILD_FOLDER"ventanas",
        "-framework", "Cocoa",
        "-framework", "Carbon",
        "-framework", "ApplicationServices",
        SRC_FOLDER"process.m",
        SRC_FOLDER"window.c",
        SRC_FOLDER"space.c",
        SRC_FOLDER"display_manager.c",
        SRC_FOLDER"display.c",
        SRC_FOLDER"layout.c",
        SRC_FOLDER"hotkey.c",
        SRC_FOLDER"main.c");
    if (!nob_cmd_run(&cmd)) return 1;

}
