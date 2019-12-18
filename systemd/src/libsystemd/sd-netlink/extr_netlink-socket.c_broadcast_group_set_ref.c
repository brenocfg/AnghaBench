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
struct TYPE_4__ {int /*<<< orphan*/  broadcast_group_refs; } ;
typedef  TYPE_1__ sd_netlink ;

/* Variables and functions */
 int /*<<< orphan*/  UINT_TO_PTR (unsigned int) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int hashmap_replace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int broadcast_group_set_ref(sd_netlink *nl, unsigned group, unsigned n_ref) {
        int r;

        assert(nl);

        r = hashmap_replace(nl->broadcast_group_refs, UINT_TO_PTR(group), UINT_TO_PTR(n_ref));
        if (r < 0)
                return r;

        return 0;
}