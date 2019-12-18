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
struct TYPE_7__ {int /*<<< orphan*/  sessions_by_section; } ;
typedef  TYPE_1__ NetDev ;
typedef  TYPE_1__ L2tpTunnel ;

/* Variables and functions */
 TYPE_1__* L2TP (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  l2tp_session_free ; 
 int /*<<< orphan*/  ordered_hashmap_free_with_destructor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void l2tp_tunnel_done(NetDev *netdev) {
        L2tpTunnel *t;

        assert(netdev);

        t = L2TP(netdev);

        assert(t);

        ordered_hashmap_free_with_destructor(t->sessions_by_section, l2tp_session_free);
}