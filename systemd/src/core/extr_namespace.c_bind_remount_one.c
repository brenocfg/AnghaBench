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
 unsigned long MS_BIND ; 
 unsigned long MS_REMOUNT ; 
 int errno ; 
 scalar_t__ mount (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bind_remount_one(const char *path, unsigned long orig_flags, unsigned long new_flags, unsigned long flags_mask) {
        if (mount(NULL, path, NULL, (orig_flags & ~flags_mask) | MS_REMOUNT | MS_BIND | new_flags, NULL) < 0)
                return -errno;

        return 0;
}