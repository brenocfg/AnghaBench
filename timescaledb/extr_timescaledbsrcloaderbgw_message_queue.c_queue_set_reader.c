#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ pid_t ;
struct TYPE_3__ {scalar_t__ reader_pid; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ MessageQueue ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ InvalidPid ; 
 scalar_t__ MyProcPid ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*,scalar_t__) ; 
 int /*<<< orphan*/  errmsg (char*) ; 

__attribute__((used)) static void
queue_set_reader(MessageQueue *queue)
{
	volatile MessageQueue *vq = queue;
	pid_t reader_pid;

	SpinLockAcquire(&vq->mutex);
	if (vq->reader_pid == InvalidPid)
	{
		vq->reader_pid = MyProcPid;
	}
	reader_pid = vq->reader_pid;
	SpinLockRelease(&vq->mutex);
	if (reader_pid != MyProcPid)
		ereport(ERROR,
				(errmsg("only one reader allowed for TimescaleDB background worker message queue"),
				 errhint("Current process is %d", reader_pid)));
}