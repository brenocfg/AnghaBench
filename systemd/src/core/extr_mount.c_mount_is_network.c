#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ fstype; int /*<<< orphan*/  options; } ;
typedef  TYPE_1__ MountParameters ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__ const*) ; 
 scalar_t__ fstab_test_option (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ fstype_is_network (scalar_t__) ; 

__attribute__((used)) static bool mount_is_network(const MountParameters *p) {
        assert(p);

        if (fstab_test_option(p->options, "_netdev\0"))
                return true;

        if (p->fstype && fstype_is_network(p->fstype))
                return true;

        return false;
}