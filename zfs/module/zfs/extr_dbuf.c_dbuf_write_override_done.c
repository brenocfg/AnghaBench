#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/ * io_abd; int /*<<< orphan*/  io_txg; int /*<<< orphan*/  io_spa; int /*<<< orphan*/  io_bp; TYPE_5__* io_private; } ;
typedef  TYPE_3__ zio_t ;
struct TYPE_13__ {int /*<<< orphan*/  db_mtx; } ;
typedef  TYPE_4__ dmu_buf_impl_t ;
struct TYPE_10__ {int /*<<< orphan*/  dr_data; int /*<<< orphan*/  dr_overridden_by; } ;
struct TYPE_11__ {TYPE_1__ dl; } ;
struct TYPE_14__ {TYPE_2__ dt; TYPE_4__* dr_dbuf; } ;
typedef  TYPE_5__ dbuf_dirty_record_t ;
typedef  int /*<<< orphan*/  blkptr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BP_EQUAL (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BP_IS_HOLE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  abd_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arc_release (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  dbuf_write_done (TYPE_3__*,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  dsl_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_get_dsl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dbuf_write_override_done(zio_t *zio)
{
	dbuf_dirty_record_t *dr = zio->io_private;
	dmu_buf_impl_t *db = dr->dr_dbuf;
	blkptr_t *obp = &dr->dt.dl.dr_overridden_by;

	mutex_enter(&db->db_mtx);
	if (!BP_EQUAL(zio->io_bp, obp)) {
		if (!BP_IS_HOLE(obp))
			dsl_free(spa_get_dsl(zio->io_spa), zio->io_txg, obp);
		arc_release(dr->dt.dl.dr_data, db);
	}
	mutex_exit(&db->db_mtx);

	dbuf_write_done(zio, NULL, db);

	if (zio->io_abd != NULL)
		abd_put(zio->io_abd);
}