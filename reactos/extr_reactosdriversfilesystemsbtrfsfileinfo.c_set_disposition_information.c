#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_9__ ;
typedef  struct TYPE_32__   TYPE_8__ ;
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;
typedef  struct TYPE_24__   TYPE_13__ ;
typedef  struct TYPE_23__   TYPE_12__ ;
typedef  struct TYPE_22__   TYPE_11__ ;
typedef  struct TYPE_21__   TYPE_10__ ;

/* Type definitions */
struct TYPE_31__ {scalar_t__ fcb; scalar_t__ delete_on_close; TYPE_3__* parent; } ;
typedef  TYPE_7__ file_ref ;
struct TYPE_30__ {int /*<<< orphan*/  Resource; } ;
struct TYPE_28__ {scalar_t__ st_size; } ;
struct TYPE_32__ {int atts; scalar_t__ type; TYPE_6__ Header; TYPE_5__* nonpaged; TYPE_4__ inode_item; scalar_t__ ads; } ;
typedef  TYPE_8__ fcb ;
struct TYPE_33__ {scalar_t__ dummy_fcb; int /*<<< orphan*/  DirNotifyList; int /*<<< orphan*/  NotifySync; } ;
typedef  TYPE_9__ device_extension ;
struct TYPE_21__ {TYPE_7__* fileref; } ;
typedef  TYPE_10__ ccb ;
typedef  int ULONG ;
struct TYPE_29__ {int /*<<< orphan*/  segment_object; } ;
struct TYPE_27__ {TYPE_2__* fcb; } ;
struct TYPE_26__ {int atts; } ;
struct TYPE_25__ {TYPE_13__* SystemBuffer; } ;
struct TYPE_24__ {scalar_t__ DeleteFile; } ;
struct TYPE_23__ {TYPE_8__* FsContext; scalar_t__ DeletePending; TYPE_10__* FsContext2; } ;
struct TYPE_22__ {TYPE_1__ AssociatedIrp; } ;
typedef  TYPE_11__* PIRP ;
typedef  TYPE_12__* PFILE_OBJECT ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_13__ FILE_DISPOSITION_INFORMATION ;

/* Variables and functions */
 scalar_t__ BTRFS_TYPE_DIRECTORY ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  ExAcquireResourceExclusiveLite (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExReleaseResourceLite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int FILE_ATTRIBUTE_READONLY ; 
 int /*<<< orphan*/  FsRtlNotifyFullChangeDirectory (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_8__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MmFlushForDelete ; 
 int /*<<< orphan*/  MmFlushImageSection (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_CANNOT_DELETE ; 
 int /*<<< orphan*/  STATUS_DIRECTORY_NOT_EMPTY ; 
 int /*<<< orphan*/  STATUS_INTERNAL_ERROR ; 
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  acquire_fcb_lock_exclusive (TYPE_9__*) ; 
 int /*<<< orphan*/  file_desc (TYPE_12__*) ; 
 int /*<<< orphan*/  release_fcb_lock (TYPE_9__*) ; 

__attribute__((used)) static NTSTATUS set_disposition_information(device_extension* Vcb, PIRP Irp, PFILE_OBJECT FileObject) {
    FILE_DISPOSITION_INFORMATION* fdi = Irp->AssociatedIrp.SystemBuffer;
    fcb* fcb = FileObject->FsContext;
    ccb* ccb = FileObject->FsContext2;
    file_ref* fileref = ccb ? ccb->fileref : NULL;
    ULONG atts;
    NTSTATUS Status;

    if (!fileref)
        return STATUS_INVALID_PARAMETER;

    acquire_fcb_lock_exclusive(Vcb);

    ExAcquireResourceExclusiveLite(fcb->Header.Resource, TRUE);

    TRACE("changing delete_on_close to %s for %S (fcb %p)\n", fdi->DeleteFile ? "TRUE" : "FALSE", file_desc(FileObject), fcb);

    if (fcb->ads) {
        if (fileref->parent)
            atts = fileref->parent->fcb->atts;
        else {
            ERR("no fileref for stream\n");
            Status = STATUS_INTERNAL_ERROR;
            goto end;
        }
    } else
        atts = fcb->atts;

    TRACE("atts = %x\n", atts);

    if (atts & FILE_ATTRIBUTE_READONLY) {
        TRACE("not allowing readonly file to be deleted\n");
        Status = STATUS_CANNOT_DELETE;
        goto end;
    }

    // FIXME - can we skip this bit for subvols?
    if (fcb->type == BTRFS_TYPE_DIRECTORY && fcb->inode_item.st_size > 0 && (!fileref || fileref->fcb != Vcb->dummy_fcb)) {
        TRACE("directory not empty\n");
        Status = STATUS_DIRECTORY_NOT_EMPTY;
        goto end;
    }

    if (!MmFlushImageSection(&fcb->nonpaged->segment_object, MmFlushForDelete)) {
        TRACE("trying to delete file which is being mapped as an image\n");
        Status = STATUS_CANNOT_DELETE;
        goto end;
    }

    ccb->fileref->delete_on_close = fdi->DeleteFile;

    FileObject->DeletePending = fdi->DeleteFile;

    Status = STATUS_SUCCESS;

end:
    ExReleaseResourceLite(fcb->Header.Resource);

    release_fcb_lock(Vcb);

    // send notification that directory is about to be deleted
    if (NT_SUCCESS(Status) && fdi->DeleteFile && fcb->type == BTRFS_TYPE_DIRECTORY) {
        FsRtlNotifyFullChangeDirectory(Vcb->NotifySync, &Vcb->DirNotifyList, FileObject->FsContext,
                                       NULL, FALSE, FALSE, 0, NULL, NULL, NULL);
    }

    return Status;
}