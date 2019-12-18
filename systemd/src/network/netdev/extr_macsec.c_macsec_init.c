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
struct TYPE_7__ {int encrypt; } ;
typedef  TYPE_1__ NetDev ;
typedef  TYPE_1__ MACsec ;

/* Variables and functions */
 TYPE_1__* MACSEC (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

__attribute__((used)) static void macsec_init(NetDev *netdev) {
        MACsec *v;

        assert(netdev);

        v = MACSEC(netdev);

        assert(v);

        v->encrypt = -1;
}