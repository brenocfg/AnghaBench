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
 int FILE_DEVICE_PARALLEL ; 
#define  IOCTL_PAR_QUERY_RAW_DEVICE_ID 128 
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  unimpl (char*,int) ; 

__attribute__((used)) static NTSTATUS
parallel_device_control(RDPCLIENT * This, NTHANDLE handle, uint32 request, STREAM in, STREAM out)
{
	if ((request >> 16) != FILE_DEVICE_PARALLEL)
		return STATUS_INVALID_PARAMETER;

	/* extract operation */
	request >>= 2;
	request &= 0xfff;

	printf("PARALLEL IOCTL %d: ", request);

	switch (request)
	{
		case IOCTL_PAR_QUERY_RAW_DEVICE_ID:

		default:

			printf("\n");
			unimpl("UNKNOWN IOCTL %d\n", request);
	}
	return STATUS_SUCCESS;
}