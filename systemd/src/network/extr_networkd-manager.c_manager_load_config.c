#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  networks; int /*<<< orphan*/  network_dirs_ts_usec; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  NETWORK_DIRS ; 
 int netdev_load (TYPE_1__*,int) ; 
 int network_load (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  paths_check_timestamp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int manager_load_config(Manager *m) {
        int r;

        /* update timestamp */
        paths_check_timestamp(NETWORK_DIRS, &m->network_dirs_ts_usec, true);

        r = netdev_load(m, false);
        if (r < 0)
                return r;

        r = network_load(m, &m->networks);
        if (r < 0)
                return r;

        return 0;
}