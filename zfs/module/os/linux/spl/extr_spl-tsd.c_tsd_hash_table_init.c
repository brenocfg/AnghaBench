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
typedef  int uint_t ;
struct TYPE_6__ {int ht_bits; int ht_key; int /*<<< orphan*/  ht_lock; TYPE_1__* ht_bins; } ;
typedef  TYPE_2__ tsd_hash_table_t ;
typedef  int /*<<< orphan*/  tsd_hash_bin_t ;
struct TYPE_5__ {int /*<<< orphan*/  hb_head; int /*<<< orphan*/  hb_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  kmem_free (TYPE_2__*,int) ; 
 void* kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static tsd_hash_table_t *
tsd_hash_table_init(uint_t bits)
{
	tsd_hash_table_t *table;
	int hash, size = (1 << bits);

	table = kmem_zalloc(sizeof (tsd_hash_table_t), KM_SLEEP);
	if (table == NULL)
		return (NULL);

	table->ht_bins = kmem_zalloc(sizeof (tsd_hash_bin_t) * size, KM_SLEEP);
	if (table->ht_bins == NULL) {
		kmem_free(table, sizeof (tsd_hash_table_t));
		return (NULL);
	}

	for (hash = 0; hash < size; hash++) {
		spin_lock_init(&table->ht_bins[hash].hb_lock);
		INIT_HLIST_HEAD(&table->ht_bins[hash].hb_head);
	}

	spin_lock_init(&table->ht_lock);
	table->ht_bits = bits;
	table->ht_key = 1;

	return (table);
}