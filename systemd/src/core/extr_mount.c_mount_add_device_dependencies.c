#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UnitDependencyMask ;
typedef  int /*<<< orphan*/  UnitDependency ;
struct TYPE_11__ {scalar_t__ from_proc_self_mountinfo; int /*<<< orphan*/  where; } ;
struct TYPE_10__ {int /*<<< orphan*/  what; } ;
typedef  TYPE_1__ MountParameters ;
typedef  TYPE_2__ Mount ;

/* Variables and functions */
 int /*<<< orphan*/  UNIT (TYPE_2__*) ; 
 int /*<<< orphan*/  UNIT_BINDS_TO ; 
 int /*<<< orphan*/  UNIT_DEPENDENCY_FILE ; 
 int /*<<< orphan*/  UNIT_DEPENDENCY_MOUNTINFO_IMPLICIT ; 
 int /*<<< orphan*/  UNIT_REQUIRES ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 TYPE_1__* get_mount_parameters (TYPE_2__*) ; 
 int /*<<< orphan*/  is_device_path (int /*<<< orphan*/ ) ; 
 scalar_t__ mount_is_bind (TYPE_1__*) ; 
 scalar_t__ mount_is_bound_to_device (TYPE_2__*) ; 
 scalar_t__ path_equal (int /*<<< orphan*/ ,char*) ; 
 int unit_add_node_dependency (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mount_add_device_dependencies(Mount *m) {
        UnitDependencyMask mask;
        MountParameters *p;
        UnitDependency dep;
        int r;

        assert(m);

        p = get_mount_parameters(m);
        if (!p)
                return 0;

        if (!p->what)
                return 0;

        if (mount_is_bind(p))
                return 0;

        if (!is_device_path(p->what))
                return 0;

        /* /dev/root is a really weird thing, it's not a real device,
         * but just a path the kernel exports for the root file system
         * specified on the kernel command line. Ignore it here. */
        if (path_equal(p->what, "/dev/root"))
                return 0;

        if (path_equal(m->where, "/"))
                return 0;

        /* Mount units from /proc/self/mountinfo are not bound to devices
         * by default since they're subject to races when devices are
         * unplugged. But the user can still force this dep with an
         * appropriate option (or udev property) so the mount units are
         * automatically stopped when the device disappears suddenly. */
        dep = mount_is_bound_to_device(m) ? UNIT_BINDS_TO : UNIT_REQUIRES;

        /* We always use 'what' from /proc/self/mountinfo if mounted */
        mask = m->from_proc_self_mountinfo ? UNIT_DEPENDENCY_MOUNTINFO_IMPLICIT : UNIT_DEPENDENCY_FILE;

        r = unit_add_node_dependency(UNIT(m), p->what, dep, mask);
        if (r < 0)
                return r;

        return 0;
}