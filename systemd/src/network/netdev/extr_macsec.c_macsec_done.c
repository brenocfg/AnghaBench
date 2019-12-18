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
struct TYPE_7__ {int /*<<< orphan*/  receive_associations_by_section; int /*<<< orphan*/  transmit_associations_by_section; int /*<<< orphan*/  receive_channels_by_section; int /*<<< orphan*/  receive_channels; } ;
typedef  TYPE_1__ NetDev ;
typedef  TYPE_1__ MACsec ;

/* Variables and functions */
 TYPE_1__* MACSEC (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  macsec_receive_association_free ; 
 int /*<<< orphan*/  macsec_receive_channel_free ; 
 int /*<<< orphan*/  macsec_transmit_association_free ; 
 int /*<<< orphan*/  ordered_hashmap_free_with_destructor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void macsec_done(NetDev *netdev) {
        MACsec *t;

        assert(netdev);

        t = MACSEC(netdev);

        assert(t);

        ordered_hashmap_free_with_destructor(t->receive_channels, macsec_receive_channel_free);
        ordered_hashmap_free_with_destructor(t->receive_channels_by_section, macsec_receive_channel_free);
        ordered_hashmap_free_with_destructor(t->transmit_associations_by_section, macsec_transmit_association_free);
        ordered_hashmap_free_with_destructor(t->receive_associations_by_section, macsec_receive_association_free);
}