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
struct TYPE_6__ {int /*<<< orphan*/  ske_obj; int /*<<< orphan*/  ske_node; } ;
typedef  TYPE_1__ spl_kmem_emergency_t ;
struct TYPE_7__ {int /*<<< orphan*/  skc_lock; int /*<<< orphan*/  skc_obj_total; int /*<<< orphan*/  skc_obj_emergency; int /*<<< orphan*/  skc_emergency_tree; int /*<<< orphan*/  skc_obj_size; } ;
typedef  TYPE_2__ spl_kmem_cache_t ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  free_pages (int /*<<< orphan*/ ,int) ; 
 int get_order (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* spl_emergency_search (int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static int
spl_emergency_free(spl_kmem_cache_t *skc, void *obj)
{
	spl_kmem_emergency_t *ske;
	int order = get_order(skc->skc_obj_size);

	spin_lock(&skc->skc_lock);
	ske = spl_emergency_search(&skc->skc_emergency_tree, obj);
	if (ske) {
		rb_erase(&ske->ske_node, &skc->skc_emergency_tree);
		skc->skc_obj_emergency--;
		skc->skc_obj_total--;
	}
	spin_unlock(&skc->skc_lock);

	if (ske == NULL)
		return (-ENOENT);

	free_pages(ske->ske_obj, order);
	kfree(ske);

	return (0);
}