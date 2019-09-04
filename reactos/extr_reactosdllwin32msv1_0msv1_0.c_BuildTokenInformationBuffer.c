#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_17__ ;
typedef  struct TYPE_22__   TYPE_16__ ;
typedef  struct TYPE_21__   TYPE_15__ ;

/* Type definitions */
typedef  size_t ULONG ;
struct TYPE_28__ {TYPE_7__* DefaultDacl; } ;
struct TYPE_23__ {TYPE_7__* PrimaryGroup; } ;
struct TYPE_27__ {TYPE_7__* Sid; } ;
struct TYPE_22__ {TYPE_4__ User; } ;
struct TYPE_24__ {int /*<<< orphan*/  HighPart; int /*<<< orphan*/  LowPart; } ;
struct TYPE_30__ {size_t GroupCount; TYPE_5__ DefaultDacl; TYPE_17__ PrimaryGroup; struct TYPE_30__* Groups; struct TYPE_30__* Sid; TYPE_16__ User; TYPE_1__ ExpirationTime; } ;
struct TYPE_25__ {int /*<<< orphan*/  HighPart; int /*<<< orphan*/  LowPart; } ;
struct TYPE_26__ {int /*<<< orphan*/  UserId; int /*<<< orphan*/  PrimaryGroupId; TYPE_2__ AccountExpires; } ;
struct TYPE_29__ {TYPE_3__ All; } ;
struct TYPE_21__ {int /*<<< orphan*/  (* FreeLsaHeap ) (TYPE_7__*) ;TYPE_7__* (* AllocateLsaHeap ) (int) ;} ;
typedef  int /*<<< orphan*/  PSID ;
typedef  TYPE_6__* PSAMPR_USER_INFO_BUFFER ;
typedef  scalar_t__ PRPC_SID ;
typedef  TYPE_7__* PLSA_TOKEN_INFORMATION_V1 ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  LSA_TOKEN_INFORMATION_V1 ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BuildTokenGroups (TYPE_7__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BuildTokenPrimaryGroup (TYPE_17__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BuildTokenUser (TYPE_16__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_15__ DispatchTable ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 TYPE_7__* stub1 (int) ; 
 int /*<<< orphan*/  stub2 (TYPE_7__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_7__*) ; 
 int /*<<< orphan*/  stub4 (TYPE_7__*) ; 
 int /*<<< orphan*/  stub5 (TYPE_7__*) ; 
 int /*<<< orphan*/  stub6 (TYPE_7__*) ; 
 int /*<<< orphan*/  stub7 (TYPE_7__*) ; 

__attribute__((used)) static
NTSTATUS
BuildTokenInformationBuffer(PLSA_TOKEN_INFORMATION_V1 *TokenInformation,
                            PRPC_SID AccountDomainSid,
                            PSAMPR_USER_INFO_BUFFER UserInfo,
                            BOOL SpecialAccount)
{
    PLSA_TOKEN_INFORMATION_V1 Buffer = NULL;
    ULONG i;
    NTSTATUS Status = STATUS_SUCCESS;

    Buffer = DispatchTable.AllocateLsaHeap(sizeof(LSA_TOKEN_INFORMATION_V1));
    if (Buffer == NULL)
    {
        WARN("Failed to allocate the local buffer!\n");
        Status = STATUS_INSUFFICIENT_RESOURCES;
        goto done;
    }

    Buffer->ExpirationTime.LowPart = UserInfo->All.AccountExpires.LowPart;
    Buffer->ExpirationTime.HighPart = UserInfo->All.AccountExpires.HighPart;

    Status = BuildTokenUser(&Buffer->User,
                            (PSID)AccountDomainSid,
                            UserInfo->All.UserId);
    if (!NT_SUCCESS(Status))
    {
        WARN("BuildTokenUser() failed (Status 0x%08lx)\n", Status);
        goto done;
    }

    Status = BuildTokenPrimaryGroup(&Buffer->PrimaryGroup,
                                    (PSID)AccountDomainSid,
                                    UserInfo->All.PrimaryGroupId);
    if (!NT_SUCCESS(Status))
    {
        WARN("BuildTokenPrimaryGroup() failed (Status 0x%08lx)\n", Status);
        goto done;
    }

    Status = BuildTokenGroups(&Buffer->Groups,
                              (PSID)AccountDomainSid,
                              UserInfo->All.UserId,
                              SpecialAccount);
    if (!NT_SUCCESS(Status))
    {
        WARN("BuildTokenGroups() failed (Status 0x%08lx)\n", Status);
        goto done;
    }

    *TokenInformation = Buffer;

done:
    if (!NT_SUCCESS(Status))
    {
        if (Buffer != NULL)
        {
            if (Buffer->User.User.Sid != NULL)
                DispatchTable.FreeLsaHeap(Buffer->User.User.Sid);

            if (Buffer->Groups != NULL)
            {
                for (i = 0; i < Buffer->Groups->GroupCount; i++)
                {
                    if (Buffer->Groups->Groups[i].Sid != NULL)
                        DispatchTable.FreeLsaHeap(Buffer->Groups->Groups[i].Sid);
                }

                DispatchTable.FreeLsaHeap(Buffer->Groups);
            }

            if (Buffer->PrimaryGroup.PrimaryGroup != NULL)
                DispatchTable.FreeLsaHeap(Buffer->PrimaryGroup.PrimaryGroup);

            if (Buffer->DefaultDacl.DefaultDacl != NULL)
                DispatchTable.FreeLsaHeap(Buffer->DefaultDacl.DefaultDacl);

            DispatchTable.FreeLsaHeap(Buffer);
        }
    }

    return Status;
}