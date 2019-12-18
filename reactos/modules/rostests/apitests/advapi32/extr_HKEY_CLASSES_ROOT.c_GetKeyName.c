#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  Length; int /*<<< orphan*/  MaximumLength; int /*<<< orphan*/  Buffer; } ;
typedef  TYPE_1__ UNICODE_STRING ;
typedef  scalar_t__ ULONG ;
struct TYPE_8__ {int /*<<< orphan*/  NameLength; int /*<<< orphan*/  Name; } ;
typedef  int /*<<< orphan*/  PUNICODE_STRING ;
typedef  TYPE_2__* PKEY_NAME_INFORMATION ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  HKEY ;

/* Variables and functions */
 int /*<<< orphan*/  KeyNameInformation ; 
 int /*<<< orphan*/  NtQueryKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  RTL_DUPLICATE_UNICODE_STRING_NULL_TERMINATE ; 
 TYPE_2__* RtlAllocateHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  RtlDuplicateUnicodeString (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlFreeHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  RtlGetProcessHeap () ; 
 int /*<<< orphan*/  STATUS_BUFFER_TOO_SMALL ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ok_ntstatus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void
GetKeyName(HKEY hKey, PUNICODE_STRING KeyName)
{
    UNICODE_STRING InfoName;
    PKEY_NAME_INFORMATION NameInformation;
    ULONG InfoLength;
    NTSTATUS Status;

    /* Get info length */
    InfoLength = 0;
    Status = NtQueryKey(hKey, KeyNameInformation, NULL, 0, &InfoLength);
    ok_ntstatus(Status, STATUS_BUFFER_TOO_SMALL);

    /* Get it for real */
    NameInformation = RtlAllocateHeap(RtlGetProcessHeap(), 0, InfoLength);
    ok(NameInformation != NULL, "\n");

    Status = NtQueryKey(hKey, KeyNameInformation, NameInformation, InfoLength, &InfoLength);
    ok_ntstatus(Status, STATUS_SUCCESS);

    InfoName.Buffer = NameInformation->Name;
    InfoName.Length = NameInformation->NameLength;
    InfoName.MaximumLength = InfoName.Length;

    RtlDuplicateUnicodeString(RTL_DUPLICATE_UNICODE_STRING_NULL_TERMINATE, &InfoName, KeyName);

    RtlFreeHeap(RtlGetProcessHeap(), 0, NameInformation);
}