#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  scan_io_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_8__ {int /*<<< orphan*/  scn_bytes_pending; } ;
typedef  TYPE_2__ dsl_scan_t ;
struct TYPE_9__ {int /*<<< orphan*/  q_zio_cv; int /*<<< orphan*/  q_sios_by_addr; int /*<<< orphan*/  q_exts_by_addr; int /*<<< orphan*/  q_sio_memused; TYPE_1__* q_vd; TYPE_2__* q_scn; } ;
typedef  TYPE_3__ dsl_scan_io_queue_t ;
struct TYPE_7__ {int /*<<< orphan*/  vdev_scan_io_queue_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSERT0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 scalar_t__ SIO_GET_ASIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ SIO_GET_MUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SIO_GET_OFFSET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_add_64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avl_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * avl_destroy_nodes (int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_free (TYPE_3__*,int) ; 
 int /*<<< orphan*/  range_tree_contains (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  range_tree_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  range_tree_vacate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  sio_free (int /*<<< orphan*/ *) ; 

void
dsl_scan_io_queue_destroy(dsl_scan_io_queue_t *queue)
{
	dsl_scan_t *scn = queue->q_scn;
	scan_io_t *sio;
	void *cookie = NULL;
	int64_t bytes_dequeued = 0;

	ASSERT(MUTEX_HELD(&queue->q_vd->vdev_scan_io_queue_lock));

	while ((sio = avl_destroy_nodes(&queue->q_sios_by_addr, &cookie)) !=
	    NULL) {
		ASSERT(range_tree_contains(queue->q_exts_by_addr,
		    SIO_GET_OFFSET(sio), SIO_GET_ASIZE(sio)));
		bytes_dequeued += SIO_GET_ASIZE(sio);
		queue->q_sio_memused -= SIO_GET_MUSED(sio);
		sio_free(sio);
	}

	ASSERT0(queue->q_sio_memused);
	atomic_add_64(&scn->scn_bytes_pending, -bytes_dequeued);
	range_tree_vacate(queue->q_exts_by_addr, NULL, queue);
	range_tree_destroy(queue->q_exts_by_addr);
	avl_destroy(&queue->q_sios_by_addr);
	cv_destroy(&queue->q_zio_cv);

	kmem_free(queue, sizeof (*queue));
}