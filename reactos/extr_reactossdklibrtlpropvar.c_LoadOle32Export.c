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
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  PCHAR ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  ANSI_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  LdrGetProcedureAddress (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LdrLoadDll (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Old32Dll ; 
 int /*<<< orphan*/  RtlInitAnsiString (int /*<<< orphan*/ *,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  RtlRaiseStatus (int /*<<< orphan*/ ) ; 

PVOID
LoadOle32Export(PVOID * BaseAddress, const PCHAR ProcedureName)
{
    NTSTATUS Status;
    ANSI_STRING ExportName;
    PVOID ProcedureAddress;

    /* First load ole32.dll */
    Status = LdrLoadDll(NULL, NULL, &Old32Dll, BaseAddress);
    if (!NT_SUCCESS(Status))
    {
        RtlRaiseStatus(Status);
    }

    RtlInitAnsiString(&ExportName, ProcedureName);

    /* Look for the procedure */
    Status = LdrGetProcedureAddress(*BaseAddress, &ExportName,
                                    0, &ProcedureAddress);
    if (!NT_SUCCESS(Status))
    {
        RtlRaiseStatus(Status);
    }

    /* Return its address */
    return ProcedureAddress;
}