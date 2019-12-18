#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct list_head {int dummy; } ;
struct TYPE_4__ {scalar_t__ sks_magic; scalar_t__ sks_ref; int /*<<< orphan*/  sks_free_list; int /*<<< orphan*/  sks_list; scalar_t__ sks_objs; TYPE_2__* sks_cache; } ;
typedef  TYPE_1__ spl_kmem_slab_t ;
struct TYPE_5__ {scalar_t__ skc_magic; int /*<<< orphan*/  skc_slab_total; int /*<<< orphan*/  skc_obj_total; } ;
typedef  TYPE_2__ spl_kmem_cache_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ SKC_MAGIC ; 
 scalar_t__ SKS_MAGIC ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_splice_init (int /*<<< orphan*/ *,struct list_head*) ; 

__attribute__((used)) static void
spl_slab_free(spl_kmem_slab_t *sks,
    struct list_head *sks_list, struct list_head *sko_list)
{
	spl_kmem_cache_t *skc;

	ASSERT(sks->sks_magic == SKS_MAGIC);
	ASSERT(sks->sks_ref == 0);

	skc = sks->sks_cache;
	ASSERT(skc->skc_magic == SKC_MAGIC);

	/*
	 * Update slab/objects counters in the cache, then remove the
	 * slab from the skc->skc_partial_list.  Finally add the slab
	 * and all its objects in to the private work lists where the
	 * destructors will be called and the memory freed to the system.
	 */
	skc->skc_obj_total -= sks->sks_objs;
	skc->skc_slab_total--;
	list_del(&sks->sks_list);
	list_add(&sks->sks_list, sks_list);
	list_splice_init(&sks->sks_free_list, sko_list);
}