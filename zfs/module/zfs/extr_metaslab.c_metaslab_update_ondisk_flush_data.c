#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  vdev_top_zap; int /*<<< orphan*/ * vdev_spa; } ;
typedef  TYPE_2__ vdev_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  objset_t ;
struct TYPE_10__ {int /*<<< orphan*/  msp_unflushed_txg; } ;
typedef  TYPE_3__ metaslab_unflushed_phys_t ;
struct TYPE_11__ {int ms_id; TYPE_1__* ms_group; } ;
typedef  TYPE_4__ metaslab_t ;
typedef  int /*<<< orphan*/  entry ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_8__ {TYPE_2__* mg_vd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMU_OTN_UINT64_METADATA ; 
 int /*<<< orphan*/  DMU_OT_NONE ; 
 int ENOENT ; 
 int /*<<< orphan*/  SPA_FEATURE_LOG_SPACEMAP ; 
 int /*<<< orphan*/  SPA_OLD_MAXBLOCKSIZE ; 
 int /*<<< orphan*/  VDEV_TOP_ZAP_MS_UNFLUSHED_PHYS_TXGS ; 
 int /*<<< orphan*/  VERIFY0 (int) ; 
 int dmu_object_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_write (int /*<<< orphan*/ *,int,int,int,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  metaslab_unflushed_txg (TYPE_4__*) ; 
 int /*<<< orphan*/  spa_feature_is_active (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * spa_meta_objset (int /*<<< orphan*/ *) ; 
 int zap_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int*,int /*<<< orphan*/ *) ; 
 int zap_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int*) ; 

__attribute__((used)) static void
metaslab_update_ondisk_flush_data(metaslab_t *ms, dmu_tx_t *tx)
{
	vdev_t *vd = ms->ms_group->mg_vd;
	spa_t *spa = vd->vdev_spa;
	objset_t *mos = spa_meta_objset(spa);

	ASSERT(spa_feature_is_active(spa, SPA_FEATURE_LOG_SPACEMAP));

	metaslab_unflushed_phys_t entry = {
		.msp_unflushed_txg = metaslab_unflushed_txg(ms),
	};
	uint64_t entry_size = sizeof (entry);
	uint64_t entry_offset = ms->ms_id * entry_size;

	uint64_t object = 0;
	int err = zap_lookup(mos, vd->vdev_top_zap,
	    VDEV_TOP_ZAP_MS_UNFLUSHED_PHYS_TXGS, sizeof (uint64_t), 1,
	    &object);
	if (err == ENOENT) {
		object = dmu_object_alloc(mos, DMU_OTN_UINT64_METADATA,
		    SPA_OLD_MAXBLOCKSIZE, DMU_OT_NONE, 0, tx);
		VERIFY0(zap_add(mos, vd->vdev_top_zap,
		    VDEV_TOP_ZAP_MS_UNFLUSHED_PHYS_TXGS, sizeof (uint64_t), 1,
		    &object, tx));
	} else {
		VERIFY0(err);
	}

	dmu_write(spa_meta_objset(spa), object, entry_offset, entry_size,
	    &entry, tx);
}