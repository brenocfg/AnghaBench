#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  ms_load_cv; scalar_t__ ms_loading; int /*<<< orphan*/  ms_lock; TYPE_1__* ms_group; scalar_t__ ms_loaded; scalar_t__ ms_flushing; int /*<<< orphan*/  ms_condensing; } ;
typedef  TYPE_2__ metaslab_t ;
struct TYPE_11__ {int /*<<< orphan*/  mc_spa; } ;
struct TYPE_9__ {TYPE_3__* mg_class; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 int MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  metaslab_flush_wait (TYPE_2__*) ; 
 int metaslab_load_impl (TYPE_2__*) ; 
 int /*<<< orphan*/  metaslab_load_wait (TYPE_2__*) ; 
 int /*<<< orphan*/  metaslab_potentially_evict (TYPE_3__*) ; 
 TYPE_3__* spa_normal_class (int /*<<< orphan*/ ) ; 

int
metaslab_load(metaslab_t *msp)
{
	ASSERT(MUTEX_HELD(&msp->ms_lock));

	/*
	 * There may be another thread loading the same metaslab, if that's
	 * the case just wait until the other thread is done and return.
	 */
	metaslab_load_wait(msp);
	if (msp->ms_loaded)
		return (0);
	VERIFY(!msp->ms_loading);
	ASSERT(!msp->ms_condensing);

	/*
	 * We set the loading flag BEFORE potentially dropping the lock to
	 * wait for an ongoing flush (see ms_flushing below). This way other
	 * threads know that there is already a thread that is loading this
	 * metaslab.
	 */
	msp->ms_loading = B_TRUE;

	/*
	 * Wait for any in-progress flushing to finish as we drop the ms_lock
	 * both here (during space_map_load()) and in metaslab_flush() (when
	 * we flush our changes to the ms_sm).
	 */
	if (msp->ms_flushing)
		metaslab_flush_wait(msp);

	/*
	 * In the possibility that we were waiting for the metaslab to be
	 * flushed (where we temporarily dropped the ms_lock), ensure that
	 * no one else loaded the metaslab somehow.
	 */
	ASSERT(!msp->ms_loaded);

	/*
	 * If we're loading a metaslab in the normal class, consider evicting
	 * another one to keep our memory usage under the limit defined by the
	 * zfs_metaslab_mem_limit tunable.
	 */
	if (spa_normal_class(msp->ms_group->mg_class->mc_spa) ==
	    msp->ms_group->mg_class) {
		metaslab_potentially_evict(msp->ms_group->mg_class);
	}

	int error = metaslab_load_impl(msp);

	ASSERT(MUTEX_HELD(&msp->ms_lock));
	msp->ms_loading = B_FALSE;
	cv_broadcast(&msp->ms_load_cv);

	return (error);
}