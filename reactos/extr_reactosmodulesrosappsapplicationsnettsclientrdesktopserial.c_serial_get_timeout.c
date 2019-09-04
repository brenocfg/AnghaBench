#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct TYPE_8__ {TYPE_1__* rdpdr_device; } ;
struct TYPE_7__ {int read_total_timeout_multiplier; int read_total_timeout_constant; int read_interval_timeout; } ;
struct TYPE_6__ {scalar_t__ device_type; scalar_t__ pdevice_data; } ;
typedef  TYPE_2__ SERIAL_DEVICE ;
typedef  TYPE_3__ RDPCLIENT ;
typedef  int /*<<< orphan*/  NTHANDLE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ DEVICE_TYPE_SERIAL ; 
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  True ; 
 int get_device_index (TYPE_3__*,int /*<<< orphan*/ ) ; 

BOOL
serial_get_timeout(RDPCLIENT * This, NTHANDLE handle, uint32 length, uint32 * timeout, uint32 * itv_timeout)
{
	int index;
	SERIAL_DEVICE *pser_inf;

	index = get_device_index(This, handle);
	if (index < 0)
		return True;

	if (This->rdpdr_device[index].device_type != DEVICE_TYPE_SERIAL)
	{
		return False;
	}

	pser_inf = (SERIAL_DEVICE *) This->rdpdr_device[index].pdevice_data;

	*timeout =
		pser_inf->read_total_timeout_multiplier * length +
		pser_inf->read_total_timeout_constant;
	*itv_timeout = pser_inf->read_interval_timeout;
	return True;
}