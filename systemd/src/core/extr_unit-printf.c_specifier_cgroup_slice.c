#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* manager; scalar_t__ cgroup_path; int /*<<< orphan*/  slice; } ;
typedef  TYPE_2__ Unit ;
struct TYPE_7__ {scalar_t__ cgroup_root; } ;

/* Variables and functions */
 int ENOMEM ; 
 TYPE_2__* UNIT_DEREF (int /*<<< orphan*/ ) ; 
 scalar_t__ UNIT_ISSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_2__ const*) ; 
 int /*<<< orphan*/  bad_specifier (TYPE_2__ const*,char) ; 
 char* strdup (scalar_t__) ; 
 char* unit_default_cgroup_path (TYPE_2__ const*) ; 

__attribute__((used)) static int specifier_cgroup_slice(char specifier, const void *data, const void *userdata, char **ret) {
        const Unit *u = userdata;
        char *n;

        assert(u);

        bad_specifier(u, specifier);

        if (UNIT_ISSET(u->slice)) {
                const Unit *slice;

                slice = UNIT_DEREF(u->slice);

                if (slice->cgroup_path)
                        n = strdup(slice->cgroup_path);
                else
                        n = unit_default_cgroup_path(slice);
        } else
                n = strdup(u->manager->cgroup_root);
        if (!n)
                return -ENOMEM;

        *ret = n;
        return 0;
}