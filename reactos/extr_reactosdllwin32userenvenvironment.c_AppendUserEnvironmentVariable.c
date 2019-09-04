#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_8__ {int MaximumLength; int /*<<< orphan*/ * Buffer; scalar_t__ Length; } ;
typedef  TYPE_1__ UNICODE_STRING ;
typedef  int /*<<< orphan*/  PWSTR ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  char* LPWSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT1 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LPTR ; 
 int /*<<< orphan*/ * LocalAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlAppendUnicodeToString (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  RtlInitUnicodeString (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  RtlQueryEnvironmentVariable_U (int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  RtlSetEnvironmentVariable (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UNICODE_NULL ; 

__attribute__((used)) static
BOOL
AppendUserEnvironmentVariable(PWSTR* Environment,
                              LPWSTR lpName,
                              LPWSTR lpValue)
{
    NTSTATUS Status;
    UNICODE_STRING Name, Value;

    RtlInitUnicodeString(&Name, lpName);

    Value.Length = 0;
    Value.MaximumLength = 1024 * sizeof(WCHAR);
    Value.Buffer = LocalAlloc(LPTR, Value.MaximumLength);
    if (Value.Buffer == NULL)
        return FALSE;

    Value.Buffer[0] = UNICODE_NULL;

    Status = RtlQueryEnvironmentVariable_U(*Environment,
                                           &Name,
                                           &Value);
    if (NT_SUCCESS(Status))
        RtlAppendUnicodeToString(&Value, L";");

    RtlAppendUnicodeToString(&Value, lpValue);

    Status = RtlSetEnvironmentVariable(Environment,
                                       &Name,
                                       &Value);
    LocalFree(Value.Buffer);
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("RtlSetEnvironmentVariable() failed (Status %lx)\n", Status);
        return FALSE;
    }

    return TRUE;
}