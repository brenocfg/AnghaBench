#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
struct TYPE_20__ {scalar_t__ zp_compress; int /*<<< orphan*/  zp_copies; } ;
struct TYPE_28__ {scalar_t__ blk_birth; } ;
struct TYPE_23__ {int io_flags; int /*<<< orphan*/  io_error; TYPE_1__ io_prop; TYPE_9__* io_bp; TYPE_9__ io_bp_orig; } ;
typedef  TYPE_4__ zio_t ;
struct TYPE_24__ {int /*<<< orphan*/  zgd_bp; int /*<<< orphan*/  zgd_lwb; } ;
typedef  TYPE_5__ zgd_t ;
typedef  size_t uint8_t ;
struct TYPE_25__ {TYPE_5__* dsa_zgd; int /*<<< orphan*/  (* dsa_done ) (TYPE_5__*,int /*<<< orphan*/ ) ;TYPE_8__* dsa_dr; } ;
typedef  TYPE_6__ dmu_sync_arg_t ;
struct TYPE_26__ {int /*<<< orphan*/  db_mtx; int /*<<< orphan*/  db_changed; TYPE_9__* db_blkptr; } ;
typedef  TYPE_7__ dmu_buf_impl_t ;
struct TYPE_21__ {scalar_t__ dr_override_state; int dr_nopwrite; TYPE_9__ dr_overridden_by; int /*<<< orphan*/  dr_copies; } ;
struct TYPE_22__ {TYPE_2__ dl; } ;
struct TYPE_27__ {TYPE_3__ dt; TYPE_7__* dr_dbuf; } ;
typedef  TYPE_8__ dbuf_dirty_record_t ;
typedef  TYPE_9__ blkptr_t ;
typedef  int /*<<< orphan*/  arc_buf_t ;
struct TYPE_19__ {int ci_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int BP_EQUAL (TYPE_9__*,TYPE_9__*) ; 
 size_t BP_GET_CHECKSUM (TYPE_9__*) ; 
 scalar_t__ BP_IS_HOLE (TYPE_9__*) ; 
 int /*<<< orphan*/  BP_ZERO (TYPE_9__*) ; 
 scalar_t__ DR_IN_DMU_SYNC ; 
 scalar_t__ DR_NOT_OVERRIDDEN ; 
 scalar_t__ DR_OVERRIDDEN ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int ZCHECKSUM_FLAG_NOPWRITE ; 
 scalar_t__ ZIO_COMPRESS_OFF ; 
 int ZIO_FLAG_NOPWRITE ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_free (TYPE_6__*,int) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zil_lwb_add_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_10__* zio_checksum_table ; 

__attribute__((used)) static void
dmu_sync_done(zio_t *zio, arc_buf_t *buf, void *varg)
{
	dmu_sync_arg_t *dsa = varg;
	dbuf_dirty_record_t *dr = dsa->dsa_dr;
	dmu_buf_impl_t *db = dr->dr_dbuf;
	zgd_t *zgd = dsa->dsa_zgd;

	/*
	 * Record the vdev(s) backing this blkptr so they can be flushed after
	 * the writes for the lwb have completed.
	 */
	if (zio->io_error == 0) {
		zil_lwb_add_block(zgd->zgd_lwb, zgd->zgd_bp);
	}

	mutex_enter(&db->db_mtx);
	ASSERT(dr->dt.dl.dr_override_state == DR_IN_DMU_SYNC);
	if (zio->io_error == 0) {
		dr->dt.dl.dr_nopwrite = !!(zio->io_flags & ZIO_FLAG_NOPWRITE);
		if (dr->dt.dl.dr_nopwrite) {
			blkptr_t *bp = zio->io_bp;
			blkptr_t *bp_orig = &zio->io_bp_orig;
			uint8_t chksum = BP_GET_CHECKSUM(bp_orig);

			ASSERT(BP_EQUAL(bp, bp_orig));
			VERIFY(BP_EQUAL(bp, db->db_blkptr));
			ASSERT(zio->io_prop.zp_compress != ZIO_COMPRESS_OFF);
			VERIFY(zio_checksum_table[chksum].ci_flags &
			    ZCHECKSUM_FLAG_NOPWRITE);
		}
		dr->dt.dl.dr_overridden_by = *zio->io_bp;
		dr->dt.dl.dr_override_state = DR_OVERRIDDEN;
		dr->dt.dl.dr_copies = zio->io_prop.zp_copies;

		/*
		 * Old style holes are filled with all zeros, whereas
		 * new-style holes maintain their lsize, type, level,
		 * and birth time (see zio_write_compress). While we
		 * need to reset the BP_SET_LSIZE() call that happened
		 * in dmu_sync_ready for old style holes, we do *not*
		 * want to wipe out the information contained in new
		 * style holes. Thus, only zero out the block pointer if
		 * it's an old style hole.
		 */
		if (BP_IS_HOLE(&dr->dt.dl.dr_overridden_by) &&
		    dr->dt.dl.dr_overridden_by.blk_birth == 0)
			BP_ZERO(&dr->dt.dl.dr_overridden_by);
	} else {
		dr->dt.dl.dr_override_state = DR_NOT_OVERRIDDEN;
	}
	cv_broadcast(&db->db_changed);
	mutex_exit(&db->db_mtx);

	dsa->dsa_done(dsa->dsa_zgd, zio->io_error);

	kmem_free(dsa, sizeof (*dsa));
}