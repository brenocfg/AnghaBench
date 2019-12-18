#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  description; int /*<<< orphan*/  id; scalar_t__ fragment_path; } ;
typedef  TYPE_1__ Unit ;
struct TYPE_16__ {int from_fragment; int /*<<< orphan*/  exec_context; int /*<<< orphan*/  where; } ;
typedef  TYPE_2__ Mount ;

/* Variables and functions */
 TYPE_1__* UNIT (TYPE_2__*) ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int mount_add_default_dependencies (TYPE_2__*) ; 
 int mount_add_device_dependencies (TYPE_2__*) ; 
 int mount_add_mount_dependencies (TYPE_2__*) ; 
 int mount_add_quota_dependencies (TYPE_2__*) ; 
 int /*<<< orphan*/  path_simplify (int /*<<< orphan*/ ,int) ; 
 int unit_add_exec_dependencies (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int unit_name_to_path (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int unit_patch_contexts (TYPE_1__*) ; 
 int unit_set_default_slice (TYPE_1__*) ; 
 int unit_set_description (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mount_add_extras(Mount *m) {
        Unit *u = UNIT(m);
        int r;

        assert(m);

        /* Note: this call might be called after we already have been loaded once (and even when it has already been
         * activated), in case data from /proc/self/mountinfo has changed. This means all code here needs to be ready
         * to run with an already set up unit. */

        if (u->fragment_path)
                m->from_fragment = true;

        if (!m->where) {
                r = unit_name_to_path(u->id, &m->where);
                if (r < 0)
                        return r;
        }

        path_simplify(m->where, false);

        if (!u->description) {
                r = unit_set_description(u, m->where);
                if (r < 0)
                        return r;
        }

        r = mount_add_device_dependencies(m);
        if (r < 0)
                return r;

        r = mount_add_mount_dependencies(m);
        if (r < 0)
                return r;

        r = mount_add_quota_dependencies(m);
        if (r < 0)
                return r;

        r = unit_patch_contexts(u);
        if (r < 0)
                return r;

        r = unit_add_exec_dependencies(u, &m->exec_context);
        if (r < 0)
                return r;

        r = unit_set_default_slice(u);
        if (r < 0)
                return r;

        r = mount_add_default_dependencies(m);
        if (r < 0)
                return r;

        return 0;
}