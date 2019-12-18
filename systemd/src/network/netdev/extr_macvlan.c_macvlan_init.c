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
struct TYPE_9__ {scalar_t__ kind; int /*<<< orphan*/  mode; } ;
typedef  TYPE_1__ NetDev ;
typedef  TYPE_1__ MacVlan ;

/* Variables and functions */
 TYPE_1__* MACVLAN (TYPE_1__*) ; 
 TYPE_1__* MACVTAP (TYPE_1__*) ; 
 scalar_t__ NETDEV_KIND_MACVLAN ; 
 int /*<<< orphan*/  _NETDEV_MACVLAN_MODE_INVALID ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

__attribute__((used)) static void macvlan_init(NetDev *n) {
        MacVlan *m;

        assert(n);

        if (n->kind == NETDEV_KIND_MACVLAN)
                m = MACVLAN(n);
        else
                m = MACVTAP(n);

        assert(m);

        m->mode = _NETDEV_MACVLAN_MODE_INVALID;
}