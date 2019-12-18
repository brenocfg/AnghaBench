#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  rl_lock; int /*<<< orphan*/  rl_tree; } ;
typedef  TYPE_1__ zfs_rangelock_t ;
struct TYPE_13__ {scalar_t__ lr_offset; scalar_t__ lr_length; scalar_t__ lr_type; int /*<<< orphan*/  lr_read_cv; void* lr_read_wanted; scalar_t__ lr_write_wanted; } ;
typedef  TYPE_2__ zfs_locked_range_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  avl_tree_t ;
typedef  int /*<<< orphan*/  avl_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  AVL_AFTER ; 
 int /*<<< orphan*/  AVL_BEFORE ; 
 TYPE_2__* AVL_NEXT (int /*<<< orphan*/ *,TYPE_2__*) ; 
 void* B_TRUE ; 
 int /*<<< orphan*/  CV_DEFAULT ; 
 scalar_t__ RL_WRITER ; 
 TYPE_2__* avl_find (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* avl_nearest (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cv_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_rangelock_add_reader (int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
zfs_rangelock_enter_reader(zfs_rangelock_t *rl, zfs_locked_range_t *new)
{
	avl_tree_t *tree = &rl->rl_tree;
	zfs_locked_range_t *prev, *next;
	avl_index_t where;
	uint64_t off = new->lr_offset;
	uint64_t len = new->lr_length;

	/*
	 * Look for any writer locks in the range.
	 */
retry:
	prev = avl_find(tree, new, &where);
	if (prev == NULL)
		prev = avl_nearest(tree, where, AVL_BEFORE);

	/*
	 * Check the previous range for a writer lock overlap.
	 */
	if (prev && (off < prev->lr_offset + prev->lr_length)) {
		if ((prev->lr_type == RL_WRITER) || (prev->lr_write_wanted)) {
			if (!prev->lr_read_wanted) {
				cv_init(&prev->lr_read_cv,
				    NULL, CV_DEFAULT, NULL);
				prev->lr_read_wanted = B_TRUE;
			}
			cv_wait(&prev->lr_read_cv, &rl->rl_lock);
			goto retry;
		}
		if (off + len < prev->lr_offset + prev->lr_length)
			goto got_lock;
	}

	/*
	 * Search through the following ranges to see if there's
	 * write lock any overlap.
	 */
	if (prev != NULL)
		next = AVL_NEXT(tree, prev);
	else
		next = avl_nearest(tree, where, AVL_AFTER);
	for (; next != NULL; next = AVL_NEXT(tree, next)) {
		if (off + len <= next->lr_offset)
			goto got_lock;
		if ((next->lr_type == RL_WRITER) || (next->lr_write_wanted)) {
			if (!next->lr_read_wanted) {
				cv_init(&next->lr_read_cv,
				    NULL, CV_DEFAULT, NULL);
				next->lr_read_wanted = B_TRUE;
			}
			cv_wait(&next->lr_read_cv, &rl->rl_lock);
			goto retry;
		}
		if (off + len <= next->lr_offset + next->lr_length)
			goto got_lock;
	}

got_lock:
	/*
	 * Add the read lock, which may involve splitting existing
	 * locks and bumping ref counts (r_count).
	 */
	zfs_rangelock_add_reader(tree, new, prev, where);
}