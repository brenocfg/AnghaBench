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
struct TYPE_11__ {int io_flags; scalar_t__ io_size; scalar_t__ io_orig_size; int /*<<< orphan*/ * io_orig_abd; int /*<<< orphan*/  io_bookmark; int /*<<< orphan*/ * io_bp; int /*<<< orphan*/ * io_abd; scalar_t__ io_bp_override; int /*<<< orphan*/ * io_spa; } ;
typedef  TYPE_1__ zio_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  ddt_t ;
struct TYPE_12__ {scalar_t__ ddp_phys_birth; } ;
typedef  TYPE_2__ ddt_phys_t ;
struct TYPE_13__ {TYPE_2__* dde_phys; TYPE_1__** dde_lead_zio; } ;
typedef  TYPE_3__ ddt_entry_t ;
typedef  int boolean_t ;
typedef  int /*<<< orphan*/  blkptr_t ;
typedef  int /*<<< orphan*/  arc_flags_t ;
struct TYPE_14__ {int /*<<< orphan*/  b_data; } ;
typedef  TYPE_4__ arc_buf_t ;
typedef  int /*<<< orphan*/  abd_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARC_FLAG_WAIT ; 
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ BP_GET_LSIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ BP_GET_PSIZE (int /*<<< orphan*/ *) ; 
 int B_FALSE ; 
 int B_TRUE ; 
 int DDT_PHYS_SINGLE ; 
 int DDT_PHYS_TRIPLE ; 
 int /*<<< orphan*/  ENOENT ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int ZIO_FLAG_CANFAIL ; 
 int ZIO_FLAG_RAW ; 
 int ZIO_FLAG_SPECULATIVE ; 
 int /*<<< orphan*/  ZIO_PRIORITY_SYNC_READ ; 
 int /*<<< orphan*/ * abd_alloc_for_io (scalar_t__,int) ; 
 scalar_t__ abd_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ abd_cmp_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  abd_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arc_buf_destroy (TYPE_4__*,TYPE_4__**) ; 
 int /*<<< orphan*/  arc_getbuf_func ; 
 int arc_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__**,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ddt_bp_fill (TYPE_2__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ddt_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ddt_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zio_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int zio_wait (int /*<<< orphan*/ ) ; 

__attribute__((used)) static boolean_t
zio_ddt_collision(zio_t *zio, ddt_t *ddt, ddt_entry_t *dde)
{
	spa_t *spa = zio->io_spa;
	boolean_t do_raw = !!(zio->io_flags & ZIO_FLAG_RAW);

	ASSERT(!(zio->io_bp_override && do_raw));

	/*
	 * Note: we compare the original data, not the transformed data,
	 * because when zio->io_bp is an override bp, we will not have
	 * pushed the I/O transforms.  That's an important optimization
	 * because otherwise we'd compress/encrypt all dmu_sync() data twice.
	 * However, we should never get a raw, override zio so in these
	 * cases we can compare the io_abd directly. This is useful because
	 * it allows us to do dedup verification even if we don't have access
	 * to the original data (for instance, if the encryption keys aren't
	 * loaded).
	 */

	for (int p = DDT_PHYS_SINGLE; p <= DDT_PHYS_TRIPLE; p++) {
		zio_t *lio = dde->dde_lead_zio[p];

		if (lio != NULL && do_raw) {
			return (lio->io_size != zio->io_size ||
			    abd_cmp(zio->io_abd, lio->io_abd) != 0);
		} else if (lio != NULL) {
			return (lio->io_orig_size != zio->io_orig_size ||
			    abd_cmp(zio->io_orig_abd, lio->io_orig_abd) != 0);
		}
	}

	for (int p = DDT_PHYS_SINGLE; p <= DDT_PHYS_TRIPLE; p++) {
		ddt_phys_t *ddp = &dde->dde_phys[p];

		if (ddp->ddp_phys_birth != 0 && do_raw) {
			blkptr_t blk = *zio->io_bp;
			uint64_t psize;
			abd_t *tmpabd;
			int error;

			ddt_bp_fill(ddp, &blk, ddp->ddp_phys_birth);
			psize = BP_GET_PSIZE(&blk);

			if (psize != zio->io_size)
				return (B_TRUE);

			ddt_exit(ddt);

			tmpabd = abd_alloc_for_io(psize, B_TRUE);

			error = zio_wait(zio_read(NULL, spa, &blk, tmpabd,
			    psize, NULL, NULL, ZIO_PRIORITY_SYNC_READ,
			    ZIO_FLAG_CANFAIL | ZIO_FLAG_SPECULATIVE |
			    ZIO_FLAG_RAW, &zio->io_bookmark));

			if (error == 0) {
				if (abd_cmp(tmpabd, zio->io_abd) != 0)
					error = SET_ERROR(ENOENT);
			}

			abd_free(tmpabd);
			ddt_enter(ddt);
			return (error != 0);
		} else if (ddp->ddp_phys_birth != 0) {
			arc_buf_t *abuf = NULL;
			arc_flags_t aflags = ARC_FLAG_WAIT;
			blkptr_t blk = *zio->io_bp;
			int error;

			ddt_bp_fill(ddp, &blk, ddp->ddp_phys_birth);

			if (BP_GET_LSIZE(&blk) != zio->io_orig_size)
				return (B_TRUE);

			ddt_exit(ddt);

			error = arc_read(NULL, spa, &blk,
			    arc_getbuf_func, &abuf, ZIO_PRIORITY_SYNC_READ,
			    ZIO_FLAG_CANFAIL | ZIO_FLAG_SPECULATIVE,
			    &aflags, &zio->io_bookmark);

			if (error == 0) {
				if (abd_cmp_buf(zio->io_orig_abd, abuf->b_data,
				    zio->io_orig_size) != 0)
					error = SET_ERROR(ENOENT);
				arc_buf_destroy(abuf, &abuf);
			}

			ddt_enter(ddt);
			return (error != 0);
		}
	}

	return (B_FALSE);
}