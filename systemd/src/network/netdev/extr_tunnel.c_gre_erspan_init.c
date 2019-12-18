#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int kind; int pmtudisc; int gre_erspan_sequence; int /*<<< orphan*/  fou_encap_type; } ;
typedef  TYPE_1__ Tunnel ;
typedef  TYPE_1__ NetDev ;

/* Variables and functions */
 TYPE_1__* ERSPAN (TYPE_1__*) ; 
 int /*<<< orphan*/  FOU_ENCAP_DIRECT ; 
 TYPE_1__* GRE (TYPE_1__*) ; 
 TYPE_1__* GRETAP (TYPE_1__*) ; 
#define  NETDEV_KIND_ERSPAN 130 
#define  NETDEV_KIND_GRE 129 
#define  NETDEV_KIND_GRETAP 128 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  assert_not_reached (char*) ; 

__attribute__((used)) static void gre_erspan_init(NetDev *n) {
        Tunnel *t;

        assert(n);

        switch (n->kind) {
        case NETDEV_KIND_GRE:
                t = GRE(n);
                break;
        case NETDEV_KIND_ERSPAN:
                t = ERSPAN(n);
                break;
        case NETDEV_KIND_GRETAP:
                t = GRETAP(n);
                break;
        default:
                assert_not_reached("invalid netdev kind");
        }

        assert(t);

        t->pmtudisc = true;
        t->gre_erspan_sequence = -1;
        t->fou_encap_type = FOU_ENCAP_DIRECT;
}