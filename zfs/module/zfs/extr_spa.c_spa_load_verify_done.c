#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int io_error; int /*<<< orphan*/  io_abd; TYPE_2__* io_spa; TYPE_3__* io_private; int /*<<< orphan*/ * io_bp; } ;
typedef  TYPE_1__ zio_t ;
struct TYPE_6__ {int /*<<< orphan*/  spa_scrub_lock; int /*<<< orphan*/  spa_scrub_io_cv; int /*<<< orphan*/  spa_load_verify_bytes; } ;
typedef  TYPE_2__ spa_t ;
struct TYPE_7__ {int /*<<< orphan*/  sle_data_count; int /*<<< orphan*/  sle_meta_count; } ;
typedef  TYPE_3__ spa_load_error_t ;
typedef  scalar_t__ dmu_object_type_t ;
typedef  int /*<<< orphan*/  blkptr_t ;

/* Variables and functions */
 scalar_t__ BP_GET_LEVEL (int /*<<< orphan*/ *) ; 
 scalar_t__ BP_GET_PSIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ BP_GET_TYPE (int /*<<< orphan*/ *) ; 
 scalar_t__ DMU_OT_INTENT_LOG ; 
 scalar_t__ DMU_OT_IS_METADATA (scalar_t__) ; 
 int /*<<< orphan*/  abd_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc_64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
spa_load_verify_done(zio_t *zio)
{
	blkptr_t *bp = zio->io_bp;
	spa_load_error_t *sle = zio->io_private;
	dmu_object_type_t type = BP_GET_TYPE(bp);
	int error = zio->io_error;
	spa_t *spa = zio->io_spa;

	abd_free(zio->io_abd);
	if (error) {
		if ((BP_GET_LEVEL(bp) != 0 || DMU_OT_IS_METADATA(type)) &&
		    type != DMU_OT_INTENT_LOG)
			atomic_inc_64(&sle->sle_meta_count);
		else
			atomic_inc_64(&sle->sle_data_count);
	}

	mutex_enter(&spa->spa_scrub_lock);
	spa->spa_load_verify_bytes -= BP_GET_PSIZE(bp);
	cv_broadcast(&spa->spa_scrub_io_cv);
	mutex_exit(&spa->spa_scrub_lock);
}