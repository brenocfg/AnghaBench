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
typedef  int /*<<< orphan*/  pid_t ;
struct TYPE_3__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  reader_pid; } ;
typedef  TYPE_1__ MessageQueue ;

/* Variables and functions */
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 

__attribute__((used)) static pid_t
queue_get_reader(MessageQueue *queue)
{
	pid_t reader;
	volatile MessageQueue *vq = queue;

	SpinLockAcquire(&vq->mutex);
	reader = vq->reader_pid;
	SpinLockRelease(&vq->mutex);
	return reader;
}