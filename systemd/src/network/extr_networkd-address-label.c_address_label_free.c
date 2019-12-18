#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ section; TYPE_1__* network; } ;
struct TYPE_6__ {scalar_t__ n_address_labels; int /*<<< orphan*/  address_labels_by_section; int /*<<< orphan*/  address_labels; } ;
typedef  TYPE_2__ AddressLabel ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  hashmap_remove (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  labels ; 
 int /*<<< orphan*/  network_config_section_free (scalar_t__) ; 

void address_label_free(AddressLabel *label) {
        if (!label)
                return;

        if (label->network) {
                LIST_REMOVE(labels, label->network->address_labels, label);
                assert(label->network->n_address_labels > 0);
                label->network->n_address_labels--;

                if (label->section) {
                        hashmap_remove(label->network->address_labels_by_section, label->section);
                        network_config_section_free(label->section);
                }
        }

        free(label);
}