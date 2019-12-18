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
 int /*<<< orphan*/  SPECIAL_LOCAL_FS_TARGET ; 
 scalar_t__ VOLATILE_STATE ; 
 int add_mount (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  arg_dest_late ; 
 scalar_t__ arg_volatile_mode ; 

__attribute__((used)) static int add_volatile_var(void) {

        if (arg_volatile_mode != VOLATILE_STATE)
                return 0;

        /* If requested, mount /var as tmpfs, but do so only if there's nothing else defined for this. */

        return add_mount(arg_dest_late,
                         "tmpfs",
                         "/var",
                         NULL,
                         "tmpfs",
                         "mode=0755",
                         0,
                         0,
                         SPECIAL_LOCAL_FS_TARGET,
                         "/proc/cmdline");
}