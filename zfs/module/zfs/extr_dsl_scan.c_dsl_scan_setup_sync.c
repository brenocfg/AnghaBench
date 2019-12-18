#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_8__ ;
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_21__ ;
typedef  struct TYPE_25__   TYPE_1__ ;
typedef  struct TYPE_24__   TYPE_19__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zfs_all_blkstats_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;
struct TYPE_27__ {int /*<<< orphan*/  spa_scrub_started; TYPE_8__* spa_root_vdev; } ;
typedef  TYPE_2__ spa_t ;
typedef  scalar_t__ pool_scan_func_t ;
struct TYPE_26__ {scalar_t__ scn_min_txg; scalar_t__ scn_max_txg; int /*<<< orphan*/  scn_queue_obj; scalar_t__ scn_ddt_class_max; int /*<<< orphan*/  scn_to_examine; scalar_t__ scn_errors; int /*<<< orphan*/  scn_start_time; int /*<<< orphan*/  scn_state; scalar_t__ scn_func; } ;
struct TYPE_28__ {TYPE_21__ scn_phys; int /*<<< orphan*/  scn_phys_cached; int /*<<< orphan*/  scn_checkpointing; scalar_t__ scn_last_checkpoint; scalar_t__ scn_done_txg; scalar_t__ scn_restart_txg; scalar_t__ scn_issued_before_pass; TYPE_4__* scn_dp; } ;
typedef  TYPE_3__ dsl_scan_t ;
struct TYPE_29__ {int /*<<< orphan*/  dp_meta_objset; TYPE_7__* dp_blkstats; TYPE_2__* dp_spa; } ;
typedef  TYPE_4__ dsl_pool_t ;
struct TYPE_30__ {scalar_t__ tx_txg; } ;
typedef  TYPE_5__ dmu_tx_t ;
typedef  scalar_t__ dmu_object_type_t ;
struct TYPE_25__ {int /*<<< orphan*/  vs_alloc; } ;
struct TYPE_32__ {TYPE_1__ vdev_stat; } ;
struct TYPE_31__ {TYPE_21__ zab_type; int /*<<< orphan*/  zab_lock; } ;
struct TYPE_24__ {TYPE_3__* dp_scan; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 scalar_t__ DDT_CLASSES ; 
 scalar_t__ DDT_CLASS_DITTO ; 
 int /*<<< orphan*/  DMU_OT_NONE ; 
 scalar_t__ DMU_OT_SCAN_QUEUE ; 
 scalar_t__ DMU_OT_ZAP_OTHER ; 
 scalar_t__ DSL_SCAN_IS_SCRUB_RESILVER (TYPE_3__*) ; 
 int /*<<< orphan*/  DSS_SCANNING ; 
 int /*<<< orphan*/  ESC_ZFS_RESILVER_START ; 
 int /*<<< orphan*/  ESC_ZFS_SCRUB_START ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  MUTEX_DEFAULT ; 
 scalar_t__ POOL_SCAN_FUNCS ; 
 scalar_t__ POOL_SCAN_NONE ; 
 scalar_t__ SPA_VERSION_DSL_SCRUB ; 
 int /*<<< orphan*/  SYNC_MANDATORY ; 
 scalar_t__ TXG_INITIAL ; 
 int /*<<< orphan*/  bcopy (TYPE_21__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bzero (TYPE_21__*,int) ; 
 TYPE_19__* dmu_tx_pool (TYPE_5__*) ; 
 int /*<<< orphan*/  dsl_scan_is_running (TYPE_3__*) ; 
 int /*<<< orphan*/  dsl_scan_sync_state (TYPE_3__*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gethrestime_sec () ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_event_notify (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_history_log_internal (TYPE_2__*,char*,TYPE_5__*,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_scan_stat_init (TYPE_2__*) ; 
 scalar_t__ spa_version (TYPE_2__*) ; 
 int /*<<< orphan*/  vdev_config_dirty (TYPE_8__*) ; 
 scalar_t__ vdev_resilver_needed (TYPE_8__*,scalar_t__*,scalar_t__*) ; 
 TYPE_7__* vmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zap_create (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 scalar_t__ zfs_scrub_ddt_class_max ; 

__attribute__((used)) static void
dsl_scan_setup_sync(void *arg, dmu_tx_t *tx)
{
	dsl_scan_t *scn = dmu_tx_pool(tx)->dp_scan;
	pool_scan_func_t *funcp = arg;
	dmu_object_type_t ot = 0;
	dsl_pool_t *dp = scn->scn_dp;
	spa_t *spa = dp->dp_spa;

	ASSERT(!dsl_scan_is_running(scn));
	ASSERT(*funcp > POOL_SCAN_NONE && *funcp < POOL_SCAN_FUNCS);
	bzero(&scn->scn_phys, sizeof (scn->scn_phys));
	scn->scn_phys.scn_func = *funcp;
	scn->scn_phys.scn_state = DSS_SCANNING;
	scn->scn_phys.scn_min_txg = 0;
	scn->scn_phys.scn_max_txg = tx->tx_txg;
	scn->scn_phys.scn_ddt_class_max = DDT_CLASSES - 1; /* the entire DDT */
	scn->scn_phys.scn_start_time = gethrestime_sec();
	scn->scn_phys.scn_errors = 0;
	scn->scn_phys.scn_to_examine = spa->spa_root_vdev->vdev_stat.vs_alloc;
	scn->scn_issued_before_pass = 0;
	scn->scn_restart_txg = 0;
	scn->scn_done_txg = 0;
	scn->scn_last_checkpoint = 0;
	scn->scn_checkpointing = B_FALSE;
	spa_scan_stat_init(spa);

	if (DSL_SCAN_IS_SCRUB_RESILVER(scn)) {
		scn->scn_phys.scn_ddt_class_max = zfs_scrub_ddt_class_max;

		/* rewrite all disk labels */
		vdev_config_dirty(spa->spa_root_vdev);

		if (vdev_resilver_needed(spa->spa_root_vdev,
		    &scn->scn_phys.scn_min_txg, &scn->scn_phys.scn_max_txg)) {
			spa_event_notify(spa, NULL, NULL,
			    ESC_ZFS_RESILVER_START);
		} else {
			spa_event_notify(spa, NULL, NULL, ESC_ZFS_SCRUB_START);
		}

		spa->spa_scrub_started = B_TRUE;
		/*
		 * If this is an incremental scrub, limit the DDT scrub phase
		 * to just the auto-ditto class (for correctness); the rest
		 * of the scrub should go faster using top-down pruning.
		 */
		if (scn->scn_phys.scn_min_txg > TXG_INITIAL)
			scn->scn_phys.scn_ddt_class_max = DDT_CLASS_DITTO;

	}

	/* back to the generic stuff */

	if (dp->dp_blkstats == NULL) {
		dp->dp_blkstats =
		    vmem_alloc(sizeof (zfs_all_blkstats_t), KM_SLEEP);
		mutex_init(&dp->dp_blkstats->zab_lock, NULL,
		    MUTEX_DEFAULT, NULL);
	}
	bzero(&dp->dp_blkstats->zab_type, sizeof (dp->dp_blkstats->zab_type));

	if (spa_version(spa) < SPA_VERSION_DSL_SCRUB)
		ot = DMU_OT_ZAP_OTHER;

	scn->scn_phys.scn_queue_obj = zap_create(dp->dp_meta_objset,
	    ot ? ot : DMU_OT_SCAN_QUEUE, DMU_OT_NONE, 0, tx);

	bcopy(&scn->scn_phys, &scn->scn_phys_cached, sizeof (scn->scn_phys));

	dsl_scan_sync_state(scn, tx, SYNC_MANDATORY);

	spa_history_log_internal(spa, "scan setup", tx,
	    "func=%u mintxg=%llu maxtxg=%llu",
	    *funcp, (u_longlong_t)scn->scn_phys.scn_min_txg,
	    (u_longlong_t)scn->scn_phys.scn_max_txg);
}