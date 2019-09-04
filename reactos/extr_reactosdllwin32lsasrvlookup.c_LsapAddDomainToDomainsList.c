#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ULONG ;
struct TYPE_10__ {size_t Entries; TYPE_2__* Domains; } ;
struct TYPE_9__ {int /*<<< orphan*/  MaximumLength; int /*<<< orphan*/  Buffer; int /*<<< orphan*/  Length; } ;
struct TYPE_7__ {int /*<<< orphan*/ * Buffer; int /*<<< orphan*/  MaximumLength; int /*<<< orphan*/  Length; } ;
struct TYPE_8__ {TYPE_1__ Name; int /*<<< orphan*/ * Sid; } ;
typedef  TYPE_3__* PUNICODE_STRING ;
typedef  size_t* PULONG ;
typedef  int /*<<< orphan*/  PSID ;
typedef  TYPE_4__* PLSAPR_REFERENCED_DOMAIN_LIST ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 void* MIDL_user_allocate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIDL_user_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlCopySid (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ RtlEqualSid (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlLengthSid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 

__attribute__((used)) static NTSTATUS
LsapAddDomainToDomainsList(PLSAPR_REFERENCED_DOMAIN_LIST ReferencedDomains,
                           PUNICODE_STRING Name,
                           PSID Sid,
                           PULONG Index)
{
    ULONG i;

    i = 0;
    while (i < ReferencedDomains->Entries &&
           ReferencedDomains->Domains[i].Sid != NULL)
    {
        if (RtlEqualSid(Sid, ReferencedDomains->Domains[i].Sid))
        {
            *Index = i;
            return STATUS_SUCCESS;
        }

        i++;
    }

    ReferencedDomains->Domains[i].Sid = MIDL_user_allocate(RtlLengthSid(Sid));
    if (ReferencedDomains->Domains[i].Sid == NULL)
        return STATUS_INSUFFICIENT_RESOURCES;

    RtlCopySid(RtlLengthSid(Sid), ReferencedDomains->Domains[i].Sid, Sid);

    ReferencedDomains->Domains[i].Name.Length = Name->Length;
    ReferencedDomains->Domains[i].Name.MaximumLength = Name->MaximumLength;
    ReferencedDomains->Domains[i].Name.Buffer = MIDL_user_allocate(Name->MaximumLength);
    if (ReferencedDomains->Domains[i].Name.Buffer == NULL)
    {
        MIDL_user_free(ReferencedDomains->Domains[i].Sid);
        ReferencedDomains->Domains[i].Sid = NULL;
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    RtlCopyMemory(ReferencedDomains->Domains[i].Name.Buffer,
                  Name->Buffer,
                  Name->MaximumLength);

    ReferencedDomains->Entries++;
    *Index = i;

    return STATUS_SUCCESS;
}