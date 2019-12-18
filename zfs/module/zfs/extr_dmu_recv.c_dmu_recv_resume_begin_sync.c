#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  recvname ;
typedef  int /*<<< orphan*/  dsl_pool_t ;
struct TYPE_9__ {int /*<<< orphan*/  ds_bp_rwlock; } ;
typedef  TYPE_2__ dsl_dataset_t ;
typedef  int /*<<< orphan*/  ds_hold_flags_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_10__ {TYPE_1__* drba_cookie; } ;
typedef  TYPE_3__ dmu_recv_begin_arg_t ;
struct TYPE_8__ {char* drc_tofs; int drc_featureflags; TYPE_2__* drc_ds; void* drc_raw; void* drc_newfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  BP_IS_HOLE (int /*<<< orphan*/ ) ; 
 void* B_TRUE ; 
 int DMU_BACKUP_FEATURE_RAW ; 
 int /*<<< orphan*/  DS_HOLD_FLAG_DECRYPT ; 
 int DS_IS_INCONSISTENT (TYPE_2__*) ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  VERIFY0 (scalar_t__) ; 
 int /*<<< orphan*/  ZFS_MAX_DATASET_NAME_LEN ; 
 int /*<<< orphan*/  dmu_recv_tag ; 
 int /*<<< orphan*/ * dmu_tx_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dataset_get_blkptr (TYPE_2__*) ; 
 scalar_t__ dsl_dataset_own_force (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__**) ; 
 char* recv_clone_name ; 
 int /*<<< orphan*/  rrw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrw_exit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char*) ; 
 int /*<<< orphan*/  spa_history_log_internal_ds (TYPE_2__*,char*,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
dmu_recv_resume_begin_sync(void *arg, dmu_tx_t *tx)
{
	dmu_recv_begin_arg_t *drba = arg;
	dsl_pool_t *dp = dmu_tx_pool(tx);
	const char *tofs = drba->drba_cookie->drc_tofs;
	uint64_t featureflags = drba->drba_cookie->drc_featureflags;
	dsl_dataset_t *ds;
	ds_hold_flags_t dsflags = 0;
	/* 6 extra bytes for /%recv */
	char recvname[ZFS_MAX_DATASET_NAME_LEN + 6];

	(void) snprintf(recvname, sizeof (recvname), "%s/%s", tofs,
	    recv_clone_name);

	if (featureflags & DMU_BACKUP_FEATURE_RAW) {
		drba->drba_cookie->drc_raw = B_TRUE;
	} else {
		dsflags |= DS_HOLD_FLAG_DECRYPT;
	}

	if (dsl_dataset_own_force(dp, recvname, dsflags, dmu_recv_tag, &ds)
	    != 0) {
		/* %recv does not exist; continue in tofs */
		VERIFY0(dsl_dataset_own_force(dp, tofs, dsflags, dmu_recv_tag,
		    &ds));
		drba->drba_cookie->drc_newfs = B_TRUE;
	}

	ASSERT(DS_IS_INCONSISTENT(ds));
	rrw_enter(&ds->ds_bp_rwlock, RW_READER, FTAG);
	ASSERT(!BP_IS_HOLE(dsl_dataset_get_blkptr(ds)) ||
	    drba->drba_cookie->drc_raw);
	rrw_exit(&ds->ds_bp_rwlock, FTAG);

	drba->drba_cookie->drc_ds = ds;

	spa_history_log_internal_ds(ds, "resume receive", tx, " ");
}