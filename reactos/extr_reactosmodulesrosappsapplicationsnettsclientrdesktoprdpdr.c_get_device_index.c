#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* rdpdr_device; } ;
struct TYPE_4__ {scalar_t__ handle; } ;
typedef  TYPE_2__ RDPCLIENT ;
typedef  scalar_t__ NTHANDLE ;

/* Variables and functions */
 int RDPDR_MAX_DEVICES ; 

int
get_device_index(RDPCLIENT * This, NTHANDLE handle)
{
	int i;
	for (i = 0; i < RDPDR_MAX_DEVICES; i++)
	{
		if (This->rdpdr_device[i].handle == handle)
			return i;
	}
	return -1;
}