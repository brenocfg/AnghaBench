#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ ske_obj; } ;
typedef  TYPE_1__ spl_kmem_emergency_t ;
struct TYPE_8__ {scalar_t__ skc_obj_emergency; scalar_t__ skc_obj_emergency_max; int /*<<< orphan*/  skc_lock; int /*<<< orphan*/  skc_obj_total; int /*<<< orphan*/  skc_emergency_tree; int /*<<< orphan*/  skc_partial_list; int /*<<< orphan*/  skc_obj_size; } ;
typedef  TYPE_2__ spl_kmem_cache_t ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ __get_free_pages (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free_pages (scalar_t__,int) ; 
 int get_order (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_1__* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_flags_convert (int) ; 
 scalar_t__ likely (int) ; 
 int list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int spl_emergency_insert (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
spl_emergency_alloc(spl_kmem_cache_t *skc, int flags, void **obj)
{
	gfp_t lflags = kmem_flags_convert(flags);
	spl_kmem_emergency_t *ske;
	int order = get_order(skc->skc_obj_size);
	int empty;

	/* Last chance use a partial slab if one now exists */
	spin_lock(&skc->skc_lock);
	empty = list_empty(&skc->skc_partial_list);
	spin_unlock(&skc->skc_lock);
	if (!empty)
		return (-EEXIST);

	ske = kmalloc(sizeof (*ske), lflags);
	if (ske == NULL)
		return (-ENOMEM);

	ske->ske_obj = __get_free_pages(lflags, order);
	if (ske->ske_obj == 0) {
		kfree(ske);
		return (-ENOMEM);
	}

	spin_lock(&skc->skc_lock);
	empty = spl_emergency_insert(&skc->skc_emergency_tree, ske);
	if (likely(empty)) {
		skc->skc_obj_total++;
		skc->skc_obj_emergency++;
		if (skc->skc_obj_emergency > skc->skc_obj_emergency_max)
			skc->skc_obj_emergency_max = skc->skc_obj_emergency;
	}
	spin_unlock(&skc->skc_lock);

	if (unlikely(!empty)) {
		free_pages(ske->ske_obj, order);
		kfree(ske);
		return (-EINVAL);
	}

	*obj = (void *)ske->ske_obj;

	return (0);
}