#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ vs_aux; } ;
struct TYPE_12__ {unsigned long long vdev_faulted; unsigned long long vdev_degraded; int /*<<< orphan*/ * vdev_aux; int /*<<< orphan*/  vdev_islog; void* vdev_delayed_close; scalar_t__ vdev_label_aux; void* vdev_tmpoffline; TYPE_2__ vdev_stat; struct TYPE_12__* vdev_top; TYPE_1__* vdev_ops; } ;
typedef  TYPE_3__ vdev_t ;
typedef  scalar_t__ vdev_aux_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
struct TYPE_10__ {int /*<<< orphan*/  vdev_op_leaf; } ;

/* Variables and functions */
 void* B_FALSE ; 
 void* B_TRUE ; 
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  ENOTSUP ; 
 int /*<<< orphan*/  SCL_NONE ; 
 scalar_t__ VDEV_AUX_EXTERNAL ; 
 scalar_t__ VDEV_AUX_EXTERNAL_PERSIST ; 
 int /*<<< orphan*/  VDEV_STATE_DEGRADED ; 
 int /*<<< orphan*/  VDEV_STATE_FAULTED ; 
 TYPE_3__* spa_lookup_by_guid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  spa_vdev_state_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int spa_vdev_state_exit (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ vdev_dtl_required (TYPE_3__*) ; 
 scalar_t__ vdev_readable (TYPE_3__*) ; 
 int /*<<< orphan*/  vdev_reopen (TYPE_3__*) ; 
 int /*<<< orphan*/  vdev_set_state (TYPE_3__*,void*,int /*<<< orphan*/ ,scalar_t__) ; 

int
vdev_fault(spa_t *spa, uint64_t guid, vdev_aux_t aux)
{
	vdev_t *vd, *tvd;

	spa_vdev_state_enter(spa, SCL_NONE);

	if ((vd = spa_lookup_by_guid(spa, guid, B_TRUE)) == NULL)
		return (spa_vdev_state_exit(spa, NULL, ENODEV));

	if (!vd->vdev_ops->vdev_op_leaf)
		return (spa_vdev_state_exit(spa, NULL, ENOTSUP));

	tvd = vd->vdev_top;

	/*
	 * If user did a 'zpool offline -f' then make the fault persist across
	 * reboots.
	 */
	if (aux == VDEV_AUX_EXTERNAL_PERSIST) {
		/*
		 * There are two kinds of forced faults: temporary and
		 * persistent.  Temporary faults go away at pool import, while
		 * persistent faults stay set.  Both types of faults can be
		 * cleared with a zpool clear.
		 *
		 * We tell if a vdev is persistently faulted by looking at the
		 * ZPOOL_CONFIG_AUX_STATE nvpair.  If it's set to "external" at
		 * import then it's a persistent fault.  Otherwise, it's
		 * temporary.  We get ZPOOL_CONFIG_AUX_STATE set to "external"
		 * by setting vd.vdev_stat.vs_aux to VDEV_AUX_EXTERNAL.  This
		 * tells vdev_config_generate() (which gets run later) to set
		 * ZPOOL_CONFIG_AUX_STATE to "external" in the nvlist.
		 */
		vd->vdev_stat.vs_aux = VDEV_AUX_EXTERNAL;
		vd->vdev_tmpoffline = B_FALSE;
		aux = VDEV_AUX_EXTERNAL;
	} else {
		vd->vdev_tmpoffline = B_TRUE;
	}

	/*
	 * We don't directly use the aux state here, but if we do a
	 * vdev_reopen(), we need this value to be present to remember why we
	 * were faulted.
	 */
	vd->vdev_label_aux = aux;

	/*
	 * Faulted state takes precedence over degraded.
	 */
	vd->vdev_delayed_close = B_FALSE;
	vd->vdev_faulted = 1ULL;
	vd->vdev_degraded = 0ULL;
	vdev_set_state(vd, B_FALSE, VDEV_STATE_FAULTED, aux);

	/*
	 * If this device has the only valid copy of the data, then
	 * back off and simply mark the vdev as degraded instead.
	 */
	if (!tvd->vdev_islog && vd->vdev_aux == NULL && vdev_dtl_required(vd)) {
		vd->vdev_degraded = 1ULL;
		vd->vdev_faulted = 0ULL;

		/*
		 * If we reopen the device and it's not dead, only then do we
		 * mark it degraded.
		 */
		vdev_reopen(tvd);

		if (vdev_readable(vd))
			vdev_set_state(vd, B_FALSE, VDEV_STATE_DEGRADED, aux);
	}

	return (spa_vdev_state_exit(spa, vd, 0));
}