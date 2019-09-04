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
struct hash_table {unsigned int nr; int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  grow_hash_table (struct hash_table*) ; 
 void** insert_hash_entry (unsigned int,void*,struct hash_table*) ; 

void **insert_hash(unsigned int hash, void *ptr, struct hash_table *table)
{
    unsigned int nr = table->nr;
    if (nr >= table->size/2)
        grow_hash_table(table);
    return insert_hash_entry(hash, ptr, table);
}