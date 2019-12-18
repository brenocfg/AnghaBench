#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  sa; scalar_t__ section; TYPE_1__* macsec; } ;
typedef  TYPE_2__ TransmitAssociation ;
struct TYPE_5__ {int /*<<< orphan*/  transmit_associations_by_section; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  network_config_section_free (scalar_t__) ; 
 int /*<<< orphan*/  ordered_hashmap_remove (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  security_association_clear (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void macsec_transmit_association_free(TransmitAssociation *a) {
        if (!a)
                return;

        if (a->macsec && a->section)
                ordered_hashmap_remove(a->macsec->transmit_associations_by_section, a->section);

        network_config_section_free(a->section);
        security_association_clear(&a->sa);

        free(a);
}