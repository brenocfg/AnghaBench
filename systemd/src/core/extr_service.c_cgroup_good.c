#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  cgroup_path; } ;
typedef  int /*<<< orphan*/  Service ;

/* Variables and functions */
 int /*<<< orphan*/  SYSTEMD_CGROUP_CONTROLLER ; 
 TYPE_1__* UNIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int cg_is_empty_recursive (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cgroup_good(Service *s) {
        int r;

        assert(s);

        /* Returns 0 if the cgroup is empty or doesn't exist, > 0 if it is exists and is populated, < 0 if we can't
         * figure it out */

        if (!UNIT(s)->cgroup_path)
                return 0;

        r = cg_is_empty_recursive(SYSTEMD_CGROUP_CONTROLLER, UNIT(s)->cgroup_path);
        if (r < 0)
                return r;

        return r == 0;
}