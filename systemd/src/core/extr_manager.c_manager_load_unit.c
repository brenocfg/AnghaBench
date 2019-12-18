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
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  int /*<<< orphan*/  Unit ;
typedef  int /*<<< orphan*/ * Manager ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  manager_dispatch_load_queue (int /*<<< orphan*/ **) ; 
 int manager_load_unit_prepare (int /*<<< orphan*/ **,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * unit_follow_merge (int /*<<< orphan*/ *) ; 

int manager_load_unit(
                Manager *m,
                const char *name,
                const char *path,
                sd_bus_error *e,
                Unit **_ret) {

        int r;

        assert(m);
        assert(_ret);

        /* This will load the service information files, but not actually
         * start any services or anything. */

        r = manager_load_unit_prepare(m, name, path, e, _ret);
        if (r != 0)
                return r;

        manager_dispatch_load_queue(m);

        *_ret = unit_follow_merge(*_ret);
        return 0;
}