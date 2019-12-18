#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  spa_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_6__ {scalar_t__ zi_cmd; int zi_duration; scalar_t__ zi_timer; } ;
struct TYPE_7__ {TYPE_1__ zi_record; int /*<<< orphan*/ * zi_spa; } ;
typedef  TYPE_2__ inject_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 scalar_t__ ZINJECT_IGNORED_WRITES ; 
 int /*<<< orphan*/  ddi_get_lbolt64 () ; 
 scalar_t__ ddi_time_after64 (scalar_t__,int /*<<< orphan*/ ) ; 
 int hz ; 
 int /*<<< orphan*/  inject_handlers ; 
 int /*<<< orphan*/  inject_lock ; 
 TYPE_2__* list_head (int /*<<< orphan*/ *) ; 
 TYPE_2__* list_next (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 
 scalar_t__ spa_syncing_txg (int /*<<< orphan*/ *) ; 
 scalar_t__ zio_injection_enabled ; 

void
spa_handle_ignored_writes(spa_t *spa)
{
	inject_handler_t *handler;

	if (zio_injection_enabled == 0)
		return;

	rw_enter(&inject_lock, RW_READER);

	for (handler = list_head(&inject_handlers); handler != NULL;
	    handler = list_next(&inject_handlers, handler)) {

		if (spa != handler->zi_spa ||
		    handler->zi_record.zi_cmd != ZINJECT_IGNORED_WRITES)
			continue;

		if (handler->zi_record.zi_duration > 0) {
			VERIFY(handler->zi_record.zi_timer == 0 ||
			    ddi_time_after64(
			    (int64_t)handler->zi_record.zi_timer +
			    handler->zi_record.zi_duration * hz,
			    ddi_get_lbolt64()));
		} else {
			/* duration is negative so the subtraction here adds */
			VERIFY(handler->zi_record.zi_timer == 0 ||
			    handler->zi_record.zi_timer -
			    handler->zi_record.zi_duration >=
			    spa_syncing_txg(spa));
		}
	}

	rw_exit(&inject_lock);
}