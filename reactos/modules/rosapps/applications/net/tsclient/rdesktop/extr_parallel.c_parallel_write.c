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
typedef  int /*<<< orphan*/  uint8 ;
typedef  int uint32 ;
typedef  int /*<<< orphan*/  RDPCLIENT ;
typedef  int NTSTATUS ;
typedef  int /*<<< orphan*/  NTHANDLE ;

/* Variables and functions */
#define  EAGAIN 130 
#define  EIO 129 
#define  ENOSPC 128 
 int /*<<< orphan*/  LPGETSTATUS ; 
 int STATUS_DEVICE_OFF_LINE ; 
 int STATUS_DEVICE_PAPER_EMPTY ; 
 int STATUS_DEVICE_POWERED_OFF ; 
 int STATUS_SUCCESS ; 
 int errno ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static NTSTATUS
parallel_write(RDPCLIENT * This, NTHANDLE handle, uint8 * data, uint32 length, uint32 offset, uint32 * result)
{
	int rc = STATUS_SUCCESS;

	int n = write(handle, data, length);
	if (n < 0)
	{
#if defined(LPGETSTATUS)
		int status;
#endif

		*result = 0;
		switch (errno)
		{
			case EAGAIN:
				rc = STATUS_DEVICE_OFF_LINE;
			case ENOSPC:
				rc = STATUS_DEVICE_PAPER_EMPTY;
			case EIO:
				rc = STATUS_DEVICE_OFF_LINE;
			default:
				rc = STATUS_DEVICE_POWERED_OFF;
		}
#if defined(LPGETSTATUS)
		if (ioctl(handle, LPGETSTATUS, &status) == 0)
		{
			/* coming soon: take care for the printer status */
			printf("parallel_write: status = %d, errno = %d\n", status, errno);
		}
#endif
	}
	*result = n;
	return rc;
}