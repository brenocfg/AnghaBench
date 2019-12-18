#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  broadcast_group_refs; } ;
typedef  TYPE_1__ sd_netlink ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 unsigned int broadcast_group_get_ref (TYPE_1__*,unsigned int) ; 
 int broadcast_group_join (TYPE_1__*,unsigned int) ; 
 int broadcast_group_set_ref (TYPE_1__*,unsigned int,unsigned int) ; 
 int hashmap_ensure_allocated (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int socket_broadcast_group_ref(sd_netlink *nl, unsigned group) {
        unsigned n_ref;
        int r;

        assert(nl);

        n_ref = broadcast_group_get_ref(nl, group);

        n_ref++;

        r = hashmap_ensure_allocated(&nl->broadcast_group_refs, NULL);
        if (r < 0)
                return r;

        r = broadcast_group_set_ref(nl, group, n_ref);
        if (r < 0)
                return r;

        if (n_ref > 1)
                /* not yet in the group */
                return 0;

        r = broadcast_group_join(nl, group);
        if (r < 0)
                return r;

        return 0;
}