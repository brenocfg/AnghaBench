#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ state; int /*<<< orphan*/  conditions; int /*<<< orphan*/  mac; int /*<<< orphan*/  ifname; int /*<<< orphan*/  description; int /*<<< orphan*/  filename; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* done ) (TYPE_1__*) ;} ;
typedef  TYPE_1__ NetDev ;

/* Variables and functions */
 TYPE_10__* NETDEV_VTABLE (TYPE_1__*) ; 
 scalar_t__ _NETDEV_STATE_INVALID ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  condition_free_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 TYPE_1__* mfree (TYPE_1__*) ; 
 int /*<<< orphan*/  netdev_callbacks_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  netdev_detach_from_manager (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static NetDev *netdev_free(NetDev *netdev) {
        assert(netdev);

        netdev_callbacks_clear(netdev);

        netdev_detach_from_manager(netdev);

        free(netdev->filename);

        free(netdev->description);
        free(netdev->ifname);
        free(netdev->mac);
        condition_free_list(netdev->conditions);

        /* Invoke the per-kind done() destructor, but only if the state field is initialized. We conditionalize that
         * because we parse .netdev files twice: once to determine the kind (with a short, minimal NetDev structure
         * allocation, with no room for per-kind fields), and once to read the kind's properties (with a full,
         * comprehensive NetDev structure allocation with enough space for whatever the specific kind needs). Now, in
         * the first case we shouldn't try to destruct the per-kind NetDev fields on destruction, in the second case we
         * should. We use the state field to discern the two cases: it's _NETDEV_STATE_INVALID on the first "raw"
         * call. */
        if (netdev->state != _NETDEV_STATE_INVALID &&
            NETDEV_VTABLE(netdev) &&
            NETDEV_VTABLE(netdev)->done)
                NETDEV_VTABLE(netdev)->done(netdev);

        return mfree(netdev);
}