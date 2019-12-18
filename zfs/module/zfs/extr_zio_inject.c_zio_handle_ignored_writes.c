#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ io_spa; scalar_t__ io_txg; int /*<<< orphan*/  io_pipeline; } ;
typedef  TYPE_2__ zio_t ;
struct TYPE_8__ {scalar_t__ zi_cmd; scalar_t__ zi_timer; scalar_t__ zi_duration; } ;
struct TYPE_10__ {scalar_t__ zi_spa; TYPE_1__ zi_record; } ;
typedef  TYPE_3__ inject_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  RW_READER ; 
 scalar_t__ ZINJECT_IGNORED_WRITES ; 
 int /*<<< orphan*/  ZIO_VDEV_IO_STAGES ; 
 scalar_t__ ddi_get_lbolt64 () ; 
 int /*<<< orphan*/  inject_handlers ; 
 int /*<<< orphan*/  inject_lock ; 
 TYPE_3__* list_head (int /*<<< orphan*/ *) ; 
 TYPE_3__* list_next (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 
 int spa_get_random (int) ; 

void
zio_handle_ignored_writes(zio_t *zio)
{
	inject_handler_t *handler;

	rw_enter(&inject_lock, RW_READER);

	for (handler = list_head(&inject_handlers); handler != NULL;
	    handler = list_next(&inject_handlers, handler)) {

		/* Ignore errors not destined for this pool */
		if (zio->io_spa != handler->zi_spa ||
		    handler->zi_record.zi_cmd != ZINJECT_IGNORED_WRITES)
			continue;

		/*
		 * Positive duration implies # of seconds, negative
		 * a number of txgs
		 */
		if (handler->zi_record.zi_timer == 0) {
			if (handler->zi_record.zi_duration > 0)
				handler->zi_record.zi_timer = ddi_get_lbolt64();
			else
				handler->zi_record.zi_timer = zio->io_txg;
		}

		/* Have a "problem" writing 60% of the time */
		if (spa_get_random(100) < 60)
			zio->io_pipeline &= ~ZIO_VDEV_IO_STAGES;
		break;
	}

	rw_exit(&inject_lock);
}