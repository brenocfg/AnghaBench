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
typedef  int /*<<< orphan*/  sd_netlink ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 unsigned int broadcast_group_get_ref (int /*<<< orphan*/ *,unsigned int) ; 
 int broadcast_group_leave (int /*<<< orphan*/ *,unsigned int) ; 
 int broadcast_group_set_ref (int /*<<< orphan*/ *,unsigned int,unsigned int) ; 

int socket_broadcast_group_unref(sd_netlink *nl, unsigned group) {
        unsigned n_ref;
        int r;

        assert(nl);

        n_ref = broadcast_group_get_ref(nl, group);

        assert(n_ref > 0);

        n_ref--;

        r = broadcast_group_set_ref(nl, group, n_ref);
        if (r < 0)
                return r;

        if (n_ref > 0)
                /* still refs left */
                return 0;

        r = broadcast_group_leave(nl, group);
        if (r < 0)
                return r;

        return 0;
}