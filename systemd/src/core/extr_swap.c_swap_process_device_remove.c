#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sd_device ;
struct TYPE_3__ {int /*<<< orphan*/  swaps_by_devnode; } ;
typedef  int /*<<< orphan*/  Swap ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/ * hashmap_get (int /*<<< orphan*/ ,char const*) ; 
 int sd_device_get_devname (int /*<<< orphan*/ *,char const**) ; 
 int swap_set_devnode (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int swap_process_device_remove(Manager *m, sd_device *dev) {
        const char *dn;
        int r = 0;
        Swap *s;

        r = sd_device_get_devname(dev, &dn);
        if (r < 0)
                return 0;

        while ((s = hashmap_get(m->swaps_by_devnode, dn))) {
                int q;

                q = swap_set_devnode(s, NULL);
                if (q < 0)
                        r = q;
        }

        return r;
}