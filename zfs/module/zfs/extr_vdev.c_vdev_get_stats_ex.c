#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {unsigned long long vdev_ms_shift; int /*<<< orphan*/  vdev_stat_lock; int /*<<< orphan*/  vdev_resilver_deferred; TYPE_2__* vdev_ops; TYPE_1__* vdev_mg; struct TYPE_14__* vdev_top; int /*<<< orphan*/ * vdev_aux; scalar_t__ vdev_asize; scalar_t__ vdev_max_asize; int /*<<< orphan*/  vdev_trim_action_time; int /*<<< orphan*/  vdev_trim_state; int /*<<< orphan*/  vdev_trim_bytes_est; int /*<<< orphan*/  vdev_trim_bytes_done; int /*<<< orphan*/  vdev_has_trim; int /*<<< orphan*/  vdev_initialize_action_time; int /*<<< orphan*/  vdev_initialize_state; int /*<<< orphan*/  vdev_initialize_bytes_est; int /*<<< orphan*/  vdev_initialize_bytes_done; int /*<<< orphan*/  vdev_state; int /*<<< orphan*/  vdev_stat; } ;
typedef  TYPE_3__ vdev_t ;
struct TYPE_15__ {int vs_trim_notsup; int /*<<< orphan*/  vs_resilver_deferred; int /*<<< orphan*/  vs_fragmentation; int /*<<< orphan*/  vs_esize; int /*<<< orphan*/  vs_trim_action_time; int /*<<< orphan*/  vs_trim_state; int /*<<< orphan*/  vs_trim_bytes_est; int /*<<< orphan*/  vs_trim_bytes_done; int /*<<< orphan*/  vs_initialize_action_time; int /*<<< orphan*/  vs_initialize_state; int /*<<< orphan*/  vs_initialize_bytes_est; int /*<<< orphan*/  vs_initialize_bytes_done; int /*<<< orphan*/  vs_rsize; int /*<<< orphan*/  vs_state; scalar_t__ vs_timestamp; } ;
typedef  TYPE_4__ vdev_stat_t ;
typedef  int /*<<< orphan*/  vdev_stat_ex_t ;
struct TYPE_13__ {scalar_t__ vdev_op_leaf; } ;
struct TYPE_12__ {int /*<<< orphan*/  mg_fragmentation; } ;

/* Variables and functions */
 int /*<<< orphan*/  P2ALIGN (scalar_t__,unsigned long long) ; 
 scalar_t__ VDEV_LABEL_END_SIZE ; 
 scalar_t__ VDEV_LABEL_START_SIZE ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,TYPE_4__*,int) ; 
 scalar_t__ gethrtime () ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vdev_get_min_asize (TYPE_3__*) ; 
 int /*<<< orphan*/  vdev_get_stats_ex_impl (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 scalar_t__ vdev_is_concrete (TYPE_3__*) ; 

void
vdev_get_stats_ex(vdev_t *vd, vdev_stat_t *vs, vdev_stat_ex_t *vsx)
{
	vdev_t *tvd = vd->vdev_top;
	mutex_enter(&vd->vdev_stat_lock);
	if (vs) {
		bcopy(&vd->vdev_stat, vs, sizeof (*vs));
		vs->vs_timestamp = gethrtime() - vs->vs_timestamp;
		vs->vs_state = vd->vdev_state;
		vs->vs_rsize = vdev_get_min_asize(vd);
		if (vd->vdev_ops->vdev_op_leaf) {
			vs->vs_rsize += VDEV_LABEL_START_SIZE +
			    VDEV_LABEL_END_SIZE;
			/*
			 * Report initializing progress. Since we don't
			 * have the initializing locks held, this is only
			 * an estimate (although a fairly accurate one).
			 */
			vs->vs_initialize_bytes_done =
			    vd->vdev_initialize_bytes_done;
			vs->vs_initialize_bytes_est =
			    vd->vdev_initialize_bytes_est;
			vs->vs_initialize_state = vd->vdev_initialize_state;
			vs->vs_initialize_action_time =
			    vd->vdev_initialize_action_time;

			/*
			 * Report manual TRIM progress. Since we don't have
			 * the manual TRIM locks held, this is only an
			 * estimate (although fairly accurate one).
			 */
			vs->vs_trim_notsup = !vd->vdev_has_trim;
			vs->vs_trim_bytes_done = vd->vdev_trim_bytes_done;
			vs->vs_trim_bytes_est = vd->vdev_trim_bytes_est;
			vs->vs_trim_state = vd->vdev_trim_state;
			vs->vs_trim_action_time = vd->vdev_trim_action_time;
		}
		/*
		 * Report expandable space on top-level, non-auxiliary devices
		 * only. The expandable space is reported in terms of metaslab
		 * sized units since that determines how much space the pool
		 * can expand.
		 */
		if (vd->vdev_aux == NULL && tvd != NULL) {
			vs->vs_esize = P2ALIGN(
			    vd->vdev_max_asize - vd->vdev_asize,
			    1ULL << tvd->vdev_ms_shift);
		}
		if (vd->vdev_aux == NULL && vd == vd->vdev_top &&
		    vdev_is_concrete(vd)) {
			vs->vs_fragmentation = (vd->vdev_mg != NULL) ?
			    vd->vdev_mg->mg_fragmentation : 0;
		}
		if (vd->vdev_ops->vdev_op_leaf)
			vs->vs_resilver_deferred = vd->vdev_resilver_deferred;
	}

	vdev_get_stats_ex_impl(vd, vs, vsx);
	mutex_exit(&vd->vdev_stat_lock);
}