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
 int /*<<< orphan*/  delete_rule (char const*) ; 
 int log_error_errno (int,char*) ; 
 int write_string_file (char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int apply_rule(const char *rule) {
        int r;

        (void) delete_rule(rule);

        r = write_string_file("/proc/sys/fs/binfmt_misc/register", rule, WRITE_STRING_FILE_DISABLE_BUFFER);
        if (r < 0)
                return log_error_errno(r, "Failed to add binary format: %m");

        return 0;
}