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
typedef  int /*<<< orphan*/  sd_device ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctx ; 
 int log_error_errno (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  module_load_and_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  streq (char*,char*) ; 

__attribute__((used)) static int builtin_kmod(sd_device *dev, int argc, char *argv[], bool test) {
        int i;

        if (!ctx)
                return 0;

        if (argc < 3 || !streq(argv[1], "load"))
                return log_error_errno(SYNTHETIC_ERRNO(EINVAL),
                                       "%s: expected: load <module>", argv[0]);

        for (i = 2; argv[i]; i++)
                (void) module_load_and_warn(ctx, argv[i], false);

        return 0;
}