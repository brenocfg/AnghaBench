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
typedef  int /*<<< orphan*/  sd_bus ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 int log_error_errno (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ path_equal (char const*,char*) ; 
 int /*<<< orphan*/  path_is_normalized (char const*) ; 
 int stop_mount (int /*<<< orphan*/ *,char const*,char*) ; 

__attribute__((used)) static int stop_mounts(
                sd_bus *bus,
                const char *where) {

        int r;

        if (path_equal(where, "/"))
                return log_error_errno(SYNTHETIC_ERRNO(EINVAL),
                                       "Refusing to operate on root directory: %s", where);

        if (!path_is_normalized(where))
                return log_error_errno(SYNTHETIC_ERRNO(EINVAL),
                                       "Path contains non-normalized components: %s", where);

        r = stop_mount(bus, where, ".mount");
        if (r < 0)
                return r;

        r = stop_mount(bus, where, ".automount");
        if (r < 0)
                return r;

        return 0;
}