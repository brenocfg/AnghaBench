#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  options; } ;
struct TYPE_5__ {TYPE_1__ parameters_proc_self_mountinfo; scalar_t__ from_fragment; } ;
typedef  TYPE_1__ MountParameters ;
typedef  TYPE_2__ Mount ;

/* Variables and functions */
 int fstab_test_option (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool mount_is_bound_to_device(const Mount *m) {
        const MountParameters *p;

        if (m->from_fragment)
                return true;

        p = &m->parameters_proc_self_mountinfo;
        return fstab_test_option(p->options, "x-systemd.device-bound\0");
}