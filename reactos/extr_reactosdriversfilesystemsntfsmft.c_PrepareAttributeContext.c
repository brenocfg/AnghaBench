#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG_PTR ;
typedef  int /*<<< orphan*/  ULONGLONG ;
struct TYPE_17__ {int /*<<< orphan*/  AttrCtxtLookasideList; } ;
struct TYPE_13__ {scalar_t__ MappingPairsOffset; } ;
struct TYPE_16__ {TYPE_1__ NonResident; } ;
struct TYPE_15__ {int CacheRunStartLCN; int CacheRunLastLCN; TYPE_4__* pRecord; int /*<<< orphan*/  DataRunsMCB; scalar_t__ CacheRunCurrentOffset; int /*<<< orphan*/  CacheRunLength; int /*<<< orphan*/  CacheRun; scalar_t__ CacheRunOffset; } ;
struct TYPE_14__ {scalar_t__ IsNonResident; int /*<<< orphan*/  Length; } ;
typedef  int /*<<< orphan*/  PUCHAR ;
typedef  TYPE_2__* PNTFS_ATTR_RECORD ;
typedef  TYPE_3__* PNTFS_ATTR_CONTEXT ;
typedef  int LONGLONG ;

/* Variables and functions */
 int /*<<< orphan*/  ConvertDataRunsToLargeMCB (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DPRINT1 (char*) ; 
 int /*<<< orphan*/  DecodeRun (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 TYPE_3__* ExAllocateFromNPagedLookasideList (int /*<<< orphan*/ *) ; 
 TYPE_4__* ExAllocatePoolWithTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExFreePoolWithTag (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExFreeToNPagedLookasideList (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NonPagedPool ; 
 TYPE_8__* NtfsGlobalData ; 
 int /*<<< orphan*/  RtlCopyMemory (TYPE_4__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG_NTFS ; 

PNTFS_ATTR_CONTEXT
PrepareAttributeContext(PNTFS_ATTR_RECORD AttrRecord)
{
    PNTFS_ATTR_CONTEXT Context;

    Context = ExAllocateFromNPagedLookasideList(&NtfsGlobalData->AttrCtxtLookasideList);
    if(!Context)
    {
        DPRINT1("Error: Unable to allocate memory for context!\n");
        return NULL;
    }

    // Allocate memory for a copy of the attribute
    Context->pRecord = ExAllocatePoolWithTag(NonPagedPool, AttrRecord->Length, TAG_NTFS);
    if(!Context->pRecord)
    {
        DPRINT1("Error: Unable to allocate memory for attribute record!\n");
        ExFreeToNPagedLookasideList(&NtfsGlobalData->AttrCtxtLookasideList, Context);
        return NULL;
    }

    // Copy the attribute
    RtlCopyMemory(Context->pRecord, AttrRecord, AttrRecord->Length);

    if (AttrRecord->IsNonResident)
    {
        LONGLONG DataRunOffset;
        ULONGLONG DataRunLength;
        ULONGLONG NextVBN = 0;
        PUCHAR DataRun = (PUCHAR)((ULONG_PTR)Context->pRecord + Context->pRecord->NonResident.MappingPairsOffset);

        Context->CacheRun = DataRun;
        Context->CacheRunOffset = 0;
        Context->CacheRun = DecodeRun(Context->CacheRun, &DataRunOffset, &DataRunLength);
        Context->CacheRunLength = DataRunLength;
        if (DataRunOffset != -1)
        {
            /* Normal run. */
            Context->CacheRunStartLCN =
            Context->CacheRunLastLCN = DataRunOffset;
        }
        else
        {
            /* Sparse run. */
            Context->CacheRunStartLCN = -1;
            Context->CacheRunLastLCN = 0;
        }
        Context->CacheRunCurrentOffset = 0;

        // Convert the data runs to a map control block
        if (!NT_SUCCESS(ConvertDataRunsToLargeMCB(DataRun, &Context->DataRunsMCB, &NextVBN)))
        {
            DPRINT1("Unable to convert data runs to MCB!\n");
            ExFreePoolWithTag(Context->pRecord, TAG_NTFS);
            ExFreeToNPagedLookasideList(&NtfsGlobalData->AttrCtxtLookasideList, Context);
            return NULL;
        }
    }

    return Context;
}