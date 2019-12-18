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
 int errno ; 
 int maybe_setgroups (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ setresgid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ setresuid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int reset_uid_gid(void) {
        int r;

        r = maybe_setgroups(0, NULL);
        if (r < 0)
                return r;

        if (setresgid(0, 0, 0) < 0)
                return -errno;

        if (setresuid(0, 0, 0) < 0)
                return -errno;

        return 0;
}