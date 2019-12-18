#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  vcsa_txg; int /*<<< orphan*/  vcsa_dest_dva; int /*<<< orphan*/ * vcsa_spa; } ;
typedef  TYPE_4__ vdev_copy_segment_arg_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
struct TYPE_18__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_17__ {TYPE_3__ member_0; } ;
struct TYPE_16__ {TYPE_2__ member_0; } ;
struct TYPE_20__ {int /*<<< orphan*/ * blk_dva; TYPE_1__ member_0; } ;
typedef  TYPE_5__ blkptr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BP_SET_BIRTH (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BP_SET_BYTEORDER (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BP_SET_CHECKSUM (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BP_SET_COMPRESS (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BP_SET_DEDUP (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BP_SET_LEVEL (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BP_SET_LSIZE (TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  BP_SET_PSIZE (TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  BP_SET_TYPE (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMU_OT_NONE ; 
 scalar_t__ DVA_GET_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DVA_GET_VDEV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DVA_SET_ASIZE (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  DVA_SET_OFFSET (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  DVA_SET_VDEV (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TXG_INITIAL ; 
 int /*<<< orphan*/  ZFS_HOST_BYTEORDER ; 
 int /*<<< orphan*/  ZIO_CHECKSUM_OFF ; 
 int /*<<< orphan*/  ZIO_COMPRESS_OFF ; 
 int /*<<< orphan*/  zio_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_5__*) ; 

__attribute__((used)) static void
unalloc_seg(void *arg, uint64_t start, uint64_t size)
{
	vdev_copy_segment_arg_t *vcsa = arg;
	spa_t *spa = vcsa->vcsa_spa;
	blkptr_t bp = { { { {0} } } };

	BP_SET_BIRTH(&bp, TXG_INITIAL, TXG_INITIAL);
	BP_SET_LSIZE(&bp, size);
	BP_SET_PSIZE(&bp, size);
	BP_SET_COMPRESS(&bp, ZIO_COMPRESS_OFF);
	BP_SET_CHECKSUM(&bp, ZIO_CHECKSUM_OFF);
	BP_SET_TYPE(&bp, DMU_OT_NONE);
	BP_SET_LEVEL(&bp, 0);
	BP_SET_DEDUP(&bp, 0);
	BP_SET_BYTEORDER(&bp, ZFS_HOST_BYTEORDER);

	DVA_SET_VDEV(&bp.blk_dva[0], DVA_GET_VDEV(vcsa->vcsa_dest_dva));
	DVA_SET_OFFSET(&bp.blk_dva[0],
	    DVA_GET_OFFSET(vcsa->vcsa_dest_dva) + start);
	DVA_SET_ASIZE(&bp.blk_dva[0], size);

	zio_free(spa, vcsa->vcsa_txg, &bp);
}