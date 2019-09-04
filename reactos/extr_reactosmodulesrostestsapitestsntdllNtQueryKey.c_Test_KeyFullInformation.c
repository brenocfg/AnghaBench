#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_12__ {int Length; } ;
typedef  TYPE_2__ UNICODE_STRING ;
typedef  int /*<<< orphan*/  UNICODE_NULL ;
typedef  int ULONG ;
struct TYPE_11__ {int QuadPart; } ;
struct TYPE_13__ {int TitleIndex; int ClassOffset; int ClassLength; int SubKeys; int MaxNameLen; int MaxClassLen; int Values; int MaxValueNameLen; int MaxValueDataLen; int* Class; TYPE_1__ LastWriteTime; } ;
typedef  TYPE_3__* PKEY_FULL_INFORMATION ;
typedef  int /*<<< orphan*/  OBJECT_ATTRIBUTES ;
typedef  int NTSTATUS ;
typedef  int /*<<< orphan*/ * HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/ ********* Class ; 
 int FIELD_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ *********) ; 
 int /*<<< orphan*/  InitializeObjectAttributes (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KEY_ALL_ACCESS ; 
 int /*<<< orphan*/  KEY_FULL_INFORMATION ; 
 int /*<<< orphan*/  KEY_READ ; 
 int /*<<< orphan*/  KeyFullInformation ; 
 int /*<<< orphan*/  NtClose (int /*<<< orphan*/ *) ; 
 int NtCreateKey (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int NtDeleteKey (int /*<<< orphan*/ *) ; 
 int NtOpenKey (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int NtQueryKey (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*,int,int*) ; 
 int /*<<< orphan*/  OBJ_CASE_INSENSITIVE ; 
 int /*<<< orphan*/  REG_OPTION_VOLATILE ; 
 TYPE_2__ RTL_CONSTANT_STRING (char*) ; 
 TYPE_3__* RtlAllocateHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RtlFillMemory (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  RtlFreeHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  RtlGetProcessHeap () ; 
 int STATUS_BUFFER_OVERFLOW ; 
 int STATUS_BUFFER_TOO_SMALL ; 
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  ok_ntstatus (int,int) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static
void
Test_KeyFullInformation(void)
{
    UNICODE_STRING HKLM_Name = RTL_CONSTANT_STRING(L"\\Registry\\Machine");
    UNICODE_STRING Software_Name = RTL_CONSTANT_STRING(L"Software");
    UNICODE_STRING Test_Name = RTL_CONSTANT_STRING(L"NtQueryKey_apitest");
    UNICODE_STRING MyClass = RTL_CONSTANT_STRING(L"MyClass");
    HANDLE HKLM_Key, HKLM_Software_Key, Test_Key;
    ULONG FullInformationLength;
    PKEY_FULL_INFORMATION FullInformation;
    ULONG InfoLength;
    OBJECT_ATTRIBUTES ObjectAttributes;
    NTSTATUS Status;

    FullInformationLength = FIELD_OFFSET(KEY_FULL_INFORMATION, Class[100]);
    FullInformation = RtlAllocateHeap(RtlGetProcessHeap(), 0, FullInformationLength);
    if (!FullInformation)
    {
        skip("Out of memory\n");
        return;
    }

    InitializeObjectAttributes(&ObjectAttributes,
        &HKLM_Name,
        OBJ_CASE_INSENSITIVE,
        NULL,
        NULL);
    Status = NtOpenKey(&HKLM_Key, KEY_READ, &ObjectAttributes);
    ok_ntstatus(Status, STATUS_SUCCESS);

    InfoLength = 0x55555555;
    Status = NtQueryKey(HKLM_Key, KeyFullInformation, NULL, 0, &InfoLength);
    ok(Status == STATUS_BUFFER_TOO_SMALL, "Status = 0x%lx\n", Status);
    ok(InfoLength == FIELD_OFFSET(KEY_FULL_INFORMATION, Class), "InfoLength = %lu\n", InfoLength);

    RtlFillMemory(FullInformation, FullInformationLength, 0x55);
    InfoLength = 0x55555555;
    Status = NtQueryKey(HKLM_Key, KeyFullInformation, FullInformation, FIELD_OFFSET(KEY_FULL_INFORMATION, Class), &InfoLength);
    ok(Status == STATUS_SUCCESS, "Status = 0x%lx\n", Status);
    ok(InfoLength == FIELD_OFFSET(KEY_FULL_INFORMATION, Class), "InfoLength = %lu\n", InfoLength);
    ok(FullInformation->LastWriteTime.QuadPart != 0x5555555555555555, "LastWriteTime unchanged\n");
    ok(FullInformation->TitleIndex == 0, "TitleIndex = %lu\n", FullInformation->TitleIndex);
    ok(FullInformation->ClassOffset == 0xffffffff, "ClassOffset = %lu\n", FullInformation->ClassOffset);
    ok(FullInformation->ClassLength == 0, "ClassLength = %lu\n", FullInformation->ClassLength);
    ok(FullInformation->SubKeys >= 5 && FullInformation->SubKeys < 20, "SubKeys = %lu\n", FullInformation->SubKeys);
    ok(FullInformation->MaxNameLen >= 8 * sizeof(WCHAR) && FullInformation->MaxNameLen < 100 * sizeof(WCHAR), "MaxNameLen = %lu\n", FullInformation->MaxNameLen);
    ok(FullInformation->MaxClassLen != 0x55555555 && FullInformation->MaxClassLen % sizeof(WCHAR) == 0, "MaxClassLen = %lu\n", FullInformation->MaxClassLen);
    ok(FullInformation->Values != 0x55555555, "Values = %lu\n", FullInformation->Values);
    ok(FullInformation->MaxValueNameLen != 0x55555555 && FullInformation->MaxValueNameLen % sizeof(WCHAR) == 0, "MaxValueNameLen = %lu\n", FullInformation->MaxValueNameLen);
    ok(FullInformation->MaxValueDataLen != 0x55555555, "MaxValueDataLen = %lu\n", FullInformation->MaxValueDataLen);
    ok(FullInformation->Class[0] == 0x5555, "Class[0] = %u\n", FullInformation->Class[0]);

    RtlFillMemory(FullInformation, FullInformationLength, 0x55);
    InfoLength = 0x55555555;
    Status = NtQueryKey(HKLM_Key, KeyFullInformation, FullInformation, FIELD_OFFSET(KEY_FULL_INFORMATION, Class) - 1, &InfoLength);
    ok(Status == STATUS_BUFFER_TOO_SMALL, "Status = 0x%lx\n", Status);
    ok(InfoLength == FIELD_OFFSET(KEY_FULL_INFORMATION, Class), "InfoLength = %lu\n", InfoLength);
    ok(FullInformation->LastWriteTime.QuadPart == 0x5555555555555555, "LastWriteTime changed: %I64d\n", FullInformation->LastWriteTime.QuadPart);

    InitializeObjectAttributes(&ObjectAttributes,
        &Software_Name,
        OBJ_CASE_INSENSITIVE,
        HKLM_Key,
        NULL);
    Status = NtOpenKey(&HKLM_Software_Key, KEY_READ, &ObjectAttributes);
    ok_ntstatus(Status, STATUS_SUCCESS);

    RtlFillMemory(FullInformation, FullInformationLength, 0x55);
    InfoLength = 0x55555555;
    Status = NtQueryKey(HKLM_Software_Key, KeyFullInformation, FullInformation, FIELD_OFFSET(KEY_FULL_INFORMATION, Class), &InfoLength);
    ok(Status == STATUS_SUCCESS, "Status = 0x%lx\n", Status);
    ok(InfoLength == FIELD_OFFSET(KEY_FULL_INFORMATION, Class), "InfoLength = %lu\n", InfoLength);
    ok(FullInformation->LastWriteTime.QuadPart != 0x5555555555555555, "LastWriteTime unchanged\n");
    ok(FullInformation->TitleIndex == 0, "TitleIndex = %lu\n", FullInformation->TitleIndex);
    ok(FullInformation->ClassOffset == 0xffffffff, "ClassOffset = %lu\n", FullInformation->ClassOffset);
    ok(FullInformation->ClassLength == 0, "ClassLength = %lu\n", FullInformation->ClassLength);
    ok(FullInformation->SubKeys >= 5 && FullInformation->SubKeys < 1000, "SubKeys = %lu\n", FullInformation->SubKeys);
    ok(FullInformation->MaxNameLen >= 8 * sizeof(WCHAR), "MaxNameLen = %lu\n", FullInformation->MaxNameLen);
    ok(FullInformation->MaxClassLen != 0x55555555 && FullInformation->MaxClassLen % sizeof(WCHAR) == 0, "MaxClassLen = %lu\n", FullInformation->MaxClassLen);
    ok(FullInformation->Values != 0x55555555, "Values = %lu\n", FullInformation->Values);
    ok(FullInformation->MaxValueNameLen != 0x55555555 && FullInformation->MaxValueNameLen % sizeof(WCHAR) == 0, "MaxValueNameLen = %lu\n", FullInformation->MaxValueNameLen);
    ok(FullInformation->MaxValueDataLen != 0x55555555, "MaxValueDataLen = %lu\n", FullInformation->MaxValueDataLen);
    ok(FullInformation->Class[0] == 0x5555, "Class[0] = %u\n", FullInformation->Class[0]);

    InitializeObjectAttributes(&ObjectAttributes,
        &Test_Name,
        OBJ_CASE_INSENSITIVE,
        HKLM_Software_Key,
        NULL);
    Status = NtCreateKey(&Test_Key, KEY_ALL_ACCESS, &ObjectAttributes, 0, &MyClass, REG_OPTION_VOLATILE, NULL);
    ok_ntstatus(Status, STATUS_SUCCESS);

    InfoLength = 0x55555555;
    Status = NtQueryKey(Test_Key, KeyFullInformation, NULL, 0, &InfoLength);
    ok(Status == STATUS_BUFFER_TOO_SMALL, "Status = 0x%lx\n", Status);
    ok(InfoLength == FIELD_OFFSET(KEY_FULL_INFORMATION, Class) + MyClass.Length, "InfoLength = %lu\n", InfoLength);

    RtlFillMemory(FullInformation, FullInformationLength, 0x55);
    InfoLength = 0x55555555;
    Status = NtQueryKey(Test_Key, KeyFullInformation, FullInformation, FIELD_OFFSET(KEY_FULL_INFORMATION, Class), &InfoLength);
    ok(Status == STATUS_BUFFER_OVERFLOW, "Status = 0x%lx\n", Status);
    ok(InfoLength == FIELD_OFFSET(KEY_FULL_INFORMATION, Class) + MyClass.Length, "InfoLength = %lu\n", InfoLength);
    ok(FullInformation->LastWriteTime.QuadPart != 0x5555555555555555, "LastWriteTime unchanged\n");
    ok(FullInformation->TitleIndex == 0, "TitleIndex = %lu\n", FullInformation->TitleIndex);
    ok(FullInformation->ClassOffset == FIELD_OFFSET(KEY_FULL_INFORMATION, Class), "ClassOffset = %lu\n", FullInformation->ClassOffset);
    ok(FullInformation->ClassLength == MyClass.Length, "ClassLength = %lu\n", FullInformation->ClassLength);
    ok(FullInformation->SubKeys == 0, "SubKeys = %lu\n", FullInformation->SubKeys);
    ok(FullInformation->MaxNameLen == 0, "MaxNameLen = %lu\n", FullInformation->MaxNameLen);
    ok(FullInformation->MaxClassLen == 0, "MaxClassLen = %lu\n", FullInformation->MaxClassLen);
    ok(FullInformation->Values == 0, "Values = %lu\n", FullInformation->Values);
    ok(FullInformation->MaxValueNameLen == 0, "MaxValueNameLen = %lu\n", FullInformation->MaxValueNameLen);
    ok(FullInformation->MaxValueDataLen == 0, "MaxValueDataLen = %lu\n", FullInformation->MaxValueDataLen);
    ok(FullInformation->Class[0] == 0x5555, "Class[0] = %u\n", FullInformation->Class[0]);

    RtlFillMemory(FullInformation, FullInformationLength, 0x55);
    InfoLength = 0x55555555;
    Status = NtQueryKey(Test_Key, KeyFullInformation, FullInformation, FIELD_OFFSET(KEY_FULL_INFORMATION, Class[1]), &InfoLength);
    ok(Status == STATUS_BUFFER_OVERFLOW, "Status = 0x%lx\n", Status);
    ok(InfoLength == FIELD_OFFSET(KEY_FULL_INFORMATION, Class) + MyClass.Length, "InfoLength = %lu\n", InfoLength);
    ok(FullInformation->LastWriteTime.QuadPart != 0x5555555555555555, "LastWriteTime unchanged\n");
    ok(FullInformation->ClassOffset == FIELD_OFFSET(KEY_FULL_INFORMATION, Class), "ClassOffset = %lu\n", FullInformation->ClassOffset);
    ok(FullInformation->ClassLength == MyClass.Length, "ClassLength = %lu\n", FullInformation->ClassLength);
    ok(FullInformation->Class[0] == L'M', "Class[0] = %u\n", FullInformation->Class[0]);
    ok(FullInformation->Class[1] == 0x5555, "Class[1] = %u\n", FullInformation->Class[1]);

    RtlFillMemory(FullInformation, FullInformationLength, 0x55);
    InfoLength = 0x55555555;
    Status = NtQueryKey(Test_Key, KeyFullInformation, FullInformation, FIELD_OFFSET(KEY_FULL_INFORMATION, Class) + MyClass.Length - 1, &InfoLength);
    ok(Status == STATUS_BUFFER_OVERFLOW, "Status = 0x%lx\n", Status);
    ok(InfoLength == FIELD_OFFSET(KEY_FULL_INFORMATION, Class) + MyClass.Length, "InfoLength = %lu\n", InfoLength);
    ok(FullInformation->LastWriteTime.QuadPart != 0x5555555555555555, "LastWriteTime unchanged\n");
    ok(FullInformation->ClassOffset == FIELD_OFFSET(KEY_FULL_INFORMATION, Class), "ClassOffset = %lu\n", FullInformation->ClassOffset);
    ok(FullInformation->ClassLength == MyClass.Length, "ClassLength = %lu\n", FullInformation->ClassLength);
    ok(FullInformation->Class[0] == L'M', "Class[0] = %u\n", FullInformation->Class[0]);
    ok(FullInformation->Class[1] == L'y', "Class[1] = %u\n", FullInformation->Class[1]);
    ok(FullInformation->Class[6] == (L's' | 0x5500), "Class[6] = %u\n", FullInformation->Class[6]);
    ok(FullInformation->Class[7] == 0x5555, "Class[7] = %u\n", FullInformation->Class[7]);

    RtlFillMemory(FullInformation, FullInformationLength, 0x55);
    InfoLength = 0x55555555;
    Status = NtQueryKey(Test_Key, KeyFullInformation, FullInformation, FIELD_OFFSET(KEY_FULL_INFORMATION, Class) + MyClass.Length, &InfoLength);
    ok(Status == STATUS_SUCCESS, "Status = 0x%lx\n", Status);
    ok(InfoLength == FIELD_OFFSET(KEY_FULL_INFORMATION, Class) + MyClass.Length, "InfoLength = %lu\n", InfoLength);
    ok(FullInformation->LastWriteTime.QuadPart != 0x5555555555555555, "LastWriteTime unchanged\n");
    ok(FullInformation->ClassOffset == FIELD_OFFSET(KEY_FULL_INFORMATION, Class), "ClassOffset = %lu\n", FullInformation->ClassOffset);
    ok(FullInformation->ClassLength == MyClass.Length, "ClassLength = %lu\n", FullInformation->ClassLength);
    ok(FullInformation->Class[0] == L'M', "Class[0] = %u\n", FullInformation->Class[0]);
    ok(FullInformation->Class[1] == L'y', "Class[1] = %u\n", FullInformation->Class[1]);
    ok(FullInformation->Class[6] == L's', "Class[6] = %u\n", FullInformation->Class[6]);
    ok(FullInformation->Class[7] == 0x5555, "Class[7] = %u\n", FullInformation->Class[7]);

    RtlFillMemory(FullInformation, FullInformationLength, 0x55);
    InfoLength = 0x55555555;
    Status = NtQueryKey(Test_Key, KeyFullInformation, FullInformation, FIELD_OFFSET(KEY_FULL_INFORMATION, Class) + MyClass.Length + sizeof(UNICODE_NULL), &InfoLength);
    ok(Status == STATUS_SUCCESS, "Status = 0x%lx\n", Status);
    ok(InfoLength == FIELD_OFFSET(KEY_FULL_INFORMATION, Class) + MyClass.Length, "InfoLength = %lu\n", InfoLength);
    ok(FullInformation->LastWriteTime.QuadPart != 0x5555555555555555, "LastWriteTime unchanged\n");
    ok(FullInformation->ClassOffset == FIELD_OFFSET(KEY_FULL_INFORMATION, Class), "ClassOffset = %lu\n", FullInformation->ClassOffset);
    ok(FullInformation->ClassLength == MyClass.Length, "ClassLength = %lu\n", FullInformation->ClassLength);
    ok(FullInformation->Class[0] == L'M', "Class[0] = %u\n", FullInformation->Class[0]);
    ok(FullInformation->Class[1] == L'y', "Class[1] = %u\n", FullInformation->Class[1]);
    ok(FullInformation->Class[6] == L's', "Class[6] = %u\n", FullInformation->Class[6]);
    ok(FullInformation->Class[7] == 0x5555, "Class[7] = %u\n", FullInformation->Class[7]);

    RtlFreeHeap(RtlGetProcessHeap(), 0, FullInformation);

    Status = NtDeleteKey(Test_Key);
    ok_ntstatus(Status, STATUS_SUCCESS);

    NtClose(Test_Key);
    NtClose(HKLM_Software_Key);
    NtClose(HKLM_Key);
}