#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buffer ;
typedef  char WCHAR ;
struct TYPE_9__ {int MaximumLength; int Length; char* Buffer; } ;
typedef  TYPE_1__ UNICODE_STRING ;
typedef  TYPE_1__* PUNICODE_STRING ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  DotDll ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  RtlDosApplyFileIsolationRedirection_Ustr (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlInitEmptyUnicodeString (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  RtlInitUnicodeString (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  STATUS_BUFFER_TOO_SMALL ; 
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  STATUS_SXS_KEY_NOT_FOUND ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  wcscpy (char*,char*) ; 
 int wcslen (char*) ; 

void TestBuffers()
{
    UNICODE_STRING Param, DynamicString, StaticString;
    PUNICODE_STRING StringUsed = NULL;
    NTSTATUS Status;
    WCHAR buffer[MAX_PATH];

    RtlInitEmptyUnicodeString(&DynamicString, NULL, 0);
    Status = RtlDosApplyFileIsolationRedirection_Ustr(TRUE,
                                                      NULL,
                                                      NULL,
                                                      NULL,
                                                      &DynamicString,
                                                      &StringUsed,
                                                      NULL,
                                                      NULL,
                                                      NULL);
    ok(Status ==STATUS_INVALID_PARAMETER, "0x%lx\n", Status);

    RtlInitEmptyUnicodeString(&Param, NULL, 0);
    RtlInitEmptyUnicodeString(&DynamicString, NULL, 0);
    Status = RtlDosApplyFileIsolationRedirection_Ustr(TRUE,
                                                      &Param,
                                                      NULL,
                                                      NULL,
                                                      &DynamicString,
                                                      &StringUsed,
                                                      NULL,
                                                      NULL,
                                                      NULL);
    ok(Status ==STATUS_SXS_KEY_NOT_FOUND, "0x%lx\n", Status);

    /* Tests for NULL termination of OriginalName */
    Param.MaximumLength = Param.Length = 12 * sizeof(WCHAR);
    Param.Buffer = L"comctl32.dllcrapcrap";
    RtlInitEmptyUnicodeString(&DynamicString, NULL, 0);
    Status = RtlDosApplyFileIsolationRedirection_Ustr(TRUE,
                                                      &Param,
                                                      NULL,
                                                      NULL,
                                                      &DynamicString,
                                                      &StringUsed,
                                                      NULL,
                                                      NULL,
                                                      NULL);
    ok(Status ==STATUS_SUCCESS, "\n");

    /* Tests for the Extension parameter */
    RtlInitUnicodeString(&Param, L"comctl32.dll");
    RtlInitEmptyUnicodeString(&DynamicString, NULL, 0);
    Status = RtlDosApplyFileIsolationRedirection_Ustr(TRUE,
                                                      &Param,
                                                      NULL,
                                                      NULL,
                                                      &DynamicString,
                                                      &StringUsed,
                                                      NULL,
                                                      NULL,
                                                      NULL);
    ok(Status ==STATUS_SUCCESS, "\n");

    RtlInitUnicodeString(&Param, L"comctl32");
    RtlInitEmptyUnicodeString(&DynamicString, NULL, 0);
    Status = RtlDosApplyFileIsolationRedirection_Ustr(TRUE,
                                                      &Param,
                                                      NULL,
                                                      NULL,
                                                      &DynamicString,
                                                      &StringUsed,
                                                      NULL,
                                                      NULL,
                                                      NULL);
    ok(Status ==STATUS_SXS_KEY_NOT_FOUND, "0x%lx\n", Status);

    RtlInitUnicodeString(&Param, L"comctl32");
    RtlInitEmptyUnicodeString(&DynamicString, NULL, 0);
    Status = RtlDosApplyFileIsolationRedirection_Ustr(TRUE,
                                                      &Param,
                                                      &DotDll,
                                                      NULL,
                                                      &DynamicString,
                                                      &StringUsed,
                                                      NULL,
                                                      NULL,
                                                      NULL);
    ok(Status ==STATUS_SUCCESS, "\n");

    /* Tests for the DynamicString parameter */
    RtlInitUnicodeString(&Param, L"comctl32.dll");
    RtlInitEmptyUnicodeString(&DynamicString, NULL, 0);
    Status = RtlDosApplyFileIsolationRedirection_Ustr(TRUE,
                                                      &Param,
                                                      NULL,
                                                      NULL,
                                                      &DynamicString,
                                                      &StringUsed,
                                                      NULL,
                                                      NULL,
                                                      NULL);
    ok(Status ==STATUS_SUCCESS, "\n");
    ok(DynamicString.Length >0 , "\n");
    ok(DynamicString.MaximumLength == DynamicString.Length + sizeof(WCHAR) , "\n");
    if (DynamicString.Buffer && DynamicString.Length)
        ok(wcslen(DynamicString.Buffer) * sizeof(WCHAR) == DynamicString.Length, "got %d and %d\n", wcslen(DynamicString.Buffer)  * sizeof(WCHAR) , DynamicString.Length);
    else
        ok(DynamicString.Buffer != NULL, "Expected non NULL buffer\n");
    ok(StringUsed == &DynamicString, "\n");

    /* Tests for the StaticString parameter */
    wcscpy(buffer, L"comctl32.dll");
    StaticString.Buffer = buffer;
    StaticString.Length = sizeof(L"comctl32.dll");
    StaticString.MaximumLength = sizeof(buffer);
    Param = StaticString;
    Status = RtlDosApplyFileIsolationRedirection_Ustr(TRUE,
                                                      &Param,
                                                      NULL,
                                                      &StaticString,
                                                      NULL,
                                                      &StringUsed,
                                                      NULL,
                                                      NULL,
                                                      NULL);
    ok(Status ==STATUS_SXS_KEY_NOT_FOUND, "0x%lx\n", Status);

    wcscpy(buffer, L"comctl32.dll");
    StaticString.Buffer = buffer;
    StaticString.Length = sizeof(L"comctl32.dll");
    StaticString.MaximumLength = sizeof(buffer);
    Status = RtlDosApplyFileIsolationRedirection_Ustr(TRUE,
                                                      &StaticString,
                                                      NULL,
                                                      &StaticString,
                                                      NULL,
                                                      &StringUsed,
                                                      NULL,
                                                      NULL,
                                                      NULL);
    ok(Status ==STATUS_SXS_KEY_NOT_FOUND, "0x%lx\n", Status);

    RtlInitUnicodeString(&Param, L"comctl32.dll");
    RtlInitEmptyUnicodeString(&StaticString, buffer, sizeof(buffer));
    Status = RtlDosApplyFileIsolationRedirection_Ustr(TRUE,
                                                      &Param,
                                                      NULL,
                                                      &StaticString,
                                                      NULL,
                                                      &StringUsed,
                                                      NULL,
                                                      NULL,
                                                      NULL);
    ok(Status ==STATUS_SUCCESS, "\n");
    ok(StaticString.Length >0 , "\n");
    ok(StaticString.MaximumLength == sizeof(buffer) , "\n");
    if (StaticString.Buffer && StaticString.Length)
        ok(wcslen(StaticString.Buffer) * sizeof(WCHAR) == StaticString.Length, "got %d and %d\n", wcslen(StaticString.Buffer)  * sizeof(WCHAR) , StaticString.Length);
    else
        ok(StaticString.Length != 0, "Expected non 0 lenght\n");
    ok(StringUsed == &StaticString, "\n");

    RtlInitEmptyUnicodeString(&StaticString, buffer, 5 * sizeof(WCHAR));
    Status = RtlDosApplyFileIsolationRedirection_Ustr(TRUE,
                                                      &Param,
                                                      NULL,
                                                      &StaticString,
                                                      NULL,
                                                      &StringUsed,
                                                      NULL,
                                                      NULL,
                                                      NULL);
    ok(Status == STATUS_BUFFER_TOO_SMALL, "0x%lx\n", Status);

    RtlInitUnicodeString(&Param, L"comctl32.dll");
    RtlInitEmptyUnicodeString(&StaticString, buffer, sizeof(buffer));
    RtlInitEmptyUnicodeString(&DynamicString, NULL, 0);
    Status = RtlDosApplyFileIsolationRedirection_Ustr(TRUE,
                                                      &Param,
                                                      NULL,
                                                      &StaticString,
                                                      &DynamicString,
                                                      &StringUsed,
                                                      NULL,
                                                      NULL,
                                                      NULL);
    ok(Status ==STATUS_SUCCESS, "\n");
    ok(StaticString.Length >0 , "\n");
    ok(StaticString.MaximumLength == sizeof(buffer) , "\n");
    if (StaticString.Buffer && StaticString.Length)
        ok(wcslen(StaticString.Buffer) * sizeof(WCHAR) == StaticString.Length, "got %d and %d\n", wcslen(StaticString.Buffer)  * sizeof(WCHAR) , StaticString.Length);
    else
        ok(StaticString.Length != 0, "Expected non 0 lenght\n");
    ok(DynamicString.Buffer == NULL, "\n");
    ok(DynamicString.Length == 0, "\n");
    ok(DynamicString.MaximumLength == 0, "\n");
    ok(StringUsed == &StaticString, "\n");

    /* Test a small buffer and a dynamic buffer */
    RtlInitUnicodeString(&Param, L"comctl32.dll");
    RtlInitEmptyUnicodeString(&StaticString, buffer, 5 * sizeof(WCHAR));
    RtlInitEmptyUnicodeString(&DynamicString, NULL, 0);
    StaticString.Buffer[0] = 1;
    Status = RtlDosApplyFileIsolationRedirection_Ustr(TRUE,
                                                      &Param,
                                                      NULL,
                                                      &StaticString,
                                                      &DynamicString,
                                                      &StringUsed,
                                                      NULL,
                                                      NULL,
                                                      NULL);
    ok(Status ==STATUS_SUCCESS, "\n");
    ok(StaticString.Buffer == buffer, "\n");
    ok(StaticString.Length == 0 , "%d\n", StaticString.Length);
    ok(StaticString.Buffer[0] == 0, "\n");
    ok(StaticString.MaximumLength == 5 * sizeof(WCHAR) , "%d\n", StaticString.MaximumLength);
    ok(DynamicString.Length >0 , "\n");
    ok(DynamicString.MaximumLength == DynamicString.Length + sizeof(WCHAR) , "\n");
    if (DynamicString.Buffer && DynamicString.Length)
        ok(wcslen(DynamicString.Buffer) * sizeof(WCHAR) == DynamicString.Length, "got %d and %d\n", wcslen(DynamicString.Buffer)  * sizeof(WCHAR) , DynamicString.Length);
    else
        ok(DynamicString.Length != 0, "Expected non 0 lenght\n");

    ok(StringUsed == &DynamicString, "\n");
}