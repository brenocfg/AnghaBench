#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct dmu_send_params {scalar_t__ resumeobj; scalar_t__ resumeoff; int /*<<< orphan*/ * redactbook; scalar_t__ rawok; scalar_t__ compressok; scalar_t__ embedok; scalar_t__ large_block_ok; TYPE_2__* dp; int /*<<< orphan*/ * to_ds; } ;
struct TYPE_6__ {scalar_t__ os_encrypted; } ;
typedef  TYPE_1__ objset_t ;
struct TYPE_7__ {int /*<<< orphan*/  dp_spa; } ;
typedef  TYPE_2__ dsl_pool_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;

/* Variables and functions */
 scalar_t__ DMU_BACKUP_FEATURE_COMPRESSED ; 
 scalar_t__ DMU_BACKUP_FEATURE_EMBED_DATA ; 
 scalar_t__ DMU_BACKUP_FEATURE_LARGE_BLOCKS ; 
 scalar_t__ DMU_BACKUP_FEATURE_LARGE_DNODE ; 
 scalar_t__ DMU_BACKUP_FEATURE_LZ4 ; 
 scalar_t__ DMU_BACKUP_FEATURE_RAW ; 
 scalar_t__ DMU_BACKUP_FEATURE_REDACTED ; 
 scalar_t__ DMU_BACKUP_FEATURE_RESUMING ; 
 scalar_t__ DMU_BACKUP_FEATURE_SA_SPILL ; 
 scalar_t__ DMU_OST_ZFS ; 
 int /*<<< orphan*/  EINVAL ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPA_FEATURE_EMBEDDED_DATA ; 
 int /*<<< orphan*/  SPA_FEATURE_LARGE_BLOCKS ; 
 int /*<<< orphan*/  SPA_FEATURE_LARGE_DNODE ; 
 int /*<<< orphan*/  SPA_FEATURE_LZ4_COMPRESS ; 
 int /*<<< orphan*/  ZFS_PROP_VERSION ; 
 scalar_t__ ZPL_VERSION_SA ; 
 scalar_t__ dmu_objset_type (TYPE_1__*) ; 
 scalar_t__ dsl_dataset_feature_is_active (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ spa_feature_is_active (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_get_zplprop (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static int
setup_featureflags(struct dmu_send_params *dspp, objset_t *os,
    uint64_t *featureflags)
{
	dsl_dataset_t *to_ds = dspp->to_ds;
	dsl_pool_t *dp = dspp->dp;
#ifdef _KERNEL
	if (dmu_objset_type(os) == DMU_OST_ZFS) {
		uint64_t version;
		if (zfs_get_zplprop(os, ZFS_PROP_VERSION, &version) != 0)
			return (SET_ERROR(EINVAL));

		if (version >= ZPL_VERSION_SA)
			*featureflags |= DMU_BACKUP_FEATURE_SA_SPILL;
	}
#endif

	/* raw sends imply large_block_ok */
	if ((dspp->rawok || dspp->large_block_ok) &&
	    dsl_dataset_feature_is_active(to_ds, SPA_FEATURE_LARGE_BLOCKS)) {
		*featureflags |= DMU_BACKUP_FEATURE_LARGE_BLOCKS;
	}

	/* encrypted datasets will not have embedded blocks */
	if ((dspp->embedok || dspp->rawok) && !os->os_encrypted &&
	    spa_feature_is_active(dp->dp_spa, SPA_FEATURE_EMBEDDED_DATA)) {
		*featureflags |= DMU_BACKUP_FEATURE_EMBED_DATA;
	}

	/* raw send implies compressok */
	if (dspp->compressok || dspp->rawok)
		*featureflags |= DMU_BACKUP_FEATURE_COMPRESSED;
	if (dspp->rawok && os->os_encrypted)
		*featureflags |= DMU_BACKUP_FEATURE_RAW;

	if ((*featureflags &
	    (DMU_BACKUP_FEATURE_EMBED_DATA | DMU_BACKUP_FEATURE_COMPRESSED |
	    DMU_BACKUP_FEATURE_RAW)) != 0 &&
	    spa_feature_is_active(dp->dp_spa, SPA_FEATURE_LZ4_COMPRESS)) {
		*featureflags |= DMU_BACKUP_FEATURE_LZ4;
	}

	if (dspp->resumeobj != 0 || dspp->resumeoff != 0) {
		*featureflags |= DMU_BACKUP_FEATURE_RESUMING;
	}

	if (dspp->redactbook != NULL) {
		*featureflags |= DMU_BACKUP_FEATURE_REDACTED;
	}

	if (dsl_dataset_feature_is_active(to_ds, SPA_FEATURE_LARGE_DNODE)) {
		*featureflags |= DMU_BACKUP_FEATURE_LARGE_DNODE;
	}
	return (0);
}