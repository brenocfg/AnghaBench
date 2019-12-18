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
typedef  int /*<<< orphan*/  uint8 ;
typedef  scalar_t__ uint32 ;
struct TYPE_3__ {scalar_t__ event_txempty; } ;
typedef  TYPE_1__ SERIAL_DEVICE ;
typedef  int /*<<< orphan*/  RDPCLIENT ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  NTHANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_SERIAL (char*) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 TYPE_1__* get_serial_info (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static NTSTATUS
serial_write(RDPCLIENT * This, NTHANDLE handle, uint8 * data, uint32 length, uint32 offset, uint32 * result)
{
	SERIAL_DEVICE *pser_inf;

	pser_inf = get_serial_info(This, handle);

	*result = write(handle, data, length);

	if (*result > 0)
		pser_inf->event_txempty = *result;

	DEBUG_SERIAL(("serial_write length %d, offset %d result %d\n", length, offset, *result));

	return STATUS_SUCCESS;
}