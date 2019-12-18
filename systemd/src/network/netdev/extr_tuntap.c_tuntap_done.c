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
struct TYPE_9__ {scalar_t__ kind; void* group_name; void* user_name; } ;
typedef  TYPE_1__ TunTap ;
typedef  TYPE_1__ NetDev ;

/* Variables and functions */
 scalar_t__ NETDEV_KIND_TUN ; 
 TYPE_1__* TAP (TYPE_1__*) ; 
 TYPE_1__* TUN (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 void* mfree (void*) ; 

__attribute__((used)) static void tuntap_done(NetDev *netdev) {
        TunTap *t = NULL;

        assert(netdev);

        if (netdev->kind == NETDEV_KIND_TUN)
                t = TUN(netdev);
        else
                t = TAP(netdev);

        assert(t);

        t->user_name = mfree(t->user_name);
        t->group_name = mfree(t->group_name);
}