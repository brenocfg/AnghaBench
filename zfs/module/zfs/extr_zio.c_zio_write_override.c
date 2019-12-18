#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int zp_copies; scalar_t__ zp_nopwrite; int /*<<< orphan*/  zp_dedup; } ;
struct TYPE_5__ {scalar_t__ io_type; scalar_t__ io_child_type; scalar_t__ io_stage; scalar_t__ io_txg; int /*<<< orphan*/ * io_bp_override; TYPE_1__ io_prop; int /*<<< orphan*/  io_spa; } ;
typedef  TYPE_2__ zio_t ;
typedef  scalar_t__ boolean_t ;
typedef  int /*<<< orphan*/  blkptr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  B_FALSE ; 
 scalar_t__ ZIO_CHILD_LOGICAL ; 
 scalar_t__ ZIO_STAGE_OPEN ; 
 scalar_t__ ZIO_TYPE_WRITE ; 
 scalar_t__ spa_syncing_txg (int /*<<< orphan*/ ) ; 

void
zio_write_override(zio_t *zio, blkptr_t *bp, int copies, boolean_t nopwrite)
{
	ASSERT(zio->io_type == ZIO_TYPE_WRITE);
	ASSERT(zio->io_child_type == ZIO_CHILD_LOGICAL);
	ASSERT(zio->io_stage == ZIO_STAGE_OPEN);
	ASSERT(zio->io_txg == spa_syncing_txg(zio->io_spa));

	/*
	 * We must reset the io_prop to match the values that existed
	 * when the bp was first written by dmu_sync() keeping in mind
	 * that nopwrite and dedup are mutually exclusive.
	 */
	zio->io_prop.zp_dedup = nopwrite ? B_FALSE : zio->io_prop.zp_dedup;
	zio->io_prop.zp_nopwrite = nopwrite;
	zio->io_prop.zp_copies = copies;
	zio->io_bp_override = bp;
}