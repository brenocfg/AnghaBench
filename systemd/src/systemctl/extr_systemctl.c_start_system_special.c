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
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 scalar_t__ UNIT_FILE_GLOBAL ; 
 scalar_t__ UNIT_FILE_SYSTEM ; 
 scalar_t__ arg_scope ; 
 int log_error_errno (int /*<<< orphan*/ ,char*,char*) ; 
 int start_special (int,char**,void*) ; 

__attribute__((used)) static int start_system_special(int argc, char *argv[], void *userdata) {
        /* Like start_special above, but raises an error when running in user mode */

        if (arg_scope != UNIT_FILE_SYSTEM)
                return log_error_errno(SYNTHETIC_ERRNO(EINVAL),
                                       "Bad action for %s mode.",
                                       arg_scope == UNIT_FILE_GLOBAL ? "--global" : "--user");

        return start_special(argc, argv, userdata);
}