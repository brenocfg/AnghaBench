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
typedef  int ULONG ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  scalar_t__ PSYSTEM_HANDLE_INFORMATION_EX ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtQuerySystemInformation ; 
 int /*<<< orphan*/  Ntdll ; 
 int /*<<< orphan*/  PF_INIT_OR_SET_STATUS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PH_LARGE_BUFFER_SIZE ; 
 int /*<<< orphan*/ * PhAllocate (int) ; 
 int /*<<< orphan*/  PhFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STATUS_INFO_LENGTH_MISMATCH ; 
 int /*<<< orphan*/  STATUS_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  STATUS_NO_MEMORY ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  SystemExtendedHandleInformation ; 
 int /*<<< orphan*/  pfNtQuerySystemInformation (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

NTSTATUS PhEnumHandlesEx(PSYSTEM_HANDLE_INFORMATION_EX *Handles)
{
	static ULONG initialBufferSize = 0x10000;
	NTSTATUS status = STATUS_SUCCESS;
	PVOID buffer;
	ULONG bufferSize;

	PF_INIT_OR_SET_STATUS(NtQuerySystemInformation, Ntdll);
	if (!NT_SUCCESS(status))
		return status;

	bufferSize = initialBufferSize;
	buffer = PhAllocate(bufferSize);
	if (buffer == NULL)
		return STATUS_NO_MEMORY;

	while ((status = pfNtQuerySystemInformation(SystemExtendedHandleInformation,
		buffer, bufferSize, NULL)) == STATUS_INFO_LENGTH_MISMATCH) {
		PhFree(buffer);
		bufferSize *= 2;

		// Fail if we're resizing the buffer to something very large.
		if (bufferSize > PH_LARGE_BUFFER_SIZE)
			return STATUS_INSUFFICIENT_RESOURCES;

		buffer = PhAllocate(bufferSize);
		if (buffer == NULL)
			return STATUS_NO_MEMORY;
	}

	if (!NT_SUCCESS(status)) {
		PhFree(buffer);
		return status;
	}

	if (bufferSize <= 0x200000)
		initialBufferSize = bufferSize;
	*Handles = (PSYSTEM_HANDLE_INFORMATION_EX)buffer;

	return status;
}