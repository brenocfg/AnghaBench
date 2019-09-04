#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VFATFCB ;
struct TYPE_19__ {int /*<<< orphan*/  IsFastIoPossible; int /*<<< orphan*/ * Resource; int /*<<< orphan*/ * PagingIoResource; } ;
struct TYPE_18__ {TYPE_7__* self; } ;
struct TYPE_17__ {TYPE_7__* self; int /*<<< orphan*/  Hash; } ;
struct TYPE_15__ {int /*<<< orphan*/  Attrib; } ;
struct TYPE_14__ {int /*<<< orphan*/  Attrib; } ;
struct TYPE_16__ {TYPE_2__ Fat; TYPE_1__ FatX; } ;
struct TYPE_20__ {int /*<<< orphan*/  ParentListHead; TYPE_6__ RFCB; int /*<<< orphan*/  MainResource; int /*<<< orphan*/  PagingIoResource; int /*<<< orphan*/  LastMutex; int /*<<< orphan*/  FileLock; TYPE_5__ ShortHash; TYPE_4__ Hash; int /*<<< orphan*/  PathNameU; TYPE_3__ entry; int /*<<< orphan*/ * Attributes; } ;
struct TYPE_13__ {int /*<<< orphan*/  FcbLookasideList; } ;
typedef  TYPE_7__* PVFATFCB ;
typedef  int /*<<< orphan*/  PUNICODE_STRING ;
typedef  int /*<<< orphan*/  PDEVICE_EXTENSION ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,int /*<<< orphan*/ ) ; 
 TYPE_7__* ExAllocateFromNPagedLookasideList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExInitializeFastMutex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExInitializeResourceLite (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FastIoIsNotPossible ; 
 int /*<<< orphan*/  FsRtlInitializeFileLock (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InitializeListHead (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_7__*,int) ; 
 TYPE_10__* VfatGlobalData ; 
 int /*<<< orphan*/  vfatInitFcb (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfatNameHash (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ vfatVolumeIsFatX (int /*<<< orphan*/ ) ; 

PVFATFCB
vfatNewFCB(
    PDEVICE_EXTENSION pVCB,
    PUNICODE_STRING pFileNameU)
{
    PVFATFCB  rcFCB;

    DPRINT("'%wZ'\n", pFileNameU);

    rcFCB = ExAllocateFromNPagedLookasideList(&VfatGlobalData->FcbLookasideList);
    if (rcFCB == NULL)
    {
        return NULL;
    }
    RtlZeroMemory(rcFCB, sizeof(VFATFCB));
    vfatInitFcb(rcFCB, pFileNameU);
    if (vfatVolumeIsFatX(pVCB))
        rcFCB->Attributes = &rcFCB->entry.FatX.Attrib;
    else
        rcFCB->Attributes = &rcFCB->entry.Fat.Attrib;
    rcFCB->Hash.Hash = vfatNameHash(0, &rcFCB->PathNameU);
    rcFCB->Hash.self = rcFCB;
    rcFCB->ShortHash.self = rcFCB;
    ExInitializeResourceLite(&rcFCB->PagingIoResource);
    ExInitializeResourceLite(&rcFCB->MainResource);
    FsRtlInitializeFileLock(&rcFCB->FileLock, NULL, NULL);
    ExInitializeFastMutex(&rcFCB->LastMutex);
    rcFCB->RFCB.PagingIoResource = &rcFCB->PagingIoResource;
    rcFCB->RFCB.Resource = &rcFCB->MainResource;
    rcFCB->RFCB.IsFastIoPossible = FastIoIsNotPossible;
    InitializeListHead(&rcFCB->ParentListHead);

    return  rcFCB;
}