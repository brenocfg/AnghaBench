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
typedef  int /*<<< orphan*/  uint8 ;
typedef  scalar_t__ uint32 ;
struct async_iorequest {scalar_t__ fd; scalar_t__ major; struct async_iorequest* next; int /*<<< orphan*/  id; int /*<<< orphan*/  device; } ;
struct TYPE_5__ {struct async_iorequest* iorequest; } ;
typedef  TYPE_1__ RDPCLIENT ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  True ; 
 struct async_iorequest* rdpdr_remove_iorequest (TYPE_1__*,struct async_iorequest*,struct async_iorequest*) ; 
 int /*<<< orphan*/  rdpdr_send_completion (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int) ; 

BOOL
rdpdr_abort_io(RDPCLIENT * This, uint32 fd, uint32 major, NTSTATUS status)
{
	uint32 result;
	struct async_iorequest *iorq;
	struct async_iorequest *prev;

	iorq = This->iorequest;
	prev = NULL;
	while (iorq != NULL)
	{
		/* Only remove from table when major is not set, or when correct major is supplied.
		   Abort read should not abort a write io request. */
		if ((iorq->fd == fd) && (major == 0 || iorq->major == major))
		{
			result = 0;
			rdpdr_send_completion(This, iorq->device, iorq->id, status, result, (uint8 *) "",
					      1);

			iorq = rdpdr_remove_iorequest(This, prev, iorq);
			return True;
		}

		prev = iorq;
		iorq = iorq->next;
	}

	return False;
}