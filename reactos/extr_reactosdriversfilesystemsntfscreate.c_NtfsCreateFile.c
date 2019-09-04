#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_70__   TYPE_9__ ;
typedef  struct TYPE_69__   TYPE_8__ ;
typedef  struct TYPE_68__   TYPE_7__ ;
typedef  struct TYPE_67__   TYPE_6__ ;
typedef  struct TYPE_66__   TYPE_5__ ;
typedef  struct TYPE_65__   TYPE_4__ ;
typedef  struct TYPE_64__   TYPE_45__ ;
typedef  struct TYPE_63__   TYPE_3__ ;
typedef  struct TYPE_62__   TYPE_33__ ;
typedef  struct TYPE_61__   TYPE_2__ ;
typedef  struct TYPE_60__   TYPE_21__ ;
typedef  struct TYPE_59__   TYPE_1__ ;
typedef  struct TYPE_58__   TYPE_17__ ;
typedef  struct TYPE_57__   TYPE_15__ ;
typedef  struct TYPE_56__   TYPE_14__ ;
typedef  struct TYPE_55__   TYPE_13__ ;
typedef  struct TYPE_54__   TYPE_12__ ;
typedef  struct TYPE_53__   TYPE_11__ ;
typedef  struct TYPE_52__   TYPE_10__ ;

/* Type definitions */
struct TYPE_69__ {TYPE_9__* Buffer; } ;
typedef  TYPE_8__ UNICODE_STRING ;
typedef  int ULONGLONG ;
typedef  int ULONG ;
struct TYPE_70__ {scalar_t__ ReparseTag; } ;
struct TYPE_68__ {scalar_t__ Information; } ;
struct TYPE_66__ {scalar_t__ AuxiliaryBuffer; } ;
struct TYPE_67__ {TYPE_5__ Overlay; } ;
struct TYPE_65__ {int Length; TYPE_9__* Buffer; } ;
struct TYPE_64__ {int /*<<< orphan*/  RefCount; } ;
struct TYPE_63__ {int /*<<< orphan*/ * FsContext2; } ;
struct TYPE_62__ {int /*<<< orphan*/  EnableWriteSupport; } ;
struct TYPE_59__ {int Options; } ;
struct TYPE_61__ {TYPE_1__ Create; } ;
struct TYPE_60__ {int /*<<< orphan*/  FileRecLookasideList; } ;
struct TYPE_58__ {scalar_t__ QuadPart; } ;
struct TYPE_57__ {TYPE_13__* DeviceExtension; } ;
struct TYPE_56__ {TYPE_4__ FileName; TYPE_3__* RelatedFileObject; } ;
struct TYPE_55__ {int Flags; int /*<<< orphan*/  OpenHandleCount; TYPE_2__ Parameters; TYPE_45__* VolumeFcb; TYPE_14__* FileObject; } ;
struct TYPE_54__ {TYPE_7__ IoStatus; TYPE_6__ Tail; } ;
struct TYPE_53__ {int /*<<< orphan*/  OpenHandleCount; int /*<<< orphan*/  MainResource; TYPE_21__* Vcb; int /*<<< orphan*/  MFTIndex; } ;
struct TYPE_52__ {int Flags; TYPE_12__* Irp; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int* PULONGLONG ;
typedef  TYPE_9__* PREPARSE_DATA_BUFFER ;
typedef  TYPE_10__* PNTFS_IRP_CONTEXT ;
typedef  TYPE_11__* PNTFS_FCB ;
typedef  int /*<<< orphan*/ * PNTFS_ATTR_CONTEXT ;
typedef  TYPE_12__* PIRP ;
typedef  TYPE_13__* PIO_STACK_LOCATION ;
typedef  int /*<<< orphan*/ * PFILE_RECORD_HEADER ;
typedef  TYPE_14__* PFILE_OBJECT ;
typedef  TYPE_15__* PDEVICE_OBJECT ;
typedef  TYPE_13__* PDEVICE_EXTENSION ;
typedef  scalar_t__ NTSTATUS ;
typedef  TYPE_17__ LARGE_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (TYPE_13__*) ; 
 int /*<<< orphan*/  AttributeData ; 
 int /*<<< orphan*/  AttributeReparsePoint ; 
 int /*<<< orphan*/  BooleanFlagOn (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT1 (char*,...) ; 
 int /*<<< orphan*/  ExAcquireResourceExclusiveLite (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ExAllocateFromNPagedLookasideList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExFreePoolWithTag (TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExFreeToNPagedLookasideList (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExReleaseResourceLite (int /*<<< orphan*/ *) ; 
 int FILE_CREATE ; 
 scalar_t__ FILE_CREATED ; 
 int FILE_DIRECTORY_FILE ; 
 scalar_t__ FILE_EXISTS ; 
 int FILE_NON_DIRECTORY_FILE ; 
 int FILE_OPEN ; 
 void* FILE_OPENED ; 
 int FILE_OPEN_BY_FILE_ID ; 
 int FILE_OPEN_IF ; 
 int FILE_OPEN_REPARSE_POINT ; 
 int FILE_OVERWRITE ; 
 int FILE_OVERWRITE_IF ; 
 scalar_t__ FILE_OVERWRITTEN ; 
 int FILE_SUPERSEDE ; 
 scalar_t__ FILE_SUPERSEDED ; 
 int FILE_VALID_OPTION_FLAGS ; 
 scalar_t__ FindAttribute (TYPE_21__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*) ; 
 scalar_t__ IO_REPARSE_TAG_MOUNT_POINT ; 
 int /*<<< orphan*/  IRPCONTEXT_CANWAIT ; 
 TYPE_13__* IoGetCurrentIrpStackLocation (TYPE_12__*) ; 
 int NTFS_FILE_FIRST_USER_FILE ; 
 int NTFS_MFT_MASK ; 
 scalar_t__ NT_SUCCESS (scalar_t__) ; 
 int /*<<< orphan*/  NtfsAttachFCBToFileObject (TYPE_13__*,TYPE_45__*,TYPE_14__*) ; 
 int /*<<< orphan*/  NtfsCloseFile (TYPE_13__*,TYPE_14__*) ; 
 scalar_t__ NtfsCreateDirectory (TYPE_13__*,TYPE_14__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ NtfsCreateFileRecord (TYPE_13__*,TYPE_14__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ NtfsFCBIsDirectory (TYPE_11__*) ; 
 scalar_t__ NtfsFCBIsReparsePoint (TYPE_11__*) ; 
 TYPE_33__* NtfsGlobalData ; 
 scalar_t__ NtfsMoonWalkID (TYPE_13__*,int,TYPE_8__*) ; 
 scalar_t__ NtfsOpenFile (TYPE_13__*,TYPE_14__*,TYPE_9__*,int /*<<< orphan*/ ,TYPE_11__**) ; 
 scalar_t__ NtfsOpenFileById (TYPE_13__*,TYPE_14__*,int,TYPE_11__**) ; 
 scalar_t__ NtfsReadFCBAttribute (TYPE_13__*,TYPE_11__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ReadFileRecord (TYPE_21__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseAttributeContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SL_CASE_SENSITIVE ; 
 scalar_t__ STATUS_ACCESS_DENIED ; 
 scalar_t__ STATUS_FILE_IS_A_DIRECTORY ; 
 scalar_t__ STATUS_INVALID_PARAMETER ; 
 scalar_t__ STATUS_NOT_A_DIRECTORY ; 
 scalar_t__ STATUS_NOT_IMPLEMENTED ; 
 scalar_t__ STATUS_NO_MEMORY ; 
 scalar_t__ STATUS_OBJECT_NAME_COLLISION ; 
 scalar_t__ STATUS_REPARSE ; 
 scalar_t__ STATUS_SUCCESS ; 
 scalar_t__ SetAttributeDataLength (TYPE_14__*,TYPE_11__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,TYPE_17__*) ; 
 int /*<<< orphan*/  TAG_NTFS ; 
 int /*<<< orphan*/  TRUE ; 
 int VCB_VOLUME_LOCKED ; 

__attribute__((used)) static
NTSTATUS
NtfsCreateFile(PDEVICE_OBJECT DeviceObject,
               PNTFS_IRP_CONTEXT IrpContext)
{
    PDEVICE_EXTENSION DeviceExt;
    PIO_STACK_LOCATION Stack;
    PFILE_OBJECT FileObject;
    ULONG RequestedDisposition;
    ULONG RequestedOptions;
    PNTFS_FCB Fcb = NULL;
//    PWSTR FileName;
    NTSTATUS Status;
    UNICODE_STRING FullPath;
    PIRP Irp = IrpContext->Irp;

    DPRINT1("NtfsCreateFile(%p, %p) called\n", DeviceObject, IrpContext);

    DeviceExt = DeviceObject->DeviceExtension;
    ASSERT(DeviceExt);
    Stack = IoGetCurrentIrpStackLocation(Irp);
    ASSERT(Stack);

    RequestedDisposition = ((Stack->Parameters.Create.Options >> 24) & 0xff);
    RequestedOptions = Stack->Parameters.Create.Options & FILE_VALID_OPTION_FLAGS;
//  PagingFileCreate = (Stack->Flags & SL_OPEN_PAGING_FILE) ? TRUE : FALSE;
    if (RequestedOptions & FILE_DIRECTORY_FILE &&
        RequestedDisposition == FILE_SUPERSEDE)
    {
        return STATUS_INVALID_PARAMETER;
    }

    /* Deny create if the volume is locked */
    if (DeviceExt->Flags & VCB_VOLUME_LOCKED)
    {
        return STATUS_ACCESS_DENIED;
    }

    FileObject = Stack->FileObject;

    if ((RequestedOptions & FILE_OPEN_BY_FILE_ID) == FILE_OPEN_BY_FILE_ID)
    {
        ULONGLONG MFTId;

        if (FileObject->FileName.Length != sizeof(ULONGLONG))
            return STATUS_INVALID_PARAMETER;

        MFTId = (*(PULONGLONG)FileObject->FileName.Buffer) & NTFS_MFT_MASK;
        if (MFTId < NTFS_FILE_FIRST_USER_FILE)
        {
            Status = NtfsOpenFileById(DeviceExt, FileObject, MFTId, &Fcb);
        }
        else
        {
            Status = NtfsMoonWalkID(DeviceExt, MFTId, &FullPath);
        }

        if (!NT_SUCCESS(Status))
        {
            return Status;
        }

        DPRINT1("Open by ID: %I64x -> %wZ\n", (*(PULONGLONG)FileObject->FileName.Buffer) & NTFS_MFT_MASK, &FullPath);
    }

    /* This a open operation for the volume itself */
    if (FileObject->FileName.Length == 0 &&
        (FileObject->RelatedFileObject == NULL || FileObject->RelatedFileObject->FsContext2 != NULL))
    {
        if (RequestedDisposition != FILE_OPEN &&
            RequestedDisposition != FILE_OPEN_IF)
        {
            return STATUS_ACCESS_DENIED;
        }

        if (RequestedOptions & FILE_DIRECTORY_FILE)
        {
            return STATUS_NOT_A_DIRECTORY;
        }

        NtfsAttachFCBToFileObject(DeviceExt, DeviceExt->VolumeFcb, FileObject);
        DeviceExt->VolumeFcb->RefCount++;

        Irp->IoStatus.Information = FILE_OPENED;
        return STATUS_SUCCESS;
    }

    if (Fcb == NULL)
    {
        Status = NtfsOpenFile(DeviceExt,
                              FileObject,
                              ((RequestedOptions & FILE_OPEN_BY_FILE_ID) ? FullPath.Buffer : FileObject->FileName.Buffer),
                              BooleanFlagOn(Stack->Flags, SL_CASE_SENSITIVE),
                              &Fcb);

        if (RequestedOptions & FILE_OPEN_BY_FILE_ID)
        {
            ExFreePoolWithTag(FullPath.Buffer, TAG_NTFS);
        }
    }

    if (NT_SUCCESS(Status))
    {
        if (RequestedDisposition == FILE_CREATE)
        {
            Irp->IoStatus.Information = FILE_EXISTS;
            NtfsCloseFile(DeviceExt, FileObject);
            return STATUS_OBJECT_NAME_COLLISION;
        }

        if (RequestedOptions & FILE_NON_DIRECTORY_FILE &&
            NtfsFCBIsDirectory(Fcb))
        {
            NtfsCloseFile(DeviceExt, FileObject);
            return STATUS_FILE_IS_A_DIRECTORY;
        }

        if (RequestedOptions & FILE_DIRECTORY_FILE &&
            !NtfsFCBIsDirectory(Fcb))
        {
            NtfsCloseFile(DeviceExt, FileObject);
            return STATUS_NOT_A_DIRECTORY;
        }

        /*
         * If it is a reparse point & FILE_OPEN_REPARSE_POINT, then allow opening it
         * as a normal file.
         * Otherwise, attempt to read reparse data and hand them to the Io manager
         * with status reparse to force a reparse.
         */
        if (NtfsFCBIsReparsePoint(Fcb) &&
            ((RequestedOptions & FILE_OPEN_REPARSE_POINT) != FILE_OPEN_REPARSE_POINT))
        {
            PREPARSE_DATA_BUFFER ReparseData = NULL;

            Status = NtfsReadFCBAttribute(DeviceExt, Fcb,
                                          AttributeReparsePoint, L"", 0,
                                          (PVOID *)&Irp->Tail.Overlay.AuxiliaryBuffer);
            if (NT_SUCCESS(Status))
            {
                ReparseData = (PREPARSE_DATA_BUFFER)Irp->Tail.Overlay.AuxiliaryBuffer;
                if (ReparseData->ReparseTag == IO_REPARSE_TAG_MOUNT_POINT)
                {
                    Status = STATUS_REPARSE;
                }
                else
                {
                    Status = STATUS_NOT_IMPLEMENTED;
                    ExFreePoolWithTag(ReparseData, TAG_NTFS);
                }
            }

            Irp->IoStatus.Information = ((Status == STATUS_REPARSE) ? ReparseData->ReparseTag : 0);

            NtfsCloseFile(DeviceExt, FileObject);
            return Status;
        }

        if (RequestedDisposition == FILE_OVERWRITE ||
            RequestedDisposition == FILE_OVERWRITE_IF ||
            RequestedDisposition == FILE_SUPERSEDE)
        {
            PFILE_RECORD_HEADER fileRecord = NULL;
            PNTFS_ATTR_CONTEXT dataContext = NULL;
            ULONG DataAttributeOffset;
            LARGE_INTEGER Zero;
            Zero.QuadPart = 0;

            if (!NtfsGlobalData->EnableWriteSupport)
            {
                DPRINT1("NTFS write-support is EXPERIMENTAL and is disabled by default!\n");
                NtfsCloseFile(DeviceExt, FileObject);
                return STATUS_ACCESS_DENIED;
            }

            // TODO: check for appropriate access
           
            ExAcquireResourceExclusiveLite(&(Fcb->MainResource), TRUE);

            fileRecord = ExAllocateFromNPagedLookasideList(&Fcb->Vcb->FileRecLookasideList);
            if (fileRecord)
            {

                Status = ReadFileRecord(Fcb->Vcb,
                                        Fcb->MFTIndex,
                                        fileRecord);
                if (!NT_SUCCESS(Status))
                    goto DoneOverwriting;

                // find the data attribute and set it's length to 0 (TODO: Handle Alternate Data Streams)
                Status = FindAttribute(Fcb->Vcb, fileRecord, AttributeData, L"", 0, &dataContext, &DataAttributeOffset);
                if (!NT_SUCCESS(Status))
                    goto DoneOverwriting;

                Status = SetAttributeDataLength(FileObject, Fcb, dataContext, DataAttributeOffset, fileRecord, &Zero);
            }
            else
            {
                Status = STATUS_NO_MEMORY;
            }            
           
        DoneOverwriting:
            if (fileRecord)
                ExFreeToNPagedLookasideList(&Fcb->Vcb->FileRecLookasideList, fileRecord);
            if (dataContext)
                ReleaseAttributeContext(dataContext);

            ExReleaseResourceLite(&(Fcb->MainResource));

            if (!NT_SUCCESS(Status))
            {
                NtfsCloseFile(DeviceExt, FileObject);
                return Status;
            }            

            if (RequestedDisposition == FILE_SUPERSEDE)
            {
                Irp->IoStatus.Information = FILE_SUPERSEDED;
            }
            else
            {
                Irp->IoStatus.Information = FILE_OVERWRITTEN;
            }
        }
    }
    else
    {
        /* HUGLY HACK: Can't create new files yet... */
        if (RequestedDisposition == FILE_CREATE ||
            RequestedDisposition == FILE_OPEN_IF ||
            RequestedDisposition == FILE_OVERWRITE_IF ||
            RequestedDisposition == FILE_SUPERSEDE)
        {
            if (!NtfsGlobalData->EnableWriteSupport)
            {
                DPRINT1("NTFS write-support is EXPERIMENTAL and is disabled by default!\n");
                NtfsCloseFile(DeviceExt, FileObject);
                return STATUS_ACCESS_DENIED;
            }

            // Was the user trying to create a directory?
            if (RequestedOptions & FILE_DIRECTORY_FILE)
            {
                // Create the directory on disk
                Status = NtfsCreateDirectory(DeviceExt,
                                             FileObject,
                                             BooleanFlagOn(Stack->Flags, SL_CASE_SENSITIVE),
                                             BooleanFlagOn(IrpContext->Flags, IRPCONTEXT_CANWAIT));
            }
            else
            {
                // Create the file record on disk
                Status = NtfsCreateFileRecord(DeviceExt,
                                              FileObject,
                                              BooleanFlagOn(Stack->Flags, SL_CASE_SENSITIVE),
                                              BooleanFlagOn(IrpContext->Flags, IRPCONTEXT_CANWAIT));
            }

            if (!NT_SUCCESS(Status))
            {
                DPRINT1("ERROR: Couldn't create file record!\n");
                return Status;
            }

            // Before we open the file/directory we just created, we need to change the disposition (upper 8 bits of ULONG)
            // from create to open, since we already created the file
            Stack->Parameters.Create.Options = (ULONG)FILE_OPEN << 24 | RequestedOptions;

            // Now we should be able to open the file using NtfsCreateFile()
            Status = NtfsCreateFile(DeviceObject, IrpContext);
            if (NT_SUCCESS(Status))
            {
                // We need to change Irp->IoStatus.Information to reflect creation
                Irp->IoStatus.Information = FILE_CREATED;
            }
            return Status;
        }
    }

    if (NT_SUCCESS(Status))
    {
        Fcb->OpenHandleCount++;
        DeviceExt->OpenHandleCount++;
    }

    /*
     * If the directory containing the file to open doesn't exist then
     * fail immediately
     */
    Irp->IoStatus.Information = (NT_SUCCESS(Status)) ? FILE_OPENED : 0;

    return Status;
}