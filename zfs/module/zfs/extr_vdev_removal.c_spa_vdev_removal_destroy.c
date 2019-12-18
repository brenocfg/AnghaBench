#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  svr_cv; int /*<<< orphan*/  svr_lock; int /*<<< orphan*/  svr_allocd_segs; int /*<<< orphan*/ * svr_new_segments; int /*<<< orphan*/ * svr_frees; int /*<<< orphan*/ * svr_max_offset_to_sync; int /*<<< orphan*/ * svr_bytes_done; } ;
typedef  TYPE_1__ spa_vdev_removal_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT0 (int /*<<< orphan*/ ) ; 
 int TXG_SIZE ; 
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  list_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  range_tree_destroy (int /*<<< orphan*/ ) ; 

void
spa_vdev_removal_destroy(spa_vdev_removal_t *svr)
{
	for (int i = 0; i < TXG_SIZE; i++) {
		ASSERT0(svr->svr_bytes_done[i]);
		ASSERT0(svr->svr_max_offset_to_sync[i]);
		range_tree_destroy(svr->svr_frees[i]);
		list_destroy(&svr->svr_new_segments[i]);
	}

	range_tree_destroy(svr->svr_allocd_segs);
	mutex_destroy(&svr->svr_lock);
	cv_destroy(&svr->svr_cv);
	kmem_free(svr, sizeof (*svr));
}