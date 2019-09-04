#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ ULONG ;
struct TYPE_11__ {scalar_t__ DomainNameFlat; int /*<<< orphan*/  MachineRole; } ;
struct TYPE_8__ {int /*<<< orphan*/  Buffer; scalar_t__ Length; } ;
struct TYPE_9__ {TYPE_1__ DomainName; } ;
struct TYPE_10__ {TYPE_2__ PolicyAccountDomainInfo; } ;
typedef  TYPE_3__* PLSAPR_POLICY_INFORMATION ;
typedef  TYPE_4__* PDSROLER_PRIMARY_DOMAIN_INFO_BASIC ;
typedef  scalar_t__ PDSROLER_PRIMARY_DOMAIN_INFORMATION ;
typedef  int /*<<< orphan*/  ObjectAttributes ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  NET_API_STATUS ;
typedef  int /*<<< orphan*/  LSA_HANDLE ;
typedef  int /*<<< orphan*/  LSAPR_OBJECT_ATTRIBUTES ;
typedef  scalar_t__ LPWSTR ;
typedef  scalar_t__ LPBYTE ;
typedef  int /*<<< orphan*/  DSROLER_PRIMARY_DOMAIN_INFO_BASIC ;

/* Variables and functions */
 int /*<<< orphan*/  DsRole_RoleStandaloneWorkstation ; 
 int /*<<< orphan*/  ERROR_OUTOFMEMORY ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  LsaIFree_LSAPR_POLICY_INFORMATION (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  LsaNtStatusToWinError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LsarClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LsarOpenPolicy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LsarQueryInformationPolicy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__**) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POLICY_VIEW_LOCAL_INFORMATION ; 
 int /*<<< orphan*/  PolicyAccountDomainInformation ; 
 int /*<<< orphan*/  RtlZeroMemory (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 TYPE_4__* midl_user_allocate (scalar_t__) ; 
 int /*<<< orphan*/  wcscpy (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
NET_API_STATUS
DsRolepGetBasicInfo(
    PDSROLER_PRIMARY_DOMAIN_INFORMATION *DomainInfo)
{
    LSAPR_OBJECT_ATTRIBUTES ObjectAttributes;
    PDSROLER_PRIMARY_DOMAIN_INFO_BASIC Buffer;
    PLSAPR_POLICY_INFORMATION PolicyInfo;
    LSA_HANDLE PolicyHandle;
    ULONG Size;
    NTSTATUS Status;

    RtlZeroMemory(&ObjectAttributes, sizeof(ObjectAttributes));
    Status = LsarOpenPolicy(NULL,
                            &ObjectAttributes,
                            POLICY_VIEW_LOCAL_INFORMATION,
                            &PolicyHandle);
    if (!NT_SUCCESS(Status))
    {
        TRACE("LsarOpenPolicyFailed with NT status %x\n",
              LsaNtStatusToWinError(Status));
        return ERROR_OUTOFMEMORY;
    }

    Status = LsarQueryInformationPolicy(PolicyHandle,
                                        PolicyAccountDomainInformation,
                                        &PolicyInfo);
    LsarClose(&PolicyHandle);
    if (!NT_SUCCESS(Status))
    {
        TRACE("LsarQueryInformationPolicy with NT status %x\n",
              LsaNtStatusToWinError(Status));
        return ERROR_OUTOFMEMORY;
    }

    Size = sizeof(DSROLER_PRIMARY_DOMAIN_INFO_BASIC) +
           PolicyInfo->PolicyAccountDomainInfo.DomainName.Length + sizeof(WCHAR);

    Buffer = midl_user_allocate(Size);
    if (Buffer == NULL)
    {
        LsaIFree_LSAPR_POLICY_INFORMATION(PolicyAccountDomainInformation,
                                          PolicyInfo);
        return ERROR_OUTOFMEMORY;
    }

    Buffer->MachineRole = DsRole_RoleStandaloneWorkstation;
    Buffer->DomainNameFlat = (LPWSTR)((LPBYTE)Buffer +
                                      sizeof(DSROLER_PRIMARY_DOMAIN_INFO_BASIC));
    wcscpy(Buffer->DomainNameFlat, PolicyInfo->PolicyAccountDomainInfo.DomainName.Buffer);

    LsaIFree_LSAPR_POLICY_INFORMATION(PolicyAccountDomainInformation,
                                      PolicyInfo);

    *DomainInfo = (PDSROLER_PRIMARY_DOMAIN_INFORMATION)Buffer;

    return ERROR_SUCCESS;
}