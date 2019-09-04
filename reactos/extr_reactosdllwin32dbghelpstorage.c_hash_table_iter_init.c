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
struct hash_table_iter {int last; int index; int /*<<< orphan*/ * element; struct hash_table const* ht; } ;
struct hash_table {int num_buckets; } ;

/* Variables and functions */
 int hash_table_hash (char const*,int) ; 

void hash_table_iter_init(const struct hash_table* ht, 
                          struct hash_table_iter* hti, const char* name)
{
    hti->ht = ht;
    if (name)
    {
        hti->last = hash_table_hash(name, ht->num_buckets);
        hti->index = hti->last - 1;
    }
    else
    {
        hti->last = ht->num_buckets - 1;
        hti->index = -1;
    }
    hti->element = NULL;
}