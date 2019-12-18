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
struct TYPE_9__ {int kind; int pmtudisc; int isatap; int /*<<< orphan*/  fou_encap_type; } ;
typedef  TYPE_1__ Tunnel ;
typedef  TYPE_1__ NetDev ;

/* Variables and functions */
 int /*<<< orphan*/  FOU_ENCAP_DIRECT ; 
 TYPE_1__* IPIP (TYPE_1__*) ; 
#define  NETDEV_KIND_IPIP 129 
#define  NETDEV_KIND_SIT 128 
 TYPE_1__* SIT (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  assert_not_reached (char*) ; 

__attribute__((used)) static void ipip_sit_init(NetDev *n) {
        Tunnel *t;

        assert(n);

        switch (n->kind) {
        case NETDEV_KIND_IPIP:
                t = IPIP(n);
                break;
        case NETDEV_KIND_SIT:
                t = SIT(n);
                break;
        default:
                assert_not_reached("invalid netdev kind");
        }

        assert(t);

        t->pmtudisc = true;
        t->fou_encap_type = FOU_ENCAP_DIRECT;
        t->isatap = -1;
}