#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* fileinfo; TYPE_1__* rdpdr_device; } ;
struct TYPE_6__ {int device_id; } ;
struct TYPE_5__ {int device_type; int handle; } ;
typedef  TYPE_3__ RDPCLIENT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
#define  DEVICE_TYPE_DISK 132 
#define  DEVICE_TYPE_PARALLEL 131 
#define  DEVICE_TYPE_PRINTER 130 
#define  DEVICE_TYPE_SCARD 129 
#define  DEVICE_TYPE_SERIAL 128 
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  True ; 

__attribute__((used)) static BOOL
rdpdr_handle_ok(RDPCLIENT * This, int device, int handle)
{
	switch (This->rdpdr_device[device].device_type)
	{
		case DEVICE_TYPE_PARALLEL:
		case DEVICE_TYPE_SERIAL:
		case DEVICE_TYPE_PRINTER:
		case DEVICE_TYPE_SCARD:
			if (This->rdpdr_device[device].handle != handle)
				return False;
			break;
		case DEVICE_TYPE_DISK:
			if (This->fileinfo[handle].device_id != device)
				return False;
			break;
	}
	return True;
}