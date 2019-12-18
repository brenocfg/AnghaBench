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
typedef  int uint32 ;
struct fileinfo {int info_class; int /*<<< orphan*/  notify; } ;
struct TYPE_4__ {struct fileinfo* fileinfo; } ;
typedef  TYPE_1__ RDPCLIENT ;
typedef  scalar_t__ NTSTATUS ;
typedef  size_t NTHANDLE ;

/* Variables and functions */
 scalar_t__ NotifyInfo (TYPE_1__*,size_t,int,int /*<<< orphan*/ *) ; 
 scalar_t__ STATUS_PENDING ; 
 scalar_t__ STATUS_SUCCESS ; 

NTSTATUS
disk_create_notify(RDPCLIENT * This, NTHANDLE handle, uint32 info_class)
{

	struct fileinfo *pfinfo;
	NTSTATUS ret = STATUS_PENDING;

	/* printf("start disk_create_notify info_class %X\n", info_class); */

	pfinfo = &(This->fileinfo[handle]);
	pfinfo->info_class = info_class;

	ret = NotifyInfo(This, handle, info_class, &pfinfo->notify);

	if (info_class & 0x1000)
	{			/* ???? */
		if (ret == STATUS_PENDING)
			return STATUS_SUCCESS;
	}

	/* printf("disk_create_notify: num_entries %d\n", pfinfo->notify.num_entries); */


	return ret;

}