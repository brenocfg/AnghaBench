#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_8__ ;
typedef  struct TYPE_34__   TYPE_7__ ;
typedef  struct TYPE_33__   TYPE_6__ ;
typedef  struct TYPE_32__   TYPE_5__ ;
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_26__ ;
typedef  struct TYPE_27__   TYPE_1__ ;

/* Type definitions */
struct TYPE_35__ {int /*<<< orphan*/  OpenHandleCount; int /*<<< orphan*/  NotifyList; int /*<<< orphan*/  NotifySync; } ;
struct TYPE_34__ {int /*<<< orphan*/  Flags; TYPE_6__* FsContext2; scalar_t__ FsContext; } ;
struct TYPE_33__ {int /*<<< orphan*/  Flags; } ;
struct TYPE_28__ {scalar_t__ QuadPart; } ;
struct TYPE_29__ {scalar_t__ QuadPart; } ;
struct TYPE_27__ {scalar_t__ QuadPart; } ;
struct TYPE_30__ {TYPE_26__ FileSize; TYPE_2__ AllocationSize; TYPE_1__ ValidDataLength; } ;
struct TYPE_32__ {scalar_t__ OpenHandleCount; int /*<<< orphan*/  MainResource; int /*<<< orphan*/  PagingIoResource; int /*<<< orphan*/  FCBShareAccess; int /*<<< orphan*/  Flags; TYPE_3__ RFCB; TYPE_7__* FileObject; int /*<<< orphan*/  FileLock; } ;
struct TYPE_31__ {int /*<<< orphan*/  Irp; TYPE_8__* DeviceExt; TYPE_7__* FileObject; } ;
typedef  TYPE_4__* PVFAT_IRP_CONTEXT ;
typedef  TYPE_5__* PVFATFCB ;
typedef  TYPE_6__* PVFATCCB ;
typedef  TYPE_7__* PFILE_OBJECT ;
typedef  TYPE_8__* PDEVICE_EXTENSION ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 scalar_t__ BooleanFlagOn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CCB_DELETE_ON_CLOSE ; 
 int /*<<< orphan*/  CcUninitializeCacheMap (TYPE_7__*,TYPE_26__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ClearFlag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT (char*,TYPE_8__*,TYPE_7__*) ; 
 int /*<<< orphan*/  ExAcquireResourceExclusiveLite (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExReleaseResourceLite (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FCB_CACHE_INITIALIZED ; 
 int /*<<< orphan*/  FCB_DELETE_PENDING ; 
 int /*<<< orphan*/  FCB_IS_DIRTY ; 
 int /*<<< orphan*/  FCB_IS_VOLUME ; 
 int /*<<< orphan*/  FILE_ACTION_REMOVED ; 
 int /*<<< orphan*/  FILE_NOTIFY_CHANGE_DIR_NAME ; 
 int /*<<< orphan*/  FILE_NOTIFY_CHANGE_FILE_NAME ; 
 int /*<<< orphan*/  FO_CLEANUP_COMPLETE ; 
 scalar_t__ FsRtlAreThereCurrentFileLocks (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FsRtlFastUnlockAll (int /*<<< orphan*/ *,TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FsRtlNotifyCleanup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_6__*) ; 
 int /*<<< orphan*/  IoGetRequestorProcess (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IoRemoveShareAccess (TYPE_7__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ObDereferenceObject (TYPE_7__*) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VfatDelEntry (TYPE_8__*,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VfatIsDirectoryEmpty (TYPE_8__*,TYPE_5__*) ; 
 int /*<<< orphan*/  VfatUpdateEntry (TYPE_8__*,TYPE_5__*) ; 
 scalar_t__ vfatFCBIsDirectory (TYPE_5__*) ; 
 int /*<<< orphan*/  vfatReportChange (TYPE_8__*,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
NTSTATUS
VfatCleanupFile(
    PVFAT_IRP_CONTEXT IrpContext)
{
    PVFATFCB pFcb;
    PVFATCCB pCcb;
    BOOLEAN IsVolume;
    PDEVICE_EXTENSION DeviceExt = IrpContext->DeviceExt;
    PFILE_OBJECT FileObject = IrpContext->FileObject;

    DPRINT("VfatCleanupFile(DeviceExt %p, FileObject %p)\n",
           IrpContext->DeviceExt, FileObject);

    /* FIXME: handle file/directory deletion here */
    pFcb = (PVFATFCB)FileObject->FsContext;
    if (!pFcb)
        return STATUS_SUCCESS;

    IsVolume = BooleanFlagOn(pFcb->Flags, FCB_IS_VOLUME);
    if (IsVolume)
    {
        pFcb->OpenHandleCount--;
        DeviceExt->OpenHandleCount--;

        if (pFcb->OpenHandleCount != 0)
        {
            IoRemoveShareAccess(FileObject, &pFcb->FCBShareAccess);
        }
    }
    else
    {
        ExAcquireResourceExclusiveLite(&pFcb->MainResource, TRUE);
        ExAcquireResourceExclusiveLite(&pFcb->PagingIoResource, TRUE);

        pCcb = FileObject->FsContext2;
        if (BooleanFlagOn(pCcb->Flags, CCB_DELETE_ON_CLOSE))
        {
            pFcb->Flags |= FCB_DELETE_PENDING;
        }

        /* Notify about the cleanup */
        FsRtlNotifyCleanup(IrpContext->DeviceExt->NotifySync,
                           &(IrpContext->DeviceExt->NotifyList),
                           FileObject->FsContext2);

        pFcb->OpenHandleCount--;
        DeviceExt->OpenHandleCount--;

        if (!vfatFCBIsDirectory(pFcb) &&
            FsRtlAreThereCurrentFileLocks(&pFcb->FileLock))
        {
            /* remove all locks this process have on this file */
            FsRtlFastUnlockAll(&pFcb->FileLock,
                               FileObject,
                               IoGetRequestorProcess(IrpContext->Irp),
                               NULL);
        }

        if (BooleanFlagOn(pFcb->Flags, FCB_IS_DIRTY))
        {
            VfatUpdateEntry (DeviceExt, pFcb);
        }

        if (BooleanFlagOn(pFcb->Flags, FCB_DELETE_PENDING) &&
            pFcb->OpenHandleCount == 0)
        {
            if (vfatFCBIsDirectory(pFcb) &&
                !VfatIsDirectoryEmpty(DeviceExt, pFcb))
            {
                pFcb->Flags &= ~FCB_DELETE_PENDING;
            }
            else
            {
                PFILE_OBJECT tmpFileObject;
                tmpFileObject = pFcb->FileObject;
                if (tmpFileObject != NULL)
                {
                    pFcb->FileObject = NULL;
                    CcUninitializeCacheMap(tmpFileObject, NULL, NULL);
                    ClearFlag(pFcb->Flags, FCB_CACHE_INITIALIZED);
                    ObDereferenceObject(tmpFileObject);
                }

                pFcb->RFCB.ValidDataLength.QuadPart = 0;
                pFcb->RFCB.FileSize.QuadPart = 0;
                pFcb->RFCB.AllocationSize.QuadPart = 0;
            }
        }

        /* Uninitialize the cache (should be done even if caching was never initialized) */
        CcUninitializeCacheMap(FileObject, &pFcb->RFCB.FileSize, NULL);

        if (BooleanFlagOn(pFcb->Flags, FCB_DELETE_PENDING) &&
            pFcb->OpenHandleCount == 0)
        {
            VfatDelEntry(DeviceExt, pFcb, NULL);

            vfatReportChange(DeviceExt,
                             pFcb,
                             (vfatFCBIsDirectory(pFcb) ?
                              FILE_NOTIFY_CHANGE_DIR_NAME : FILE_NOTIFY_CHANGE_FILE_NAME),
                             FILE_ACTION_REMOVED);
        }

        if (pFcb->OpenHandleCount != 0)
        {
            IoRemoveShareAccess(FileObject, &pFcb->FCBShareAccess);
        }
/* FIXME: causes FS corruption and breaks selfhosting/testbots and so on */
#if 0
        /* If that's the last open handle we just closed, try to see whether
         * we can delay close operation
         */
        else if (!BooleanFlagOn(pFcb->Flags, FCB_DELETE_PENDING) && !BooleanFlagOn(pFcb->Flags, FCB_IS_PAGE_FILE) &&
                 !BooleanFlagOn(pFcb->Flags, FCB_IS_FAT) && !BooleanFlagOn(pFcb->Flags, FCB_IS_VOLUME))
        {
            /* This is only allowed if that's a directory with no open files
             * OR if it's a file with no section opened
             */
            if ((vfatFCBIsDirectory(pFcb) && IsListEmpty(&pFcb->ParentListHead)) ||
                (!vfatFCBIsDirectory(pFcb) && FileObject->SectionObjectPointer->DataSectionObject == NULL &&
                 FileObject->SectionObjectPointer->ImageSectionObject == NULL))
            {
                DPRINT("Delaying close of: %wZ\n", &pFcb->PathNameU);
                SetFlag(pFcb->Flags, FCB_DELAYED_CLOSE);
            }
        }
#endif

        FileObject->Flags |= FO_CLEANUP_COMPLETE;
#ifdef KDBG
        pFcb->Flags |= FCB_CLEANED_UP;
#endif

        ExReleaseResourceLite(&pFcb->PagingIoResource);
        ExReleaseResourceLite(&pFcb->MainResource);
    }

#ifdef ENABLE_SWAPOUT
    if (IsVolume && BooleanFlagOn(DeviceExt->Flags, VCB_DISMOUNT_PENDING))
    {
        VfatCheckForDismount(DeviceExt, TRUE);
    }
#endif

    return STATUS_SUCCESS;
}