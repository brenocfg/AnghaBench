#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  shm_mq_result ;
typedef  int /*<<< orphan*/  shm_mq_handle ;
typedef  int /*<<< orphan*/  PGPROC ;
typedef  int /*<<< orphan*/  MessageQueue ;

/* Variables and functions */
 int BGW_MQ_NUM_WAITS ; 
 int /*<<< orphan*/  BGW_MQ_WAIT_INTERVAL ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 scalar_t__ InvalidPid ; 
 int /*<<< orphan*/  MyLatch ; 
 int /*<<< orphan*/  ResetLatch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHM_MQ_DETACHED ; 
 int /*<<< orphan*/  SHM_MQ_SUCCESS ; 
 int /*<<< orphan*/  WAIT_EVENT_MQ_INTERNAL ; 
 int WL_LATCH_SET ; 
 int WL_TIMEOUT ; 
 int /*<<< orphan*/  WaitLatch (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,...) ; 
 scalar_t__ queue_get_reader (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shm_mq_get_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * shm_mq_get_sender (int /*<<< orphan*/ ) ; 

__attribute__((used)) static shm_mq_result
ts_shm_mq_wait_for_attach(MessageQueue *queue, shm_mq_handle *ack_queue_handle)
{
	int n;
	PGPROC *reader_proc;

	for (n = 1; n <= BGW_MQ_NUM_WAITS; n++)
	{
		/* The reader is the sender on the ack queue */
		reader_proc = shm_mq_get_sender(shm_mq_get_queue(ack_queue_handle));
		if (reader_proc != NULL)
			return SHM_MQ_SUCCESS;
		else if (queue_get_reader(queue) == InvalidPid)
			return SHM_MQ_DETACHED; /* Reader died after we enqueued our
									 * message */
#if PG96
		WaitLatch(MyLatch, WL_LATCH_SET | WL_TIMEOUT, BGW_MQ_WAIT_INTERVAL);
#else
		WaitLatch(MyLatch, WL_LATCH_SET | WL_TIMEOUT, BGW_MQ_WAIT_INTERVAL, WAIT_EVENT_MQ_INTERNAL);
#endif

		ResetLatch(MyLatch);
		CHECK_FOR_INTERRUPTS();
	}
	return SHM_MQ_DETACHED;
}