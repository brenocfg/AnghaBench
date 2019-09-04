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
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  NTHANDLE ;

/* Variables and functions */
#define  ENOSPC 128 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  STATUS_ACCESS_DENIED ; 
 int /*<<< orphan*/  STATUS_DISK_FULL ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int errno ; 
 int /*<<< orphan*/  lseek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static NTSTATUS
disk_write(RDPCLIENT * This, NTHANDLE handle, uint8 * data, uint32 length, uint32 offset, uint32 * result)
{
	int n;

	lseek(handle, offset, SEEK_SET);

	n = write(handle, data, length);

	if (n < 0)
	{
		perror("write");
		*result = 0;
		switch (errno)
		{
			case ENOSPC:
				return STATUS_DISK_FULL;
			default:
				return STATUS_ACCESS_DENIED;
		}
	}

	*result = n;

	return STATUS_SUCCESS;
}