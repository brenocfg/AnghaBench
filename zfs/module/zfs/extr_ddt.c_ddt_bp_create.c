#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  enum zio_checksum { ____Placeholder_zio_checksum } zio_checksum ;
struct TYPE_24__ {int /*<<< orphan*/  ddp_phys_birth; } ;
typedef  TYPE_1__ ddt_phys_t ;
struct TYPE_25__ {int /*<<< orphan*/  ddk_cksum; } ;
typedef  TYPE_2__ ddt_key_t ;
struct TYPE_26__ {int /*<<< orphan*/  blk_cksum; } ;
typedef  TYPE_3__ blkptr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BP_SET_BYTEORDER (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BP_SET_CHECKSUM (TYPE_3__*,int) ; 
 int /*<<< orphan*/  BP_SET_COMPRESS (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BP_SET_CRYPT (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BP_SET_DEDUP (TYPE_3__*,int) ; 
 int /*<<< orphan*/  BP_SET_FILL (TYPE_3__*,int) ; 
 int /*<<< orphan*/  BP_SET_LEVEL (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BP_SET_LSIZE (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BP_SET_PSIZE (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BP_SET_TYPE (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BP_ZERO (TYPE_3__*) ; 
 int /*<<< orphan*/  DDK_GET_COMPRESS (TYPE_2__ const*) ; 
 int /*<<< orphan*/  DDK_GET_CRYPT (TYPE_2__ const*) ; 
 int /*<<< orphan*/  DDK_GET_LSIZE (TYPE_2__ const*) ; 
 int /*<<< orphan*/  DDK_GET_PSIZE (TYPE_2__ const*) ; 
 int /*<<< orphan*/  DMU_OT_DEDUP ; 
 int /*<<< orphan*/  ZFS_HOST_BYTEORDER ; 
 int /*<<< orphan*/  ddt_bp_fill (TYPE_1__ const*,TYPE_3__*,int /*<<< orphan*/ ) ; 

void
ddt_bp_create(enum zio_checksum checksum,
    const ddt_key_t *ddk, const ddt_phys_t *ddp, blkptr_t *bp)
{
	BP_ZERO(bp);

	if (ddp != NULL)
		ddt_bp_fill(ddp, bp, ddp->ddp_phys_birth);

	bp->blk_cksum = ddk->ddk_cksum;

	BP_SET_LSIZE(bp, DDK_GET_LSIZE(ddk));
	BP_SET_PSIZE(bp, DDK_GET_PSIZE(ddk));
	BP_SET_COMPRESS(bp, DDK_GET_COMPRESS(ddk));
	BP_SET_CRYPT(bp, DDK_GET_CRYPT(ddk));
	BP_SET_FILL(bp, 1);
	BP_SET_CHECKSUM(bp, checksum);
	BP_SET_TYPE(bp, DMU_OT_DEDUP);
	BP_SET_LEVEL(bp, 0);
	BP_SET_DEDUP(bp, 1);
	BP_SET_BYTEORDER(bp, ZFS_HOST_BYTEORDER);
}