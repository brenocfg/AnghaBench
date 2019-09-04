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
struct TYPE_3__ {int /*<<< orphan*/ * UniqueThread; scalar_t__ UniqueProcess; } ;
typedef  int /*<<< orphan*/ * PHANDLE ;
typedef  int /*<<< orphan*/  OBJECT_ATTRIBUTES ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  scalar_t__ LONG_PTR ;
typedef  scalar_t__ HANDLE ;
typedef  TYPE_1__ CLIENT_ID ;
typedef  int /*<<< orphan*/  ACCESS_MASK ;

/* Variables and functions */
 scalar_t__ GetCurrentProcessId () ; 
 int /*<<< orphan*/  InitializeObjectAttributes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtCurrentProcess () ; 
 int /*<<< orphan*/  NtOpenProcess ; 
 int /*<<< orphan*/  Ntdll ; 
 int /*<<< orphan*/  PF_INIT_OR_SET_STATUS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  pfNtOpenProcess (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 

NTSTATUS PhOpenProcess(PHANDLE ProcessHandle, ACCESS_MASK DesiredAccess, HANDLE ProcessId)
{
	NTSTATUS status = STATUS_SUCCESS;
	OBJECT_ATTRIBUTES objectAttributes;
	CLIENT_ID clientId;

	if ((LONG_PTR)ProcessId == (LONG_PTR)GetCurrentProcessId()) {
		*ProcessHandle = NtCurrentProcess();
		return 0;
	}

	PF_INIT_OR_SET_STATUS(NtOpenProcess, Ntdll);
	if (!NT_SUCCESS(status))
		return status;

	clientId.UniqueProcess = ProcessId;
	clientId.UniqueThread = NULL;

	InitializeObjectAttributes(&objectAttributes, NULL, 0, NULL, NULL);
	status = pfNtOpenProcess(ProcessHandle, DesiredAccess, &objectAttributes, &clientId);

	return status;
}