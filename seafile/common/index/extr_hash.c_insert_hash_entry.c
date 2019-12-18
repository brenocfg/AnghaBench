#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct hash_table_entry {void* ptr; unsigned int hash; } ;
struct hash_table {int /*<<< orphan*/  nr; } ;

/* Variables and functions */
 struct hash_table_entry* lookup_hash_entry (unsigned int,struct hash_table*) ; 

__attribute__((used)) static void **insert_hash_entry(unsigned int hash, void *ptr, struct hash_table *table)
{
    struct hash_table_entry *entry = lookup_hash_entry(hash, table);

    if (!entry->ptr) {
        entry->ptr = ptr;
        entry->hash = hash;
        table->nr++;
        return NULL;
    }
    return &entry->ptr;
}