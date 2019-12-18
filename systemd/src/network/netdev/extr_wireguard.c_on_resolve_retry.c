#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usec_t ;
typedef  int /*<<< orphan*/  sd_event_source ;
struct TYPE_9__ {int /*<<< orphan*/  peers_with_failed_endpoint; int /*<<< orphan*/  peers_with_unresolved_endpoint; } ;
typedef  TYPE_1__ Wireguard ;
typedef  TYPE_1__ NetDev ;

/* Variables and functions */
 int /*<<< orphan*/  SWAP_TWO (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* WIREGUARD (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  netdev_is_managed (TYPE_1__*) ; 
 int /*<<< orphan*/  resolve_endpoints (TYPE_1__*) ; 
 TYPE_1__* set_isempty (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int on_resolve_retry(sd_event_source *s, usec_t usec, void *userdata) {
        NetDev *netdev = userdata;
        Wireguard *w;

        assert(netdev);
        w = WIREGUARD(netdev);
        assert(w);

        if (!netdev_is_managed(netdev))
                return 0;

        assert(set_isempty(w->peers_with_unresolved_endpoint));

        SWAP_TWO(w->peers_with_unresolved_endpoint, w->peers_with_failed_endpoint);

        resolve_endpoints(netdev);

        return 0;
}