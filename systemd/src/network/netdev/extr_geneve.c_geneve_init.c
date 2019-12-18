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
struct TYPE_7__ {int udpcsum; int udp6zerocsumtx; int udp6zerocsumrx; int /*<<< orphan*/  dest_port; int /*<<< orphan*/  geneve_df; scalar_t__ id; } ;
typedef  TYPE_1__ NetDev ;
typedef  TYPE_1__ Geneve ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_GENEVE_DESTINATION_PORT ; 
 TYPE_1__* GENEVE (TYPE_1__*) ; 
 scalar_t__ GENEVE_VID_MAX ; 
 int /*<<< orphan*/  _NETDEV_GENEVE_DF_INVALID ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

__attribute__((used)) static void geneve_init(NetDev *netdev) {
        Geneve *v;

        assert(netdev);

        v = GENEVE(netdev);

        assert(v);

        v->id = GENEVE_VID_MAX + 1;
        v->geneve_df = _NETDEV_GENEVE_DF_INVALID;
        v->dest_port = DEFAULT_GENEVE_DESTINATION_PORT;
        v->udpcsum = false;
        v->udp6zerocsumtx = false;
        v->udp6zerocsumrx = false;
}