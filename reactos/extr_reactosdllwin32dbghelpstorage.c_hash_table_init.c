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
struct pool {int dummy; } ;
struct hash_table {unsigned int num_buckets; int /*<<< orphan*/ * buckets; struct pool* pool; scalar_t__ num_elts; } ;

/* Variables and functions */

void hash_table_init(struct pool* pool, struct hash_table* ht, unsigned num_buckets)
{
    ht->num_elts = 0;
    ht->num_buckets = num_buckets;
    ht->pool = pool;
    ht->buckets = NULL;
}