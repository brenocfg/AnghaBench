#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ io_type; scalar_t__ io_spa; scalar_t__ io_bp; TYPE_1__* io_logical; } ;
typedef  TYPE_2__ zio_t ;
struct TYPE_13__ {scalar_t__ zi_cmd; } ;
struct TYPE_12__ {scalar_t__ zi_spa; TYPE_4__ zi_record; } ;
typedef  TYPE_3__ inject_handler_t ;
struct TYPE_10__ {int /*<<< orphan*/  io_bookmark; } ;

/* Variables and functions */
 int /*<<< orphan*/  BP_GET_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  DMU_OT_NONE ; 
 int /*<<< orphan*/  RW_READER ; 
 scalar_t__ ZINJECT_DATA_FAULT ; 
 scalar_t__ ZIO_TYPE_READ ; 
 int /*<<< orphan*/  inject_handlers ; 
 int /*<<< orphan*/  inject_lock ; 
 TYPE_3__* list_head (int /*<<< orphan*/ *) ; 
 TYPE_3__* list_next (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zio_match_dva (TYPE_2__*) ; 
 scalar_t__ zio_match_handler (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,int) ; 

int
zio_handle_fault_injection(zio_t *zio, int error)
{
	int ret = 0;
	inject_handler_t *handler;

	/*
	 * Ignore I/O not associated with any logical data.
	 */
	if (zio->io_logical == NULL)
		return (0);

	/*
	 * Currently, we only support fault injection on reads.
	 */
	if (zio->io_type != ZIO_TYPE_READ)
		return (0);

	rw_enter(&inject_lock, RW_READER);

	for (handler = list_head(&inject_handlers); handler != NULL;
	    handler = list_next(&inject_handlers, handler)) {
		if (zio->io_spa != handler->zi_spa ||
		    handler->zi_record.zi_cmd != ZINJECT_DATA_FAULT)
			continue;

		/* If this handler matches, return the specified error */
		if (zio_match_handler(&zio->io_logical->io_bookmark,
		    zio->io_bp ? BP_GET_TYPE(zio->io_bp) : DMU_OT_NONE,
		    zio_match_dva(zio), &handler->zi_record, error)) {
			ret = error;
			break;
		}
	}

	rw_exit(&inject_lock);

	return (ret);
}