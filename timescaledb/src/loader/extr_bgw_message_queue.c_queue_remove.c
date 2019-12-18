#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ num_elements; size_t read_upto; int /*<<< orphan*/  lock; int /*<<< orphan*/ * buffer; } ;
typedef  TYPE_1__ MessageQueue ;
typedef  int /*<<< orphan*/  BgwMessage ;

/* Variables and functions */
 int BGW_MQ_MAX_MESSAGES ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 scalar_t__ MyProcPid ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * palloc (int) ; 
 scalar_t__ queue_get_reader (TYPE_1__*) ; 

__attribute__((used)) static BgwMessage *
queue_remove(MessageQueue *queue)
{
	BgwMessage *message = NULL;

	LWLockAcquire(queue->lock, LW_EXCLUSIVE);
	if (queue_get_reader(queue) != MyProcPid)
		ereport(ERROR,
				(errmsg(
					"cannot read if not reader for TimescaleDB background worker message queue")));

	if (queue->num_elements > 0)
	{
		message = palloc(sizeof(BgwMessage));
		memcpy(message, &queue->buffer[queue->read_upto], sizeof(BgwMessage));
		queue->read_upto = (queue->read_upto + 1) % BGW_MQ_MAX_MESSAGES;
		queue->num_elements--;
	}
	LWLockRelease(queue->lock);
	return message;
}