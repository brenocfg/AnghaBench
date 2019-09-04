#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_10__ {int Length; int MaximumLength; int /*<<< orphan*/  Buffer; } ;
typedef  TYPE_1__ UNICODE_STRING ;
typedef  int ULONG ;
struct TYPE_11__ {int NameLength; int /*<<< orphan*/  Name; } ;
typedef  TYPE_2__* PKEY_NAME_INFORMATION ;
typedef  int /*<<< orphan*/  OBJECT_ATTRIBUTES ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/ * HANDLE ;

/* Variables and functions */
 int FIELD_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InitializeObjectAttributes (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KEY_NAME_INFORMATION ; 
 int /*<<< orphan*/  KEY_READ ; 
 int /*<<< orphan*/  KeyNameInformation ; 
 int /*<<< orphan*/ * Name ; 
 int /*<<< orphan*/  NtClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NtOpenKey (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NtQueryKey (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int,int*) ; 
 int /*<<< orphan*/  OBJ_CASE_INSENSITIVE ; 
 TYPE_1__ RTL_CONSTANT_STRING (char*) ; 
 TYPE_2__* RtlAllocateHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ RtlCompareUnicodeString (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlFreeHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  RtlGetProcessHeap () ; 
 int /*<<< orphan*/  STATUS_BUFFER_TOO_SMALL ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  ok_ntstatus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok_size_t (int,int) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static
void
Test_KeyNameInformation(void)
{
    UNICODE_STRING HKLM_Name = RTL_CONSTANT_STRING(L"\\Registry\\Machine");
    UNICODE_STRING HKLM_Software_Name = RTL_CONSTANT_STRING(L"\\Registry\\Machine\\Software");
    UNICODE_STRING Software_Name = RTL_CONSTANT_STRING(L"Software");
    UNICODE_STRING InfoName;
    HANDLE HKLM_Key, HKLM_Software_Key;
    PKEY_NAME_INFORMATION NameInformation;
    ULONG InfoLength;
    OBJECT_ATTRIBUTES ObjectAttributes;
    NTSTATUS Status;

    /* Open the HKCU key */
    InitializeObjectAttributes(&ObjectAttributes,
        &HKLM_Name,
        OBJ_CASE_INSENSITIVE,
        NULL,
        NULL);
    Status = NtOpenKey(&HKLM_Key, KEY_READ, &ObjectAttributes);
    ok_ntstatus(Status, STATUS_SUCCESS);

    /* Get the name info length */
    InfoLength = 0;
    Status = NtQueryKey(HKLM_Key, KeyNameInformation, NULL, 0, &InfoLength);
    ok_ntstatus(Status, STATUS_BUFFER_TOO_SMALL);
    ok_size_t(InfoLength, FIELD_OFFSET(KEY_NAME_INFORMATION, Name[HKLM_Name.Length/sizeof(WCHAR)]));

    /* Get it for real */
    NameInformation = RtlAllocateHeap(RtlGetProcessHeap(), 0, InfoLength);
    if (!NameInformation)
    {
        skip("Out of memory\n");
        return;
    }

    Status = NtQueryKey(HKLM_Key, KeyNameInformation, NameInformation, InfoLength, &InfoLength);
    ok_ntstatus(Status, STATUS_SUCCESS);
    ok_size_t(InfoLength, FIELD_OFFSET(KEY_NAME_INFORMATION, Name[HKLM_Name.Length/sizeof(WCHAR)]));
    ok_size_t(NameInformation->NameLength, HKLM_Name.Length);

    InfoName.Buffer = NameInformation->Name;
    InfoName.Length = NameInformation->NameLength;
    InfoName.MaximumLength = NameInformation->NameLength;
    ok(RtlCompareUnicodeString(&InfoName, &HKLM_Name, TRUE) == 0, "%.*S\n",
        InfoName.Length, InfoName.Buffer);

    RtlFreeHeap(RtlGetProcessHeap(), 0, NameInformation);

    /* Open one subkey */
    InitializeObjectAttributes(&ObjectAttributes,
        &Software_Name,
        OBJ_CASE_INSENSITIVE,
        HKLM_Key,
        NULL);
    Status = NtOpenKey(&HKLM_Software_Key, KEY_READ, &ObjectAttributes);
    ok_ntstatus(Status, STATUS_SUCCESS);

    /* Get the name info length */
    InfoLength = 0;
    Status = NtQueryKey(HKLM_Software_Key, KeyNameInformation, NULL, 0, &InfoLength);
    ok_ntstatus(Status, STATUS_BUFFER_TOO_SMALL);
    ok_size_t(InfoLength, FIELD_OFFSET(KEY_NAME_INFORMATION, Name[HKLM_Software_Name.Length/sizeof(WCHAR)]));

    /* Get it for real */
    NameInformation = RtlAllocateHeap(RtlGetProcessHeap(), 0, InfoLength);
    ok(NameInformation != NULL, "\n");

    Status = NtQueryKey(HKLM_Software_Key, KeyNameInformation, NameInformation, InfoLength, &InfoLength);
    ok_ntstatus(Status, STATUS_SUCCESS);
    ok_size_t(InfoLength, FIELD_OFFSET(KEY_NAME_INFORMATION, Name[HKLM_Software_Name.Length/sizeof(WCHAR)]));
    ok_size_t(NameInformation->NameLength, HKLM_Software_Name.Length);

    InfoName.Buffer = NameInformation->Name;
    InfoName.Length = NameInformation->NameLength;
    InfoName.MaximumLength = NameInformation->NameLength;
    ok(RtlCompareUnicodeString(&InfoName, &HKLM_Software_Name, TRUE) == 0, "%.*S\n",
        InfoName.Length, InfoName.Buffer);

    RtlFreeHeap(RtlGetProcessHeap(), 0, NameInformation);

    NtClose(HKLM_Software_Key);
    NtClose(HKLM_Key);
}