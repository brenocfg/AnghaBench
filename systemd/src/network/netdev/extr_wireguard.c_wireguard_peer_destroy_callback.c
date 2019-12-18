#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  section; struct TYPE_6__* wireguard; } ;
typedef  TYPE_1__ WireguardPeer ;
typedef  int /*<<< orphan*/  NetDev ;

/* Variables and functions */
 int /*<<< orphan*/ * NETDEV (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  netdev_unref (int /*<<< orphan*/ *) ; 
 scalar_t__ section_is_invalid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wireguard_peer_free (TYPE_1__*) ; 

__attribute__((used)) static void wireguard_peer_destroy_callback(WireguardPeer *peer) {
        NetDev *netdev;

        assert(peer);
        assert(peer->wireguard);

        netdev = NETDEV(peer->wireguard);

        if (section_is_invalid(peer->section))
                wireguard_peer_free(peer);

        netdev_unref(netdev);
}