#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  zl_spa; int /*<<< orphan*/  zl_os; TYPE_1__* zl_header; } ;
typedef  TYPE_2__ zilog_t ;
typedef  int /*<<< orphan*/  zbookmark_phys_t ;
struct TYPE_13__ {int lr_offset; int /*<<< orphan*/  lr_foid; int /*<<< orphan*/  lr_length; int /*<<< orphan*/  lr_blkptr; } ;
typedef  TYPE_3__ lr_write_t ;
typedef  enum zio_flag { ____Placeholder_zio_flag } zio_flag ;
typedef  int /*<<< orphan*/  blkptr_t ;
typedef  int /*<<< orphan*/  arc_flags_t ;
struct TYPE_14__ {int /*<<< orphan*/  b_data; } ;
typedef  TYPE_4__ arc_buf_t ;
struct TYPE_11__ {scalar_t__ zh_claim_txg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARC_FLAG_WAIT ; 
 int BP_GET_LSIZE (int /*<<< orphan*/  const*) ; 
 scalar_t__ BP_IS_HOLE (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  MAX (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_BOOKMARK (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ZB_ZIL_LEVEL ; 
 int ZIO_FLAG_CANFAIL ; 
 int ZIO_FLAG_RAW ; 
 int ZIO_FLAG_SCRUB ; 
 int ZIO_FLAG_SPECULATIVE ; 
 int /*<<< orphan*/  ZIO_PRIORITY_SYNC_READ ; 
 int /*<<< orphan*/  arc_buf_destroy (TYPE_4__*,TYPE_4__**) ; 
 int /*<<< orphan*/  arc_buf_size (TYPE_4__*) ; 
 int /*<<< orphan*/  arc_getbuf_func ; 
 int arc_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,TYPE_4__**,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_objset_id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zil_read_log_data(zilog_t *zilog, const lr_write_t *lr, void *wbuf)
{
	enum zio_flag zio_flags = ZIO_FLAG_CANFAIL;
	const blkptr_t *bp = &lr->lr_blkptr;
	arc_flags_t aflags = ARC_FLAG_WAIT;
	arc_buf_t *abuf = NULL;
	zbookmark_phys_t zb;
	int error;

	if (BP_IS_HOLE(bp)) {
		if (wbuf != NULL)
			bzero(wbuf, MAX(BP_GET_LSIZE(bp), lr->lr_length));
		return (0);
	}

	if (zilog->zl_header->zh_claim_txg == 0)
		zio_flags |= ZIO_FLAG_SPECULATIVE | ZIO_FLAG_SCRUB;

	/*
	 * If we are not using the resulting data, we are just checking that
	 * it hasn't been corrupted so we don't need to waste CPU time
	 * decompressing and decrypting it.
	 */
	if (wbuf == NULL)
		zio_flags |= ZIO_FLAG_RAW;

	SET_BOOKMARK(&zb, dmu_objset_id(zilog->zl_os), lr->lr_foid,
	    ZB_ZIL_LEVEL, lr->lr_offset / BP_GET_LSIZE(bp));

	error = arc_read(NULL, zilog->zl_spa, bp, arc_getbuf_func, &abuf,
	    ZIO_PRIORITY_SYNC_READ, zio_flags, &aflags, &zb);

	if (error == 0) {
		if (wbuf != NULL)
			bcopy(abuf->b_data, wbuf, arc_buf_size(abuf));
		arc_buf_destroy(abuf, &abuf);
	}

	return (error);
}