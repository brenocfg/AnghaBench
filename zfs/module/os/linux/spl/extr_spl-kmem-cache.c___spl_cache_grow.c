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
struct TYPE_6__ {int /*<<< orphan*/  sks_list; scalar_t__ sks_objs; } ;
typedef  TYPE_1__ spl_kmem_slab_t ;
struct TYPE_7__ {int /*<<< orphan*/  skc_lock; int /*<<< orphan*/  skc_waitq; int /*<<< orphan*/  skc_flags; int /*<<< orphan*/  skc_partial_list; int /*<<< orphan*/  skc_obj_total; int /*<<< orphan*/  skc_slab_total; } ;
typedef  TYPE_2__ spl_kmem_cache_t ;
typedef  int /*<<< orphan*/  fstrans_cookie_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  KMC_BIT_DEADLOCKED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  smp_mb__before_atomic () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spl_fstrans_mark () ; 
 int /*<<< orphan*/  spl_fstrans_unmark (int /*<<< orphan*/ ) ; 
 TYPE_1__* spl_slab_alloc (TYPE_2__*,int) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
__spl_cache_grow(spl_kmem_cache_t *skc, int flags)
{
	spl_kmem_slab_t *sks;

	fstrans_cookie_t cookie = spl_fstrans_mark();
	sks = spl_slab_alloc(skc, flags);
	spl_fstrans_unmark(cookie);

	spin_lock(&skc->skc_lock);
	if (sks) {
		skc->skc_slab_total++;
		skc->skc_obj_total += sks->sks_objs;
		list_add_tail(&sks->sks_list, &skc->skc_partial_list);

		smp_mb__before_atomic();
		clear_bit(KMC_BIT_DEADLOCKED, &skc->skc_flags);
		smp_mb__after_atomic();
		wake_up_all(&skc->skc_waitq);
	}
	spin_unlock(&skc->skc_lock);

	return (sks == NULL ? -ENOMEM : 0);
}