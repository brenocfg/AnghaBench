#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_9__ ;
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_13__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  file_ref ;
struct TYPE_23__ {int /*<<< orphan*/ * Resource; } ;
struct TYPE_25__ {scalar_t__ type; TYPE_4__* Vcb; TYPE_3__ Header; } ;
typedef  TYPE_5__ fcb ;
struct TYPE_26__ {int /*<<< orphan*/  DirNotifyList; int /*<<< orphan*/  NotifySync; } ;
typedef  TYPE_6__ device_extension ;
struct TYPE_20__ {scalar_t__ Length; scalar_t__ MaximumLength; int /*<<< orphan*/  Buffer; } ;
struct TYPE_27__ {int access; TYPE_13__ filename; int /*<<< orphan*/ * fileref; } ;
typedef  TYPE_7__ ccb ;
typedef  scalar_t__ ULONG ;
typedef  scalar_t__ UINT16 ;
struct TYPE_21__ {int /*<<< orphan*/  CompletionFilter; } ;
struct TYPE_22__ {TYPE_1__ NotifyDirectory; } ;
struct TYPE_29__ {int Flags; TYPE_2__ Parameters; TYPE_10__* FileObject; } ;
struct TYPE_28__ {scalar_t__ RequestorMode; } ;
struct TYPE_24__ {int /*<<< orphan*/  tree_lock; } ;
struct TYPE_19__ {TYPE_7__* FsContext2; TYPE_5__* FsContext; } ;
typedef  int /*<<< orphan*/  PSTRING ;
typedef  TYPE_8__* PIRP ;
typedef  TYPE_9__* PIO_STACK_LOCATION ;
typedef  TYPE_10__* PFILE_OBJECT ;
typedef  scalar_t__ NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_TAG ; 
 scalar_t__ BTRFS_TYPE_DIRECTORY ; 
 int /*<<< orphan*/  ERR (char*,...) ; 
 int /*<<< orphan*/  ExAcquireResourceExclusiveLite (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExAcquireResourceSharedLite (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExAllocatePoolWithTag (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExReleaseResourceLite (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int FILE_LIST_DIRECTORY ; 
 int /*<<< orphan*/  FsRtlNotifyFilterChangeDirectory (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_7__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_8__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_9__* IoGetCurrentIrpStackLocation (TYPE_8__*) ; 
 int /*<<< orphan*/  NT_SUCCESS (scalar_t__) ; 
 int /*<<< orphan*/  PagedPool ; 
 int SL_WATCH_TREE ; 
 scalar_t__ STATUS_ACCESS_DENIED ; 
 scalar_t__ STATUS_BUFFER_OVERFLOW ; 
 scalar_t__ STATUS_INSUFFICIENT_RESOURCES ; 
 scalar_t__ STATUS_INVALID_PARAMETER ; 
 scalar_t__ STATUS_PENDING ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ UserMode ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  file_desc (TYPE_10__*) ; 
 scalar_t__ fileref_get_filename (int /*<<< orphan*/ *,TYPE_13__*,int /*<<< orphan*/ *,scalar_t__*) ; 

__attribute__((used)) static NTSTATUS notify_change_directory(device_extension* Vcb, PIRP Irp) {
    PIO_STACK_LOCATION IrpSp = IoGetCurrentIrpStackLocation(Irp);
    PFILE_OBJECT FileObject = IrpSp->FileObject;
    fcb* fcb = FileObject->FsContext;
    ccb* ccb = FileObject->FsContext2;
    file_ref* fileref = ccb ? ccb->fileref : NULL;
    NTSTATUS Status;

    TRACE("IRP_MN_NOTIFY_CHANGE_DIRECTORY\n");

    if (!ccb) {
        ERR("ccb was NULL\n");
        return STATUS_INVALID_PARAMETER;
    }

    if (!fileref) {
        ERR("no fileref\n");
        return STATUS_INVALID_PARAMETER;
    }

    if (Irp->RequestorMode == UserMode && !(ccb->access & FILE_LIST_DIRECTORY)) {
        WARN("insufficient privileges\n");
        return STATUS_ACCESS_DENIED;
    }

    ExAcquireResourceSharedLite(&fcb->Vcb->tree_lock, TRUE);
    ExAcquireResourceExclusiveLite(fcb->Header.Resource, TRUE);

    if (fcb->type != BTRFS_TYPE_DIRECTORY) {
        Status = STATUS_INVALID_PARAMETER;
        goto end;
    }

    // FIXME - raise exception if FCB marked for deletion?

    TRACE("%S\n", file_desc(FileObject));

    if (ccb->filename.Length == 0) {
        ULONG reqlen;

        ccb->filename.MaximumLength = ccb->filename.Length = 0;

        Status = fileref_get_filename(fileref, &ccb->filename, NULL, &reqlen);
        if (Status == STATUS_BUFFER_OVERFLOW) {
            ccb->filename.Buffer = ExAllocatePoolWithTag(PagedPool, reqlen, ALLOC_TAG);
            if (!ccb->filename.Buffer) {
                ERR("out of memory\n");
                Status = STATUS_INSUFFICIENT_RESOURCES;
                goto end;
            }

            ccb->filename.MaximumLength = (UINT16)reqlen;

            Status = fileref_get_filename(fileref, &ccb->filename, NULL, &reqlen);
            if (!NT_SUCCESS(Status)) {
                ERR("fileref_get_filename returned %08x\n", Status);
                goto end;
            }
        } else {
            ERR("fileref_get_filename returned %08x\n", Status);
            goto end;
        }
    }

    FsRtlNotifyFilterChangeDirectory(Vcb->NotifySync, &Vcb->DirNotifyList, FileObject->FsContext2, (PSTRING)&ccb->filename,
                                     IrpSp->Flags & SL_WATCH_TREE, FALSE, IrpSp->Parameters.NotifyDirectory.CompletionFilter, Irp,
                                     NULL, NULL, NULL);

    Status = STATUS_PENDING;

end:
    ExReleaseResourceLite(fcb->Header.Resource);
    ExReleaseResourceLite(&fcb->Vcb->tree_lock);

    return Status;
}