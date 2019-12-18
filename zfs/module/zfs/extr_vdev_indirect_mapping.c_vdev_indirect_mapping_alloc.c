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
struct TYPE_10__ {void* vimp_counts_object; } ;
typedef  TYPE_1__ vdev_indirect_mapping_phys_t ;
typedef  int uint64_t ;
struct TYPE_11__ {int /*<<< orphan*/  os_spa; } ;
typedef  TYPE_2__ objset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_12__ {TYPE_1__* db_data; } ;
typedef  TYPE_3__ dmu_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMU_OTN_UINT32_METADATA ; 
 int /*<<< orphan*/  DMU_OTN_UINT64_METADATA ; 
 int /*<<< orphan*/  DMU_OT_NONE ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  SPA_FEATURE_OBSOLETE_COUNTS ; 
 int /*<<< orphan*/  SPA_OLD_MAXBLOCKSIZE ; 
 int VDEV_INDIRECT_MAPPING_SIZE_V0 ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_bonus_hold (TYPE_2__*,int,int /*<<< orphan*/ ,TYPE_3__**) ; 
 int /*<<< orphan*/  dmu_buf_rele (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_buf_will_dirty (TYPE_3__*,int /*<<< orphan*/ *) ; 
 void* dmu_object_alloc (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_tx_is_syncing (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_feature_incr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ spa_feature_is_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

uint64_t
vdev_indirect_mapping_alloc(objset_t *os, dmu_tx_t *tx)
{
	uint64_t object;
	ASSERT(dmu_tx_is_syncing(tx));
	uint64_t bonus_size = VDEV_INDIRECT_MAPPING_SIZE_V0;

	if (spa_feature_is_enabled(os->os_spa, SPA_FEATURE_OBSOLETE_COUNTS)) {
		bonus_size = sizeof (vdev_indirect_mapping_phys_t);
	}

	object = dmu_object_alloc(os,
	    DMU_OTN_UINT64_METADATA, SPA_OLD_MAXBLOCKSIZE,
	    DMU_OTN_UINT64_METADATA, bonus_size,
	    tx);

	if (spa_feature_is_enabled(os->os_spa, SPA_FEATURE_OBSOLETE_COUNTS)) {
		dmu_buf_t *dbuf;
		vdev_indirect_mapping_phys_t *vimp;

		VERIFY0(dmu_bonus_hold(os, object, FTAG, &dbuf));
		dmu_buf_will_dirty(dbuf, tx);
		vimp = dbuf->db_data;
		vimp->vimp_counts_object = dmu_object_alloc(os,
		    DMU_OTN_UINT32_METADATA, SPA_OLD_MAXBLOCKSIZE,
		    DMU_OT_NONE, 0, tx);
		spa_feature_incr(os->os_spa, SPA_FEATURE_OBSOLETE_COUNTS, tx);
		dmu_buf_rele(dbuf, FTAG);
	}

	return (object);
}