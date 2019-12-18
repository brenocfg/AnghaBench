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
struct TYPE_7__ {int /*<<< orphan*/  mac_peer; int /*<<< orphan*/  ifname_peer; } ;
typedef  TYPE_1__ Veth ;
typedef  TYPE_1__ NetDev ;

/* Variables and functions */
 TYPE_1__* VETH (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void veth_done(NetDev *n) {
        Veth *v;

        assert(n);

        v = VETH(n);

        assert(v);

        free(v->ifname_peer);
        free(v->mac_peer);
}