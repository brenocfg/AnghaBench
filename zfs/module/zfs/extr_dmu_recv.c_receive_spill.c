#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct receive_writer_arg {scalar_t__ max_object; scalar_t__ byteswap; int /*<<< orphan*/  os; scalar_t__ raw; scalar_t__ spill; } ;
struct drr_spill {scalar_t__ drr_compressiontype; scalar_t__ drr_compressed_size; scalar_t__ drr_object; int /*<<< orphan*/  drr_type; int /*<<< orphan*/  drr_length; int /*<<< orphan*/  drr_flags; } ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  size_t dmu_object_byteswap_t ;
struct TYPE_15__ {int /*<<< orphan*/  db_size; int /*<<< orphan*/  db_object; } ;
typedef  TYPE_1__ dmu_buf_t ;
typedef  int /*<<< orphan*/  dmu_buf_impl_t ;
struct TYPE_16__ {int /*<<< orphan*/  b_data; } ;
typedef  TYPE_2__ arc_buf_t ;
struct TYPE_17__ {int /*<<< orphan*/  (* ob_func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 size_t DMU_OT_BYTESWAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMU_OT_IS_VALID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMU_READ_NO_DECRYPT ; 
 scalar_t__ DRR_SPILL_IS_UNMODIFIED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRR_SPILL_PAYLOAD_SIZE (struct drr_spill*) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  FTAG ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPA_MINBLOCKSIZE ; 
 int /*<<< orphan*/  TXG_WAIT ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 scalar_t__ ZIO_COMPRESS_FUNCTIONS ; 
 scalar_t__ ZIO_COMPRESS_OFF ; 
 scalar_t__ arc_get_compression (TYPE_2__*) ; 
 int /*<<< orphan*/  arc_is_encrypted (TYPE_2__*) ; 
 int /*<<< orphan*/  dbuf_assign_arcbuf (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ dbuf_spill_set_blksz (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_bonus_hold (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  dmu_buf_rele (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_buf_will_fill (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ dmu_object_info (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_objset_spa (int /*<<< orphan*/ ) ; 
 TYPE_7__* dmu_ot_byteswap ; 
 int /*<<< orphan*/  dmu_return_arcbuf (TYPE_2__*) ; 
 int dmu_spill_hold_by_bonus (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  dmu_tx_abort (int /*<<< orphan*/ *) ; 
 int dmu_tx_assign (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_tx_commit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dmu_tx_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_tx_hold_spill (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_maxblocksize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
receive_spill(struct receive_writer_arg *rwa, struct drr_spill *drrs,
    arc_buf_t *abuf)
{
	dmu_tx_t *tx;
	dmu_buf_t *db, *db_spill;
	int err;

	if (drrs->drr_length < SPA_MINBLOCKSIZE ||
	    drrs->drr_length > spa_maxblocksize(dmu_objset_spa(rwa->os)))
		return (SET_ERROR(EINVAL));

	/*
	 * This is an unmodified spill block which was added to the stream
	 * to resolve an issue with incorrectly removing spill blocks.  It
	 * should be ignored by current versions of the code which support
	 * the DRR_FLAG_SPILL_BLOCK flag.
	 */
	if (rwa->spill && DRR_SPILL_IS_UNMODIFIED(drrs->drr_flags)) {
		dmu_return_arcbuf(abuf);
		return (0);
	}

	if (rwa->raw) {
		if (!DMU_OT_IS_VALID(drrs->drr_type) ||
		    drrs->drr_compressiontype >= ZIO_COMPRESS_FUNCTIONS ||
		    drrs->drr_compressed_size == 0)
			return (SET_ERROR(EINVAL));
	}

	if (dmu_object_info(rwa->os, drrs->drr_object, NULL) != 0)
		return (SET_ERROR(EINVAL));

	if (drrs->drr_object > rwa->max_object)
		rwa->max_object = drrs->drr_object;

	VERIFY0(dmu_bonus_hold(rwa->os, drrs->drr_object, FTAG, &db));
	if ((err = dmu_spill_hold_by_bonus(db, DMU_READ_NO_DECRYPT, FTAG,
	    &db_spill)) != 0) {
		dmu_buf_rele(db, FTAG);
		return (err);
	}

	tx = dmu_tx_create(rwa->os);

	dmu_tx_hold_spill(tx, db->db_object);

	err = dmu_tx_assign(tx, TXG_WAIT);
	if (err != 0) {
		dmu_buf_rele(db, FTAG);
		dmu_buf_rele(db_spill, FTAG);
		dmu_tx_abort(tx);
		return (err);
	}

	/*
	 * Spill blocks may both grow and shrink.  When a change in size
	 * occurs any existing dbuf must be updated to match the logical
	 * size of the provided arc_buf_t.
	 */
	if (db_spill->db_size != drrs->drr_length) {
		dmu_buf_will_fill(db_spill, tx);
		VERIFY(0 == dbuf_spill_set_blksz(db_spill,
		    drrs->drr_length, tx));
	}

	if (rwa->byteswap && !arc_is_encrypted(abuf) &&
	    arc_get_compression(abuf) == ZIO_COMPRESS_OFF) {
		dmu_object_byteswap_t byteswap =
		    DMU_OT_BYTESWAP(drrs->drr_type);
		dmu_ot_byteswap[byteswap].ob_func(abuf->b_data,
		    DRR_SPILL_PAYLOAD_SIZE(drrs));
	}

	dbuf_assign_arcbuf((dmu_buf_impl_t *)db_spill, abuf, tx);

	dmu_buf_rele(db, FTAG);
	dmu_buf_rele(db_spill, FTAG);

	dmu_tx_commit(tx);
	return (0);
}