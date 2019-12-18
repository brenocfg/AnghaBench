#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ zb_blkid; scalar_t__ zb_level; scalar_t__ zb_object; scalar_t__ zb_objset; } ;
struct TYPE_6__ {int io_error; int io_flags; int /*<<< orphan*/  io_abd; TYPE_3__ io_bookmark; TYPE_2__* io_private; int /*<<< orphan*/ * io_bp; TYPE_4__* io_spa; } ;
typedef  TYPE_1__ zio_t ;
struct TYPE_7__ {int zcb_haderrors; int /*<<< orphan*/ * zcb_errors; } ;
typedef  TYPE_2__ zdb_cb_t ;
typedef  TYPE_3__ zbookmark_phys_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;
struct TYPE_9__ {int /*<<< orphan*/  spa_scrub_lock; int /*<<< orphan*/  spa_scrub_io_cv; int /*<<< orphan*/  spa_load_verify_bytes; } ;
typedef  TYPE_4__ spa_t ;
typedef  int /*<<< orphan*/  blkptr_t ;
typedef  int /*<<< orphan*/  blkbuf ;

/* Variables and functions */
 scalar_t__ BP_GET_PSIZE (int /*<<< orphan*/ *) ; 
 int BP_SPRINTF_LEN ; 
 int ZIO_FLAG_SPECULATIVE ; 
 int /*<<< orphan*/  abd_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int* dump_opt ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snprintf_blkptr (char*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
zdb_blkptr_done(zio_t *zio)
{
	spa_t *spa = zio->io_spa;
	blkptr_t *bp = zio->io_bp;
	int ioerr = zio->io_error;
	zdb_cb_t *zcb = zio->io_private;
	zbookmark_phys_t *zb = &zio->io_bookmark;

	abd_free(zio->io_abd);

	mutex_enter(&spa->spa_scrub_lock);
	spa->spa_load_verify_bytes -= BP_GET_PSIZE(bp);
	cv_broadcast(&spa->spa_scrub_io_cv);

	if (ioerr && !(zio->io_flags & ZIO_FLAG_SPECULATIVE)) {
		char blkbuf[BP_SPRINTF_LEN];

		zcb->zcb_haderrors = 1;
		zcb->zcb_errors[ioerr]++;

		if (dump_opt['b'] >= 2)
			snprintf_blkptr(blkbuf, sizeof (blkbuf), bp);
		else
			blkbuf[0] = '\0';

		(void) printf("zdb_blkptr_cb: "
		    "Got error %d reading "
		    "<%llu, %llu, %lld, %llx> %s -- skipping\n",
		    ioerr,
		    (u_longlong_t)zb->zb_objset,
		    (u_longlong_t)zb->zb_object,
		    (u_longlong_t)zb->zb_level,
		    (u_longlong_t)zb->zb_blkid,
		    blkbuf);
	}
	mutex_exit(&spa->spa_scrub_lock);
}