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
 int PTR_TO_UINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT_TO_PTR (unsigned int) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  hashmap_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned broadcast_group_get_ref(sd_netlink *nl, unsigned group) {
        assert(nl);

        return PTR_TO_UINT(hashmap_get(nl->broadcast_group_refs, UINT_TO_PTR(group)));
}