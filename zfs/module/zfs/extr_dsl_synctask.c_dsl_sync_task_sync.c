#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_7__ {scalar_t__ dst_error; int dst_space; scalar_t__ (* dst_checkfunc ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;scalar_t__ dst_nowaiter; int /*<<< orphan*/  dst_arg; int /*<<< orphan*/  (* dst_syncfunc ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  dst_space_check; TYPE_2__* dst_pool; } ;
typedef  TYPE_1__ dsl_sync_task_t ;
struct TYPE_8__ {int /*<<< orphan*/  dp_config_rwlock; int /*<<< orphan*/  dp_root_dir; } ;
typedef  TYPE_2__ dsl_pool_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_9__ {scalar_t__ dd_used_bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT0 (scalar_t__) ; 
 int /*<<< orphan*/  ENOSPC ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  RW_WRITER ; 
 scalar_t__ SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZFS_SPACE_CHECK_NONE ; 
 TYPE_6__* dsl_dir_phys (int /*<<< orphan*/ ) ; 
 scalar_t__ dsl_pool_unreserved_space (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  rrw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrw_exit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
dsl_sync_task_sync(dsl_sync_task_t *dst, dmu_tx_t *tx)
{
	dsl_pool_t *dp = dst->dst_pool;

	ASSERT0(dst->dst_error);

	/*
	 * Check for sufficient space.
	 *
	 * When the sync task was created, the caller specified the
	 * type of space checking required.  See the comment in
	 * zfs_space_check_t for details on the semantics of each
	 * type of space checking.
	 *
	 * We just check against what's on-disk; we don't want any
	 * in-flight accounting to get in our way, because open context
	 * may have already used up various in-core limits
	 * (arc_tempreserve, dsl_pool_tempreserve).
	 */
	if (dst->dst_space_check != ZFS_SPACE_CHECK_NONE) {
		uint64_t quota = dsl_pool_unreserved_space(dp,
		    dst->dst_space_check);
		uint64_t used = dsl_dir_phys(dp->dp_root_dir)->dd_used_bytes;

		/* MOS space is triple-dittoed, so we multiply by 3. */
		if (used + dst->dst_space * 3 > quota) {
			dst->dst_error = SET_ERROR(ENOSPC);
			if (dst->dst_nowaiter)
				kmem_free(dst, sizeof (*dst));
			return;
		}
	}

	/*
	 * Check for errors by calling checkfunc.
	 */
	rrw_enter(&dp->dp_config_rwlock, RW_WRITER, FTAG);
	dst->dst_error = dst->dst_checkfunc(dst->dst_arg, tx);
	if (dst->dst_error == 0)
		dst->dst_syncfunc(dst->dst_arg, tx);
	rrw_exit(&dp->dp_config_rwlock, FTAG);
	if (dst->dst_nowaiter)
		kmem_free(dst, sizeof (*dst));
}