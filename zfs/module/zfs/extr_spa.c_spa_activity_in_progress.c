#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int zpool_wait_activity_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_15__ {int /*<<< orphan*/  sr_state; } ;
struct TYPE_18__ {TYPE_2__* spa_dsl_pool; TYPE_1__ spa_removing_phys; int /*<<< orphan*/  spa_root_vdev; int /*<<< orphan*/  spa_activities_lock; } ;
typedef  TYPE_4__ spa_t ;
struct TYPE_17__ {int /*<<< orphan*/  scn_state; int /*<<< orphan*/  scn_func; } ;
struct TYPE_19__ {TYPE_3__ scn_phys; } ;
typedef  TYPE_5__ dsl_scan_t ;
typedef  int boolean_t ;
struct TYPE_16__ {TYPE_5__* dp_scan; int /*<<< orphan*/  dp_free_bpobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMU_POOL_DIRECTORY_OBJECT ; 
 int /*<<< orphan*/  DMU_POOL_ZPOOL_CHECKPOINT ; 
 int /*<<< orphan*/  DSS_SCANNING ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  POOL_SCAN_SCRUB ; 
 int /*<<< orphan*/  RW_READER ; 
 int SCL_CONFIG ; 
 int SCL_STATE ; 
 int /*<<< orphan*/  SPA_FEATURE_ASYNC_DESTROY ; 
 int /*<<< orphan*/  SPA_FEATURE_POOL_CHECKPOINT ; 
 int /*<<< orphan*/  SPA_VERSION_DEADLISTS ; 
#define  ZPOOL_WAIT_CKPT_DISCARD 134 
#define  ZPOOL_WAIT_FREE 133 
#define  ZPOOL_WAIT_INITIALIZE 132 
#define  ZPOOL_WAIT_REMOVE 131 
#define  ZPOOL_WAIT_REPLACE 130 
#define  ZPOOL_WAIT_RESILVER 129 
#define  ZPOOL_WAIT_SCRUB 128 
 int /*<<< orphan*/  bpobj_is_empty (int /*<<< orphan*/ *) ; 
 int dsl_scan_is_paused_scrub (TYPE_5__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int /*<<< orphan*/  spa_config_enter (TYPE_4__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_exit (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_feature_is_active (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_livelist_delete_check (TYPE_4__*) ; 
 int /*<<< orphan*/  spa_meta_objset (TYPE_4__*) ; 
 int spa_vdev_initializing (TYPE_4__*,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  spa_version (TYPE_4__*) ; 
 int vdev_replace_in_progress (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zap_contains (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
spa_activity_in_progress(spa_t *spa, zpool_wait_activity_t activity,
    boolean_t use_tag, uint64_t tag, boolean_t *in_progress)
{
	int error = 0;

	ASSERT(MUTEX_HELD(&spa->spa_activities_lock));

	switch (activity) {
	case ZPOOL_WAIT_CKPT_DISCARD:
		*in_progress =
		    (spa_feature_is_active(spa, SPA_FEATURE_POOL_CHECKPOINT) &&
		    zap_contains(spa_meta_objset(spa),
		    DMU_POOL_DIRECTORY_OBJECT, DMU_POOL_ZPOOL_CHECKPOINT) ==
		    ENOENT);
		break;
	case ZPOOL_WAIT_FREE:
		*in_progress = ((spa_version(spa) >= SPA_VERSION_DEADLISTS &&
		    !bpobj_is_empty(&spa->spa_dsl_pool->dp_free_bpobj)) ||
		    spa_feature_is_active(spa, SPA_FEATURE_ASYNC_DESTROY) ||
		    spa_livelist_delete_check(spa));
		break;
	case ZPOOL_WAIT_INITIALIZE:
		error = spa_vdev_initializing(spa, use_tag, tag, in_progress);
		break;
	case ZPOOL_WAIT_REPLACE:
		mutex_exit(&spa->spa_activities_lock);
		spa_config_enter(spa, SCL_CONFIG | SCL_STATE, FTAG, RW_READER);
		mutex_enter(&spa->spa_activities_lock);

		*in_progress = vdev_replace_in_progress(spa->spa_root_vdev);
		spa_config_exit(spa, SCL_CONFIG | SCL_STATE, FTAG);
		break;
	case ZPOOL_WAIT_REMOVE:
		*in_progress = (spa->spa_removing_phys.sr_state ==
		    DSS_SCANNING);
		break;
	case ZPOOL_WAIT_RESILVER:
	case ZPOOL_WAIT_SCRUB:
	{
		boolean_t scanning, paused, is_scrub;
		dsl_scan_t *scn =  spa->spa_dsl_pool->dp_scan;

		is_scrub = (scn->scn_phys.scn_func == POOL_SCAN_SCRUB);
		scanning = (scn->scn_phys.scn_state == DSS_SCANNING);
		paused = dsl_scan_is_paused_scrub(scn);
		*in_progress = (scanning && !paused &&
		    is_scrub == (activity == ZPOOL_WAIT_SCRUB));
		break;
	}
	default:
		panic("unrecognized value for activity %d", activity);
	}

	return (error);
}