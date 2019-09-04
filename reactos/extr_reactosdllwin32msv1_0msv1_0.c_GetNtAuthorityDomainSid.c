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
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_3__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ SID_IDENTIFIER_AUTHORITY ;
typedef  int /*<<< orphan*/ * PRPC_SID ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/ * RtlAllocateHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlGetProcessHeap () ; 
 int /*<<< orphan*/  RtlInitializeSid (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlLengthRequiredSid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SECURITY_NT_AUTHORITY ; 
 int /*<<< orphan*/  STATUS_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 

__attribute__((used)) static
NTSTATUS
GetNtAuthorityDomainSid(PRPC_SID *Sid)
{
    SID_IDENTIFIER_AUTHORITY NtAuthority = {SECURITY_NT_AUTHORITY};
    ULONG Length = 0;

    Length = RtlLengthRequiredSid(0);
    *Sid = RtlAllocateHeap(RtlGetProcessHeap(), 0, Length);
    if (*Sid == NULL)
    {
        ERR("Failed to allocate SID\n");
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    RtlInitializeSid(*Sid,&NtAuthority, 0);

    return STATUS_SUCCESS;
}