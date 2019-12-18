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
 scalar_t__ UNIT_FILE_SYSTEM ; 
 int /*<<< orphan*/  ansi_highlight_red () ; 
 int /*<<< orphan*/  ansi_normal () ; 
 scalar_t__ arg_scope ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int /*<<< orphan*/  log_warning (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char*) ; 

__attribute__((used)) static void warn_unit_file_changed(const char *name) {
        assert(name);

        log_warning("%sWarning:%s The unit file, source configuration file or drop-ins of %s changed on disk. Run 'systemctl%s daemon-reload' to reload units.",
                    ansi_highlight_red(),
                    ansi_normal(),
                    name,
                    arg_scope == UNIT_FILE_SYSTEM ? "" : " --user");
}