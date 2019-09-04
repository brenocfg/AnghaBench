#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_5__ {int /*<<< orphan*/  Sid; } ;
struct TYPE_6__ {TYPE_1__ PolicyAccountDomainInfo; } ;
typedef  int /*<<< orphan*/ * PRPC_SID ;
typedef  TYPE_2__* PLSAPR_POLICY_INFORMATION ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/ * LSAPR_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  LsaIFree_LSAPR_POLICY_INFORMATION (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  LsaIOpenPolicyTrusted (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  LsarClose (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  LsarQueryInformationPolicy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__**) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PolicyAccountDomainInformation ; 
 int /*<<< orphan*/ * RtlAllocateHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlGetProcessHeap () ; 
 int /*<<< orphan*/  RtlLengthSid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
NTSTATUS
GetAccountDomainSid(PRPC_SID *Sid)
{
    LSAPR_HANDLE PolicyHandle = NULL;
    PLSAPR_POLICY_INFORMATION PolicyInfo = NULL;
    ULONG Length = 0;
    NTSTATUS Status;

    Status = LsaIOpenPolicyTrusted(&PolicyHandle);
    if (!NT_SUCCESS(Status))
    {
        TRACE("LsaIOpenPolicyTrusted() failed (Status 0x%08lx)\n", Status);
        return Status;
    }

    Status = LsarQueryInformationPolicy(PolicyHandle,
                                        PolicyAccountDomainInformation,
                                        &PolicyInfo);
    if (!NT_SUCCESS(Status))
    {
        TRACE("LsarQueryInformationPolicy() failed (Status 0x%08lx)\n", Status);
        goto done;
    }

    Length = RtlLengthSid(PolicyInfo->PolicyAccountDomainInfo.Sid);

    *Sid = RtlAllocateHeap(RtlGetProcessHeap(), 0, Length);
    if (*Sid == NULL)
    {
        ERR("Failed to allocate SID\n");
        Status = STATUS_INSUFFICIENT_RESOURCES;
        goto done;
    }

    memcpy(*Sid, PolicyInfo->PolicyAccountDomainInfo.Sid, Length);

done:
    if (PolicyInfo != NULL)
        LsaIFree_LSAPR_POLICY_INFORMATION(PolicyAccountDomainInformation,
                                          PolicyInfo);

    if (PolicyHandle != NULL)
        LsarClose(&PolicyHandle);

    return Status;
}