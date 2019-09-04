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
struct fileinfo {int /*<<< orphan*/  notify; int /*<<< orphan*/  info_class; int /*<<< orphan*/  pdir; } ;
struct TYPE_4__ {struct fileinfo* fileinfo; } ;
typedef  TYPE_1__ RDPCLIENT ;
typedef  scalar_t__ NTSTATUS ;
typedef  size_t NTHANDLE ;
typedef  int /*<<< orphan*/  NOTIFY ;

/* Variables and functions */
 scalar_t__ NotifyInfo (TYPE_1__*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ STATUS_INVALID_DEVICE_REQUEST ; 
 scalar_t__ STATUS_NOTIFY_ENUM_DIR ; 
 scalar_t__ STATUS_PENDING ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

NTSTATUS
disk_check_notify(RDPCLIENT * This, NTHANDLE handle)
{
	struct fileinfo *pfinfo;
	NTSTATUS status = STATUS_PENDING;

	NOTIFY notify;

	pfinfo = &(This->fileinfo[handle]);
	if (!pfinfo->pdir)
		return STATUS_INVALID_DEVICE_REQUEST;



	status = NotifyInfo(This, handle, pfinfo->info_class, &notify);

	if (status != STATUS_PENDING)
		return status;

	if (memcmp(&pfinfo->notify, &notify, sizeof(NOTIFY)))
	{
		/*printf("disk_check_notify found changed event\n"); */
		memcpy(&pfinfo->notify, &notify, sizeof(NOTIFY));
		status = STATUS_NOTIFY_ENUM_DIR;
	}

	return status;


}