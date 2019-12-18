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
struct TYPE_9__ {scalar_t__ kind; int /*<<< orphan*/  ttl; } ;
typedef  TYPE_1__ Tunnel ;
typedef  TYPE_1__ NetDev ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_TNL_HOP_LIMIT ; 
 TYPE_1__* IP6GRE (TYPE_1__*) ; 
 TYPE_1__* IP6GRETAP (TYPE_1__*) ; 
 scalar_t__ NETDEV_KIND_IP6GRE ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

__attribute__((used)) static void ip6gre_init(NetDev *n) {
        Tunnel *t;

        assert(n);

        if (n->kind == NETDEV_KIND_IP6GRE)
                t = IP6GRE(n);
        else
                t = IP6GRETAP(n);

        assert(t);

        t->ttl = DEFAULT_TNL_HOP_LIMIT;
}