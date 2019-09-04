#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int WCHAR ;
struct TYPE_6__ {int* Buffer; int Length; int MaximumLength; } ;
typedef  TYPE_1__ UNICODE_STRING ;
typedef  char* ULONG ;
typedef  int* PULONG ;
typedef  int /*<<< orphan*/  OBJECT_ATTRIBUTES ;
typedef  int /*<<< orphan*/  NameBuffer ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT1 (char*,TYPE_1__*,...) ; 
 int /*<<< orphan*/  InitializeObjectAttributes (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlInitUnicodeString (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  STATUS_UNSUCCESSFUL ; 
 int /*<<< orphan*/  SYMBOLIC_LINK_ALL_ACCESS ; 
 int /*<<< orphan*/  ZwClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZwOpenSymbolicLinkObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZwQuerySymbolicLinkObject (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ _wcsicmp (int*,char*) ; 
 scalar_t__ _wcsnicmp (int*,char*,int) ; 
 scalar_t__ iswdigit (int) ; 
 int /*<<< orphan*/  swprintf (int*,char*,char*) ; 

NTSTATUS
xHalpGetDiskNumberFromRDisk(ULONG RDisk, PULONG DiskNumber)
{
    WCHAR NameBuffer[80];
    UNICODE_STRING ArcName;
    UNICODE_STRING LinkName;
    OBJECT_ATTRIBUTES ObjectAttributes;
    HANDLE LinkHandle;
    NTSTATUS Status;

    swprintf(NameBuffer,
        L"\\ArcName\\multi(0)disk(0)rdisk(%lu)",
        RDisk);

    RtlInitUnicodeString(&ArcName, NameBuffer);
    InitializeObjectAttributes(&ObjectAttributes,
        &ArcName,
        0,
        NULL,
        NULL);
    Status = ZwOpenSymbolicLinkObject(&LinkHandle,
        SYMBOLIC_LINK_ALL_ACCESS,
        &ObjectAttributes);
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("ZwOpenSymbolicLinkObject failed for %wZ, status=%lx\n", &ArcName, Status);
        return Status;
    }

    LinkName.Buffer = NameBuffer;
    LinkName.Length = 0;
    LinkName.MaximumLength = sizeof(NameBuffer);
    Status = ZwQuerySymbolicLinkObject(LinkHandle,
        &LinkName,
        NULL);
    ZwClose(LinkHandle);
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("ZwQuerySymbolicLinkObject failed, status=%lx\n", Status);
        return Status;
    }
    if (LinkName.Length < sizeof(L"\\Device\\Harddisk0\\Partition0") - sizeof(WCHAR) ||
        LinkName.Length >= sizeof(NameBuffer))
    {
        return STATUS_UNSUCCESSFUL;
    }

    NameBuffer[LinkName.Length / sizeof(WCHAR)] = 0;
    if (_wcsnicmp(NameBuffer, L"\\Device\\Harddisk", (sizeof(L"\\Device\\Harddisk") - sizeof(WCHAR)) / sizeof(WCHAR)))
    {
        return STATUS_UNSUCCESSFUL;
    }
    LinkName.Buffer += (sizeof(L"\\Device\\Harddisk") - sizeof(WCHAR)) / sizeof(WCHAR);

    if (!iswdigit(*LinkName.Buffer))
    {
        return STATUS_UNSUCCESSFUL;
    }
    *DiskNumber = 0;
    while (iswdigit(*LinkName.Buffer))
    {
        *DiskNumber = *DiskNumber * 10 + *LinkName.Buffer - L'0';
        LinkName.Buffer++;
    }
    if (_wcsicmp(LinkName.Buffer, L"\\Partition0"))
    {
        return STATUS_UNSUCCESSFUL;
    }
    return STATUS_SUCCESS;
}