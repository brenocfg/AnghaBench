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
 int /*<<< orphan*/  WRITE_STRING_FILE_DISABLE_BUFFER ; 
 int /*<<< orphan*/  enable_disable (int) ; 
 int /*<<< orphan*/  log_debug (char*,int /*<<< orphan*/ ) ; 
 int log_warning_errno (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  one_zero (int) ; 
 int write_string_file (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int toggle_utf8_sysfs(bool utf8) {
        int r;

        r = write_string_file("/sys/module/vt/parameters/default_utf8", one_zero(utf8), WRITE_STRING_FILE_DISABLE_BUFFER);
        if (r < 0)
                return log_warning_errno(r, "Failed to %s sysfs UTF-8 flag: %m", enable_disable(utf8));

        log_debug("Sysfs UTF-8 flag %sd", enable_disable(utf8));
        return 0;
}