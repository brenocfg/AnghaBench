#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32 ;
typedef  int /*<<< orphan*/  STREAM ;
typedef  int /*<<< orphan*/  RDPCLIENT ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  NTHANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  unimpl (char*,int) ; 

__attribute__((used)) static NTSTATUS
disk_device_control(RDPCLIENT * This, NTHANDLE handle, uint32 request, STREAM in, STREAM out)
{
	if (((request >> 16) != 20) || ((request >> 16) != 9))
		return STATUS_INVALID_PARAMETER;

	/* extract operation */
	request >>= 2;
	request &= 0xfff;

	printf("DISK IOCTL %d\n", request);

	switch (request)
	{
		case 25:	/* ? */
		case 42:	/* ? */
		default:
			unimpl("DISK IOCTL %d\n", request);
			return STATUS_INVALID_PARAMETER;
	}

	return STATUS_SUCCESS;
}