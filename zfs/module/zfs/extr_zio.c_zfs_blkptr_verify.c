#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
struct TYPE_24__ {size_t vdev_asize; int /*<<< orphan*/ * vdev_ops; } ;
typedef  TYPE_2__ vdev_t ;
typedef  size_t uint64_t ;
struct TYPE_25__ {TYPE_1__* spa_root_vdev; int /*<<< orphan*/  spa_trust_config; } ;
typedef  TYPE_3__ spa_t ;
typedef  int /*<<< orphan*/  longlong_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_26__ {int /*<<< orphan*/ * blk_dva; } ;
typedef  TYPE_4__ blkptr_t ;
struct TYPE_23__ {size_t vdev_children; TYPE_2__** vdev_child; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ BPE_GET_ETYPE (TYPE_4__ const*) ; 
 scalar_t__ BP_GET_CHECKSUM (TYPE_4__ const*) ; 
 scalar_t__ BP_GET_COMPRESS (TYPE_4__ const*) ; 
 scalar_t__ BP_GET_LSIZE (TYPE_4__ const*) ; 
 int BP_GET_NDVAS (TYPE_4__ const*) ; 
 scalar_t__ BP_GET_PSIZE (TYPE_4__ const*) ; 
 scalar_t__ BP_GET_TYPE (TYPE_4__ const*) ; 
 scalar_t__ BP_IS_EMBEDDED (TYPE_4__ const*) ; 
 scalar_t__ BP_IS_GANG (TYPE_4__ const*) ; 
 int /*<<< orphan*/  DMU_OT_IS_VALID (scalar_t__) ; 
 size_t DVA_GET_ASIZE (int /*<<< orphan*/ *) ; 
 size_t DVA_GET_OFFSET (int /*<<< orphan*/ *) ; 
 size_t DVA_GET_VDEV (int /*<<< orphan*/ *) ; 
 scalar_t__ NUM_BP_EMBEDDED_TYPES ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  RW_WRITER ; 
 int /*<<< orphan*/  SCL_VDEV ; 
 int /*<<< orphan*/  SPA_GANGBLOCKSIZE ; 
 scalar_t__ SPA_MAXBLOCKSIZE ; 
 scalar_t__ ZIO_CHECKSUM_FUNCTIONS ; 
 scalar_t__ ZIO_CHECKSUM_ON ; 
 scalar_t__ ZIO_COMPRESS_FUNCTIONS ; 
 scalar_t__ ZIO_COMPRESS_ON ; 
 int /*<<< orphan*/  spa_config_enter (TYPE_3__*,int /*<<< orphan*/ ,TYPE_4__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_exit (TYPE_3__*,int /*<<< orphan*/ ,TYPE_4__ const*) ; 
 int /*<<< orphan*/  spa_config_held (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_hole_ops ; 
 int /*<<< orphan*/  vdev_missing_ops ; 
 size_t vdev_psize_to_asize (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_panic_recover (char*,TYPE_4__ const*,int,...) ; 

__attribute__((used)) static void
zfs_blkptr_verify(spa_t *spa, const blkptr_t *bp, boolean_t config_held)
{
	if (!DMU_OT_IS_VALID(BP_GET_TYPE(bp))) {
		zfs_panic_recover("blkptr at %p has invalid TYPE %llu",
		    bp, (longlong_t)BP_GET_TYPE(bp));
	}
	if (BP_GET_CHECKSUM(bp) >= ZIO_CHECKSUM_FUNCTIONS ||
	    BP_GET_CHECKSUM(bp) <= ZIO_CHECKSUM_ON) {
		zfs_panic_recover("blkptr at %p has invalid CHECKSUM %llu",
		    bp, (longlong_t)BP_GET_CHECKSUM(bp));
	}
	if (BP_GET_COMPRESS(bp) >= ZIO_COMPRESS_FUNCTIONS ||
	    BP_GET_COMPRESS(bp) <= ZIO_COMPRESS_ON) {
		zfs_panic_recover("blkptr at %p has invalid COMPRESS %llu",
		    bp, (longlong_t)BP_GET_COMPRESS(bp));
	}
	if (BP_GET_LSIZE(bp) > SPA_MAXBLOCKSIZE) {
		zfs_panic_recover("blkptr at %p has invalid LSIZE %llu",
		    bp, (longlong_t)BP_GET_LSIZE(bp));
	}
	if (BP_GET_PSIZE(bp) > SPA_MAXBLOCKSIZE) {
		zfs_panic_recover("blkptr at %p has invalid PSIZE %llu",
		    bp, (longlong_t)BP_GET_PSIZE(bp));
	}

	if (BP_IS_EMBEDDED(bp)) {
		if (BPE_GET_ETYPE(bp) >= NUM_BP_EMBEDDED_TYPES) {
			zfs_panic_recover("blkptr at %p has invalid ETYPE %llu",
			    bp, (longlong_t)BPE_GET_ETYPE(bp));
		}
	}

	/*
	 * Do not verify individual DVAs if the config is not trusted. This
	 * will be done once the zio is executed in vdev_mirror_map_alloc.
	 */
	if (!spa->spa_trust_config)
		return;

	if (!config_held)
		spa_config_enter(spa, SCL_VDEV, bp, RW_READER);
	else
		ASSERT(spa_config_held(spa, SCL_VDEV, RW_WRITER));
	/*
	 * Pool-specific checks.
	 *
	 * Note: it would be nice to verify that the blk_birth and
	 * BP_PHYSICAL_BIRTH() are not too large.  However, spa_freeze()
	 * allows the birth time of log blocks (and dmu_sync()-ed blocks
	 * that are in the log) to be arbitrarily large.
	 */
	for (int i = 0; i < BP_GET_NDVAS(bp); i++) {
		uint64_t vdevid = DVA_GET_VDEV(&bp->blk_dva[i]);

		if (vdevid >= spa->spa_root_vdev->vdev_children) {
			zfs_panic_recover("blkptr at %p DVA %u has invalid "
			    "VDEV %llu",
			    bp, i, (longlong_t)vdevid);
			continue;
		}
		vdev_t *vd = spa->spa_root_vdev->vdev_child[vdevid];
		if (vd == NULL) {
			zfs_panic_recover("blkptr at %p DVA %u has invalid "
			    "VDEV %llu",
			    bp, i, (longlong_t)vdevid);
			continue;
		}
		if (vd->vdev_ops == &vdev_hole_ops) {
			zfs_panic_recover("blkptr at %p DVA %u has hole "
			    "VDEV %llu",
			    bp, i, (longlong_t)vdevid);
			continue;
		}
		if (vd->vdev_ops == &vdev_missing_ops) {
			/*
			 * "missing" vdevs are valid during import, but we
			 * don't have their detailed info (e.g. asize), so
			 * we can't perform any more checks on them.
			 */
			continue;
		}
		uint64_t offset = DVA_GET_OFFSET(&bp->blk_dva[i]);
		uint64_t asize = DVA_GET_ASIZE(&bp->blk_dva[i]);
		if (BP_IS_GANG(bp))
			asize = vdev_psize_to_asize(vd, SPA_GANGBLOCKSIZE);
		if (offset + asize > vd->vdev_asize) {
			zfs_panic_recover("blkptr at %p DVA %u has invalid "
			    "OFFSET %llu",
			    bp, i, (longlong_t)offset);
		}
	}
	if (!config_held)
		spa_config_exit(spa, SCL_VDEV, bp);
}