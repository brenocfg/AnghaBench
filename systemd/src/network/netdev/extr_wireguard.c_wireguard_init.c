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
struct TYPE_7__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ Wireguard ;
typedef  TYPE_1__ NetDev ;

/* Variables and functions */
 int /*<<< orphan*/  WGDEVICE_F_REPLACE_PEERS ; 
 TYPE_1__* WIREGUARD (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

__attribute__((used)) static void wireguard_init(NetDev *netdev) {
        Wireguard *w;

        assert(netdev);
        w = WIREGUARD(netdev);
        assert(w);

        w->flags = WGDEVICE_F_REPLACE_PEERS;
}