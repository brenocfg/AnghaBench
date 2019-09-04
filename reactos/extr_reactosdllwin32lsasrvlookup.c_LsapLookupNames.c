#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_37__   TYPE_3__ ;
typedef  struct TYPE_36__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_37__ {int Entries; TYPE_1__* Sids; } ;
struct TYPE_36__ {int MaxEntries; int DomainIndex; struct TYPE_36__* Domains; struct TYPE_36__* Buffer; scalar_t__ Flags; int /*<<< orphan*/ * Sid; int /*<<< orphan*/  Use; scalar_t__ Entries; } ;
typedef  TYPE_1__* PRPC_UNICODE_STRING ;
typedef  TYPE_1__* PLSAPR_TRANSLATED_SID_EX2 ;
typedef  TYPE_3__* PLSAPR_TRANSLATED_SIDS_EX2 ;
typedef  TYPE_1__* PLSAPR_REFERENCED_DOMAIN_LIST ;
typedef  scalar_t__ NTSTATUS ;
typedef  int /*<<< orphan*/  LSA_TRUST_INFORMATION ;
typedef  int /*<<< orphan*/  LSAP_LOOKUP_LEVEL ;
typedef  int /*<<< orphan*/  LSAPR_TRANSLATED_SID_EX2 ;
typedef  int /*<<< orphan*/  LSAPR_REFERENCED_DOMAIN_LIST ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ LsapLookupAccountNames (int,TYPE_1__*,TYPE_1__*,TYPE_1__*,TYPE_1__*,int*) ; 
 scalar_t__ LsapLookupBuiltinNames (int,TYPE_1__*,TYPE_1__*,TYPE_1__*,TYPE_1__*,int*) ; 
 scalar_t__ LsapLookupFullyQualifiedWellKnownNames (int,TYPE_1__*,TYPE_1__*,TYPE_1__*,TYPE_1__*,int*) ; 
 scalar_t__ LsapLookupIsolatedAccountNames (int,TYPE_1__*,TYPE_1__*,TYPE_1__*,TYPE_1__*,int*) ; 
 scalar_t__ LsapLookupIsolatedBuiltinNames (int,TYPE_1__*,TYPE_1__*,TYPE_1__*,TYPE_1__*,int*) ; 
 scalar_t__ LsapLookupIsolatedNames (int,TYPE_1__*,TYPE_1__*,TYPE_1__*,TYPE_1__*,int*) ; 
 scalar_t__ LsapSplitNames (int,TYPE_1__*,TYPE_1__**,TYPE_1__**) ; 
 void* MIDL_user_allocate (int) ; 
 int /*<<< orphan*/  MIDL_user_free (TYPE_1__*) ; 
 int /*<<< orphan*/  NT_SUCCESS (scalar_t__) ; 
 scalar_t__ STATUS_INSUFFICIENT_RESOURCES ; 
 scalar_t__ STATUS_NONE_MAPPED ; 
 scalar_t__ STATUS_SOME_NOT_MAPPED ; 
 scalar_t__ STATUS_SUCCESS ; 
 int /*<<< orphan*/  SidTypeUnknown ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 

NTSTATUS
LsapLookupNames(DWORD Count,
                PRPC_UNICODE_STRING Names,
                PLSAPR_REFERENCED_DOMAIN_LIST *ReferencedDomains,
                PLSAPR_TRANSLATED_SIDS_EX2 TranslatedSids,
                LSAP_LOOKUP_LEVEL LookupLevel,
                DWORD *MappedCount,
                DWORD LookupOptions,
                DWORD ClientRevision)
{
    PLSAPR_REFERENCED_DOMAIN_LIST DomainsBuffer = NULL;
    PLSAPR_TRANSLATED_SID_EX2 SidsBuffer = NULL;
    PRPC_UNICODE_STRING DomainNames = NULL;
    PRPC_UNICODE_STRING AccountNames = NULL;
    ULONG SidsBufferLength;
    ULONG i;
    ULONG Mapped = 0;
    NTSTATUS Status = STATUS_SUCCESS;

//TRACE("()\n");

    TranslatedSids->Entries = 0;
    TranslatedSids->Sids = NULL;
    *ReferencedDomains = NULL;

    SidsBufferLength = Count * sizeof(LSAPR_TRANSLATED_SID_EX2);
    SidsBuffer = MIDL_user_allocate(SidsBufferLength);
    if (SidsBuffer == NULL)
    {
//TRACE("\n");
        Status = STATUS_INSUFFICIENT_RESOURCES;
        goto done;
    }

    DomainsBuffer = MIDL_user_allocate(sizeof(LSAPR_REFERENCED_DOMAIN_LIST));
    if (DomainsBuffer == NULL)
    {
//TRACE("\n");
        Status = STATUS_INSUFFICIENT_RESOURCES;
        goto done;
    }

    DomainsBuffer->Domains = MIDL_user_allocate(Count * sizeof(LSA_TRUST_INFORMATION));
    if (DomainsBuffer->Domains == NULL)
    {
//TRACE("\n");
        Status = STATUS_INSUFFICIENT_RESOURCES;
        goto done;
    }
    DomainsBuffer->Entries = 0;
    DomainsBuffer->MaxEntries = Count;

    for (i = 0; i < Count; i++)
    {
        SidsBuffer[i].Use = SidTypeUnknown;
        SidsBuffer[i].Sid = NULL;
        SidsBuffer[i].DomainIndex = -1;
        SidsBuffer[i].Flags = 0;
    }

    Status = LsapSplitNames(Count,
                            Names,
                            &DomainNames,
                            &AccountNames);
    if (!NT_SUCCESS(Status))
    {
        TRACE("LsapSplitNames failed! (Status %lx)\n", Status);
        goto done;
    }


    Status = LsapLookupIsolatedNames(Count,
                                     DomainNames,
                                     AccountNames,
                                     DomainsBuffer,
                                     SidsBuffer,
                                     &Mapped);
    if (!NT_SUCCESS(Status) &&
        Status != STATUS_NONE_MAPPED &&
        Status != STATUS_SOME_NOT_MAPPED)
    {
        TRACE("LsapLookupIsolatedNames failed! (Status %lx)\n", Status);
        goto done;
    }

    if (Mapped == Count)
        goto done;


    Status = LsapLookupIsolatedBuiltinNames(Count,
                                            DomainNames,
                                            AccountNames,
                                            DomainsBuffer,
                                            SidsBuffer,
                                            &Mapped);
    if (!NT_SUCCESS(Status) &&
        Status != STATUS_NONE_MAPPED &&
        Status != STATUS_SOME_NOT_MAPPED)
    {
        TRACE("LsapLookupIsolatedBuiltinNames failed! (Status %lx)\n", Status);
        goto done;
    }

    if (Mapped == Count)
        goto done;


    Status = LsapLookupIsolatedAccountNames(Count,
                                            DomainNames,
                                            AccountNames,
                                            DomainsBuffer,
                                            SidsBuffer,
                                            &Mapped);
    if (!NT_SUCCESS(Status) &&
        Status != STATUS_NONE_MAPPED &&
        Status != STATUS_SOME_NOT_MAPPED)
    {
        TRACE("LsapLookupIsolatedAccountNames failed! (Status %lx)\n", Status);
        goto done;
    }

    if (Mapped == Count)
        goto done;

    Status = LsapLookupFullyQualifiedWellKnownNames(Count,
                                                    DomainNames,
                                                    AccountNames,
                                                    DomainsBuffer,
                                                    SidsBuffer,
                                                    &Mapped);
    if (!NT_SUCCESS(Status) &&
        Status != STATUS_NONE_MAPPED &&
        Status != STATUS_SOME_NOT_MAPPED)
    {
        TRACE("LsapLookupFullyQualifiedWellKnownNames failed! (Status %lx)\n", Status);
        goto done;
    }

    if (Mapped == Count)
        goto done;

    Status = LsapLookupBuiltinNames(Count,
                                    DomainNames,
                                    AccountNames,
                                    DomainsBuffer,
                                    SidsBuffer,
                                    &Mapped);
    if (!NT_SUCCESS(Status) &&
        Status != STATUS_NONE_MAPPED &&
        Status != STATUS_SOME_NOT_MAPPED)
    {
        TRACE("LsapLookupBuiltinNames failed! (Status %lx)\n", Status);
        goto done;
    }

    if (Mapped == Count)
        goto done;


    Status = LsapLookupAccountNames(Count,
                                    DomainNames,
                                    AccountNames,
                                    DomainsBuffer,
                                    SidsBuffer,
                                    &Mapped);
    if (!NT_SUCCESS(Status) &&
        Status != STATUS_NONE_MAPPED &&
        Status != STATUS_SOME_NOT_MAPPED)
    {
        TRACE("LsapLookupAccountNames failed! (Status %lx)\n", Status);
        goto done;
    }

    if (Mapped == Count)
        goto done;

done:
//    TRACE("done: Status %lx\n", Status);

    if (DomainNames != NULL)
    {
//TRACE("Free DomainNames\n");
        for (i = 0; i < Count; i++)
        {
            if (DomainNames[i].Buffer != NULL)
                MIDL_user_free(DomainNames[i].Buffer);
        }

        MIDL_user_free(DomainNames);
    }

    if (AccountNames != NULL)
    {
//TRACE("Free AccountNames\n");
        for (i = 0; i < Count; i++)
        {
//TRACE("i: %lu\n", i);
            if (AccountNames[i].Buffer != NULL)
            {
                MIDL_user_free(AccountNames[i].Buffer);
            }
        }

        MIDL_user_free(AccountNames);
    }

    if (!NT_SUCCESS(Status))
    {
//TRACE("Failure!\n");

//TRACE("Free DomainsBuffer\n");
        if (DomainsBuffer != NULL)
        {
            if (DomainsBuffer->Domains != NULL)
                MIDL_user_free(DomainsBuffer->Domains);

            MIDL_user_free(DomainsBuffer);
        }

//TRACE("Free SidsBuffer\n");
        if (SidsBuffer != NULL)
            MIDL_user_free(SidsBuffer);
    }
    else
    {
//TRACE("Success!\n");

        *ReferencedDomains = DomainsBuffer;
        TranslatedSids->Entries = Count;
        TranslatedSids->Sids = SidsBuffer;
        *MappedCount = Mapped;

        if (Mapped == 0)
            Status = STATUS_NONE_MAPPED;
        else if (Mapped < Count)
            Status = STATUS_SOME_NOT_MAPPED;
    }

//    TRACE("done: Status %lx\n", Status);

    return Status;
}