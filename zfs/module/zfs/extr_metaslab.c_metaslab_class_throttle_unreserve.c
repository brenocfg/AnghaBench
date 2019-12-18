#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zio_t ;
struct TYPE_3__ {int /*<<< orphan*/  mc_lock; int /*<<< orphan*/ * mc_alloc_slots; int /*<<< orphan*/  mc_alloc_throttle_enabled; } ;
typedef  TYPE_1__ metaslab_class_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_refcount_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
metaslab_class_throttle_unreserve(metaslab_class_t *mc, int slots,
    int allocator, zio_t *zio)
{
	ASSERT(mc->mc_alloc_throttle_enabled);
	mutex_enter(&mc->mc_lock);
	for (int d = 0; d < slots; d++) {
		(void) zfs_refcount_remove(&mc->mc_alloc_slots[allocator],
		    zio);
	}
	mutex_exit(&mc->mc_lock);
}