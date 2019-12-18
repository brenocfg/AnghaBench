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
typedef  int /*<<< orphan*/  uint8 ;
typedef  int uint32 ;
struct TYPE_5__ {TYPE_1__* fileinfo; } ;
struct TYPE_4__ {int flags_and_attributes; } ;
typedef  TYPE_2__ RDPCLIENT ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  size_t NTHANDLE ;

/* Variables and functions */
#define  EISDIR 128 
 int FILE_DIRECTORY_FILE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  STATUS_NOT_IMPLEMENTED ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int errno ; 
 int /*<<< orphan*/  lseek (size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int read (size_t,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static NTSTATUS
disk_read(RDPCLIENT * This, NTHANDLE handle, uint8 * data, uint32 length, uint32 offset, uint32 * result)
{
	int n;

#if 0
	/* browsing dir ????        */
	/* each request is 24 bytes */
	if (This->fileinfo[handle].flags_and_attributes & FILE_DIRECTORY_FILE)
	{
		*result = 0;
		return STATUS_SUCCESS;
	}
#endif

	lseek(handle, offset, SEEK_SET);

	n = read(handle, data, length);

	if (n < 0)
	{
		*result = 0;
		switch (errno)
		{
			case EISDIR:
				/* Implement 24 Byte directory read ??
				   with STATUS_NOT_IMPLEMENTED server doesn't read again */
				/* return STATUS_FILE_IS_A_DIRECTORY; */
				return STATUS_NOT_IMPLEMENTED;
			default:
				perror("read");
				return STATUS_INVALID_PARAMETER;
		}
	}

	*result = n;

	return STATUS_SUCCESS;
}