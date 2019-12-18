#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  shm_mq_handle ;
typedef  int /*<<< orphan*/  shm_mq ;
typedef  int /*<<< orphan*/  dsm_segment ;
struct TYPE_5__ {int /*<<< orphan*/  ack_dsm_handle; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  BgwMessageType ;
typedef  TYPE_1__ BgwMessage ;

/* Variables and functions */
 int /*<<< orphan*/  BGW_ACK_QUEUE_SIZE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  MyProc ; 
 TYPE_1__* bgw_message_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsm_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dsm_find_mapping (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsm_segment_address (int /*<<< orphan*/ *) ; 
 int enqueue_message_wait_for_ack (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  mq ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 
 int /*<<< orphan*/ * shm_mq_attach (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * shm_mq_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shm_mq_set_receiver (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

extern bool
ts_bgw_message_send_and_wait(BgwMessageType message_type, Oid db_oid)
{
	shm_mq *ack_queue;
	dsm_segment *seg;
	shm_mq_handle *ack_queue_handle;
	BgwMessage *message;
	bool ack_received = false;

	message = bgw_message_create(message_type, db_oid);

	seg = dsm_find_mapping(message->ack_dsm_handle);
	if (seg == NULL)
		ereport(ERROR,
				(errmsg("TimescaleDB background worker dynamic shared memory segment not mapped")));
	ack_queue = shm_mq_create(dsm_segment_address(seg), BGW_ACK_QUEUE_SIZE);
	shm_mq_set_receiver(ack_queue, MyProc);
	ack_queue_handle = shm_mq_attach(ack_queue, seg, NULL);
	if (ack_queue_handle != NULL)
		ack_received = enqueue_message_wait_for_ack(mq, message, ack_queue_handle);
	dsm_detach(seg); /* Queue detach happens in dsm detach callback */
	pfree(message);
	return ack_received;
}