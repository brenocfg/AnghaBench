#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  procLatch; } ;
struct TYPE_5__ {size_t num_elements; size_t read_upto; int /*<<< orphan*/  lock; int /*<<< orphan*/ * buffer; } ;
typedef  int /*<<< orphan*/  QueueResponseType ;
typedef  TYPE_1__ MessageQueue ;
typedef  int /*<<< orphan*/  BgwMessage ;

/* Variables and functions */
 size_t BGW_MQ_MAX_MESSAGES ; 
 TYPE_4__* BackendPidGetProc (scalar_t__) ; 
 scalar_t__ InvalidPid ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int /*<<< orphan*/  MESSAGE_SENT ; 
 int /*<<< orphan*/  QUEUE_FULL ; 
 int /*<<< orphan*/  READER_DETACHED ; 
 int /*<<< orphan*/  SetLatch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ queue_get_reader (TYPE_1__*) ; 

__attribute__((used)) static QueueResponseType
queue_add(MessageQueue *queue, BgwMessage *message)
{
	QueueResponseType message_result = QUEUE_FULL;

	LWLockAcquire(queue->lock, LW_EXCLUSIVE);
	if (queue->num_elements < BGW_MQ_MAX_MESSAGES)
	{
		memcpy(&queue->buffer[(queue->read_upto + queue->num_elements) % BGW_MQ_MAX_MESSAGES],
			   message,
			   sizeof(BgwMessage));
		queue->num_elements++;
		message_result = MESSAGE_SENT;
	}
	LWLockRelease(queue->lock);

	if (queue_get_reader(queue) != InvalidPid)
		SetLatch(&BackendPidGetProc(queue_get_reader(queue))->procLatch);
	else
		message_result = READER_DETACHED;
	return message_result;
}