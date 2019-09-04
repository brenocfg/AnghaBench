#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int MaximumLength; int /*<<< orphan*/ * Buffer; scalar_t__ Length; } ;
typedef  TYPE_1__ WCHAR ;
typedef  TYPE_1__ UNICODE_STRING ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/  PWSTR ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  int NTSTATUS ;
typedef  TYPE_1__* LPWSTR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAYSIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  DPRINT (char*,TYPE_1__*,...) ; 
 int /*<<< orphan*/  DPRINT1 (char*,...) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ GetShortPathNameW (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPTR ; 
 int /*<<< orphan*/ * LocalAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  NT_SUCCESS (int) ; 
 int RtlExpandEnvironmentStrings_U (int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*,int*) ; 
 int /*<<< orphan*/  RtlInitUnicodeString (TYPE_1__*,TYPE_1__*) ; 
 int RtlSetEnvironmentVariable (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _wcsicmp (TYPE_1__*,char*) ; 

__attribute__((used)) static
BOOL
SetUserEnvironmentVariable(PWSTR* Environment,
                           LPWSTR lpName,
                           LPWSTR lpValue,
                           BOOL bExpand)
{
    NTSTATUS Status;
    UNICODE_STRING Name;
    UNICODE_STRING SrcValue, DstValue;
    ULONG Length;
    PVOID Buffer = NULL;
    WCHAR ShortName[MAX_PATH];

    if (bExpand)
    {
        RtlInitUnicodeString(&SrcValue, lpValue);

        Length = 2 * MAX_PATH * sizeof(WCHAR);

        DstValue.Length = 0;
        DstValue.MaximumLength = Length;
        DstValue.Buffer = Buffer = LocalAlloc(LPTR, Length);
        if (DstValue.Buffer == NULL)
        {
            DPRINT1("LocalAlloc() failed\n");
            return FALSE;
        }

        Status = RtlExpandEnvironmentStrings_U(*Environment,
                                               &SrcValue,
                                               &DstValue,
                                               &Length);
        if (!NT_SUCCESS(Status))
        {
            DPRINT1("RtlExpandEnvironmentStrings_U() failed (Status %lx)\n", Status);
            DPRINT1("Length %lu\n", Length);

            if (Buffer)
                LocalFree(Buffer);

            return FALSE;
        }
    }
    else
    {
        RtlInitUnicodeString(&DstValue, lpValue);
    }

    if (!_wcsicmp(lpName, L"TEMP") || !_wcsicmp(lpName, L"TMP"))
    {
        if (GetShortPathNameW(DstValue.Buffer, ShortName, ARRAYSIZE(ShortName)))
        {
            RtlInitUnicodeString(&DstValue, ShortName);
        }
        else
        {
            DPRINT("GetShortPathNameW() failed for %S (Error %lu)\n", DstValue.Buffer, GetLastError());
        }

        DPRINT("Buffer: %S\n", ShortName);
    }

    RtlInitUnicodeString(&Name, lpName);

    DPRINT("Value: %wZ\n", &DstValue);

    Status = RtlSetEnvironmentVariable(Environment,
                                       &Name,
                                       &DstValue);

    if (Buffer)
        LocalFree(Buffer);

    if (!NT_SUCCESS(Status))
    {
        DPRINT1("RtlSetEnvironmentVariable() failed (Status %lx)\n", Status);
        return FALSE;
    }

    return TRUE;
}