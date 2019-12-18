#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  sio_zb; int /*<<< orphan*/  sio_flags; } ;
typedef  TYPE_1__ scan_io_t ;
typedef  int /*<<< orphan*/  list_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_13__ {int /*<<< orphan*/  scn_bytes_pending; int /*<<< orphan*/  scn_dp; } ;
typedef  TYPE_2__ dsl_scan_t ;
struct TYPE_14__ {TYPE_2__* q_scn; } ;
typedef  TYPE_3__ dsl_scan_io_queue_t ;
typedef  int /*<<< orphan*/  boolean_t ;
typedef  int /*<<< orphan*/  blkptr_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 scalar_t__ SIO_GET_ASIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  atomic_add_64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* list_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_remove_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scan_exec_io (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ scan_io_queue_check_suspend (TYPE_2__*) ; 
 int /*<<< orphan*/  scan_io_queues_update_zio_stats (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sio2bp (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sio_free (TYPE_1__*) ; 

__attribute__((used)) static boolean_t
scan_io_queue_issue(dsl_scan_io_queue_t *queue, list_t *io_list)
{
	dsl_scan_t *scn = queue->q_scn;
	scan_io_t *sio;
	int64_t bytes_issued = 0;
	boolean_t suspended = B_FALSE;

	while ((sio = list_head(io_list)) != NULL) {
		blkptr_t bp;

		if (scan_io_queue_check_suspend(scn)) {
			suspended = B_TRUE;
			break;
		}

		sio2bp(sio, &bp);
		bytes_issued += SIO_GET_ASIZE(sio);
		scan_exec_io(scn->scn_dp, &bp, sio->sio_flags,
		    &sio->sio_zb, queue);
		(void) list_remove_head(io_list);
		scan_io_queues_update_zio_stats(queue, &bp);
		sio_free(sio);
	}

	atomic_add_64(&scn->scn_bytes_pending, -bytes_issued);

	return (suspended);
}