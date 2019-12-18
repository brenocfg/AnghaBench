#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  COPY_REFLINK ; 
 int ENOENT ; 
 int /*<<< orphan*/  F_OK ; 
 char** STRV_MAKE (int /*<<< orphan*/ ) ; 
 scalar_t__ arg_copy_keymap ; 
 int /*<<< orphan*/  arg_keymap ; 
 scalar_t__ arg_root ; 
 int copy_file (char*,char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ isempty (int /*<<< orphan*/ ) ; 
 scalar_t__ laccess (char const*,int /*<<< orphan*/ ) ; 
 int log_error_errno (int,char*,char const*) ; 
 int /*<<< orphan*/  log_info (char*,char const*) ; 
 int mkdir_parents (char const*,int) ; 
 char* prefix_roota (scalar_t__,char*) ; 
 int prompt_keymap () ; 
 int /*<<< orphan*/  strjoina (char*,int /*<<< orphan*/ ) ; 
 int write_env_file (char const*,char**) ; 

__attribute__((used)) static int process_keymap(void) {
        const char *etc_vconsoleconf;
        char **keymap;
        int r;

        etc_vconsoleconf = prefix_roota(arg_root, "/etc/vconsole.conf");
        if (laccess(etc_vconsoleconf, F_OK) >= 0)
                return 0;

        if (arg_copy_keymap && arg_root) {

                (void) mkdir_parents(etc_vconsoleconf, 0755);
                r = copy_file("/etc/vconsole.conf", etc_vconsoleconf, 0, 0644, 0, 0, COPY_REFLINK);
                if (r != -ENOENT) {
                        if (r < 0)
                                return log_error_errno(r, "Failed to copy %s: %m", etc_vconsoleconf);

                        log_info("%s copied.", etc_vconsoleconf);
                        return 0;
                }
        }

        r = prompt_keymap();
        if (r == -ENOENT)
                return 0; /* don't fail if no keymaps are installed */
        if (r < 0)
                return r;

        if (isempty(arg_keymap))
                return 0;

        keymap = STRV_MAKE(strjoina("KEYMAP=", arg_keymap));

        r = mkdir_parents(etc_vconsoleconf, 0755);
        if (r < 0)
                return log_error_errno(r, "Failed to create the parent directory of %s: %m", etc_vconsoleconf);

        r = write_env_file(etc_vconsoleconf, keymap);
        if (r < 0)
                return log_error_errno(r, "Failed to write %s: %m", etc_vconsoleconf);

        log_info("%s written.", etc_vconsoleconf);
        return 0;
}