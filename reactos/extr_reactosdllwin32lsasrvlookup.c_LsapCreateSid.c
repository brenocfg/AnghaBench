#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WELL_KNOWN_SID ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  size_t ULONG ;
typedef  scalar_t__ UCHAR ;
struct TYPE_11__ {int Length; int MaximumLength; TYPE_3__* Buffer; } ;
struct TYPE_10__ {int Length; int MaximumLength; TYPE_3__* Buffer; } ;
struct TYPE_12__ {struct TYPE_12__* Sid; int /*<<< orphan*/  ListEntry; int /*<<< orphan*/  Use; TYPE_2__ DomainName; TYPE_1__ AccountName; } ;
typedef  int /*<<< orphan*/  SID_NAME_USE ;
typedef  int /*<<< orphan*/  PWSTR ;
typedef  TYPE_3__* PWELL_KNOWN_SID ;
typedef  int /*<<< orphan*/ * PULONG ;
typedef  int /*<<< orphan*/  PSID_IDENTIFIER_AUTHORITY ;
typedef  TYPE_3__* PSID ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 int /*<<< orphan*/  InitializeListHead (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InsertTailList (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* RtlAllocateHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RtlFreeHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  RtlGetProcessHeap () ; 
 int /*<<< orphan*/  RtlInitializeSid (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int RtlLengthRequiredSid (scalar_t__) ; 
 int /*<<< orphan*/ * RtlSubAuthoritySid (TYPE_3__*,size_t) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WellKnownSidListHead ; 
 int /*<<< orphan*/  wcscpy (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int wcslen (int /*<<< orphan*/ ) ; 

BOOLEAN
LsapCreateSid(PSID_IDENTIFIER_AUTHORITY IdentifierAuthority,
              UCHAR SubAuthorityCount,
              PULONG SubAuthorities,
              PWSTR AccountName,
              PWSTR DomainName,
              SID_NAME_USE Use,
              PSID *SidPtr)
{
    PWELL_KNOWN_SID SidEntry;
    PULONG p;
    ULONG i;

    SidEntry = RtlAllocateHeap(RtlGetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(WELL_KNOWN_SID));
    if (SidEntry == NULL)
        return FALSE;

    InitializeListHead(&SidEntry->ListEntry);

    SidEntry->Sid = RtlAllocateHeap(RtlGetProcessHeap(),
                                    0,
                                    RtlLengthRequiredSid(SubAuthorityCount));
    if (SidEntry->Sid == NULL)
    {
        RtlFreeHeap(RtlGetProcessHeap(), 0, SidEntry);
        return FALSE;
    }

    RtlInitializeSid(SidEntry->Sid,
                     IdentifierAuthority,
                     SubAuthorityCount);

    for (i = 0; i < (ULONG)SubAuthorityCount; i++)
    {
        p = RtlSubAuthoritySid(SidEntry->Sid, i);
        *p = SubAuthorities[i];
    }

//    RtlInitUnicodeString(&SidEntry->AccountName,
//                         AccountName);
    SidEntry->AccountName.Length = wcslen(AccountName) * sizeof(WCHAR);
    SidEntry->AccountName.MaximumLength = SidEntry->AccountName.Length + sizeof(WCHAR);
    SidEntry->AccountName.Buffer = RtlAllocateHeap(RtlGetProcessHeap(), 0,
                                                   SidEntry->AccountName.MaximumLength);
    if (SidEntry->AccountName.Buffer == NULL)
    {
        RtlFreeHeap(RtlGetProcessHeap(), 0, SidEntry->Sid);
        RtlFreeHeap(RtlGetProcessHeap(), 0, SidEntry);
        return FALSE;
    }

    wcscpy(SidEntry->AccountName.Buffer,
           AccountName);

//    RtlInitUnicodeString(&SidEntry->DomainName,
//                         DomainName);
    SidEntry->DomainName.Length = wcslen(DomainName) * sizeof(WCHAR);
    SidEntry->DomainName.MaximumLength = SidEntry->DomainName.Length + sizeof(WCHAR);
    SidEntry->DomainName.Buffer = RtlAllocateHeap(RtlGetProcessHeap(), 0,
                                                  SidEntry->DomainName.MaximumLength);
    if (SidEntry->DomainName.Buffer == NULL)
    {
        RtlFreeHeap(RtlGetProcessHeap(), 0, SidEntry->AccountName.Buffer);
        RtlFreeHeap(RtlGetProcessHeap(), 0, SidEntry->Sid);
        RtlFreeHeap(RtlGetProcessHeap(), 0, SidEntry);
        return FALSE;
    }

    wcscpy(SidEntry->DomainName.Buffer,
           DomainName);

    SidEntry->Use = Use;

    InsertTailList(&WellKnownSidListHead,
                   &SidEntry->ListEntry);

    if (SidPtr != NULL)
        *SidPtr = SidEntry->Sid;

    return TRUE;
}