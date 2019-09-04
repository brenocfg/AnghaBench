#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hash_table {int /*<<< orphan*/  array; } ;
struct TYPE_2__ {void* ptr; } ;

/* Variables and functions */
 TYPE_1__* lookup_hash_entry (unsigned int,struct hash_table const*) ; 

void *lookup_hash(unsigned int hash, const struct hash_table *table)
{
    if (!table->array)
        return NULL;
    return lookup_hash_entry(hash, table)->ptr;
}