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
 int ENOENT ; 
 int /*<<< orphan*/  assert (char**) ; 
 int log_debug_errno (int,char*) ; 
 int read_one_line_file (char*,char**) ; 

int read_reboot_parameter(char **parameter) {
        int r;

        assert(parameter);

        r = read_one_line_file("/run/systemd/reboot-param", parameter);
        if (r < 0 && r != -ENOENT)
                return log_debug_errno(r, "Failed to read /run/systemd/reboot-param: %m");

        return 0;
}