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
struct TYPE_6__ {scalar_t__ n_static_fdb_entries; int /*<<< orphan*/  fdb_entries_by_section; int /*<<< orphan*/  static_fdb_entries; } ;
typedef  TYPE_2__ FdbEntry ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  hashmap_remove (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  network_config_section_free (scalar_t__) ; 
 int /*<<< orphan*/  static_fdb_entries ; 

void fdb_entry_free(FdbEntry *fdb_entry) {
        if (!fdb_entry)
                return;

        if (fdb_entry->network) {
                LIST_REMOVE(static_fdb_entries, fdb_entry->network->static_fdb_entries, fdb_entry);
                assert(fdb_entry->network->n_static_fdb_entries > 0);
                fdb_entry->network->n_static_fdb_entries--;

                if (fdb_entry->section)
                        hashmap_remove(fdb_entry->network->fdb_entries_by_section, fdb_entry->section);
        }

        network_config_section_free(fdb_entry->section);
        free(fdb_entry);
}