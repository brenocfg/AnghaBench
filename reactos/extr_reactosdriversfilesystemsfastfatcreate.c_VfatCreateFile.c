#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_80__   TYPE_9__ ;
typedef  struct TYPE_79__   TYPE_8__ ;
typedef  struct TYPE_78__   TYPE_7__ ;
typedef  struct TYPE_77__   TYPE_6__ ;
typedef  struct TYPE_76__   TYPE_61__ ;
typedef  struct TYPE_75__   TYPE_5__ ;
typedef  struct TYPE_74__   TYPE_4__ ;
typedef  struct TYPE_73__   TYPE_3__ ;
typedef  struct TYPE_72__   TYPE_2__ ;
typedef  struct TYPE_71__   TYPE_1__ ;
typedef  struct TYPE_70__   TYPE_18__ ;
typedef  struct TYPE_69__   TYPE_17__ ;
typedef  struct TYPE_68__   TYPE_16__ ;
typedef  struct TYPE_67__   TYPE_15__ ;
typedef  struct TYPE_66__   TYPE_14__ ;
typedef  struct TYPE_65__   TYPE_13__ ;
typedef  struct TYPE_64__   TYPE_12__ ;
typedef  struct TYPE_63__   TYPE_11__ ;
typedef  struct TYPE_62__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_63__ {int Length; int* Buffer; } ;
typedef  TYPE_11__ UNICODE_STRING ;
typedef  int ULONG ;
struct TYPE_79__ {int Options; int FileAttributes; int /*<<< orphan*/  ShareAccess; TYPE_7__* SecurityContext; int /*<<< orphan*/  EaLength; } ;
struct TYPE_80__ {TYPE_8__ Create; } ;
struct TYPE_78__ {int DesiredAccess; } ;
struct TYPE_77__ {int /*<<< orphan*/  AllocationSize; } ;
struct TYPE_76__ {int /*<<< orphan*/  FailedCreates; int /*<<< orphan*/  SuccessfulCreates; int /*<<< orphan*/  CreateHits; } ;
struct TYPE_74__ {int /*<<< orphan*/  UpdateTime; int /*<<< orphan*/  UpdateDate; } ;
struct TYPE_73__ {int /*<<< orphan*/  UpdateTime; int /*<<< orphan*/  UpdateDate; } ;
struct TYPE_75__ {TYPE_4__ Fat; TYPE_3__ FatX; } ;
struct TYPE_72__ {int /*<<< orphan*/  SystemBuffer; } ;
struct TYPE_71__ {scalar_t__ FsContext; int /*<<< orphan*/ * FsContext2; } ;
struct TYPE_70__ {int Flags; scalar_t__ VolumeFcb; int /*<<< orphan*/  OpenHandleCount; } ;
struct TYPE_69__ {TYPE_18__* DeviceExtension; } ;
struct TYPE_68__ {TYPE_13__* FsContext2; TYPE_12__* FsContext; TYPE_1__* RelatedFileObject; TYPE_11__ FileName; } ;
struct TYPE_67__ {int Flags; TYPE_9__ Parameters; TYPE_16__* FileObject; } ;
struct TYPE_62__ {scalar_t__ Information; } ;
struct TYPE_66__ {TYPE_10__ IoStatus; TYPE_6__ Overlay; TYPE_2__ AssociatedIrp; } ;
struct TYPE_65__ {int /*<<< orphan*/  Flags; } ;
struct TYPE_64__ {scalar_t__ OpenHandleCount; int Flags; int RefCount; int* Attributes; int /*<<< orphan*/  FCBShareAccess; int /*<<< orphan*/  MainResource; TYPE_5__ entry; int /*<<< orphan*/  PathNameU; int /*<<< orphan*/  SectionObjectPointers; } ;
typedef  int* PWCHAR ;
typedef  TYPE_12__* PVFATFCB ;
typedef  TYPE_13__* PVFATCCB ;
typedef  TYPE_14__* PIRP ;
typedef  TYPE_15__* PIO_STACK_LOCATION ;
typedef  TYPE_16__* PFILE_OBJECT ;
typedef  TYPE_17__* PDEVICE_OBJECT ;
typedef  TYPE_18__* PDEVICE_EXTENSION ;
typedef  scalar_t__ NTSTATUS ;
typedef  size_t LONG ;
typedef  int /*<<< orphan*/  LARGE_INTEGER ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ BooleanFlagOn (int,int) ; 
 int /*<<< orphan*/  CCB_DELETE_ON_CLOSE ; 
 int /*<<< orphan*/  DPRINT (char*) ; 
 int /*<<< orphan*/  DPRINT1 (char*,...) ; 
 int /*<<< orphan*/  ExAcquireResourceExclusiveLite (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ExReleaseResourceLite (int /*<<< orphan*/ *) ; 
 scalar_t__ FALSE ; 
 int FCB_IS_PAGE_FILE ; 
 int /*<<< orphan*/  FILE_ACTION_ADDED ; 
 int /*<<< orphan*/  FILE_ACTION_MODIFIED ; 
 int FILE_ATTRIBUTE_ARCHIVE ; 
 int FILE_ATTRIBUTE_DIRECTORY ; 
 int FILE_ATTRIBUTE_HIDDEN ; 
 int FILE_ATTRIBUTE_READONLY ; 
 int FILE_ATTRIBUTE_SYSTEM ; 
 int FILE_CREATE ; 
 scalar_t__ FILE_CREATED ; 
 int FILE_DELETE_ON_CLOSE ; 
 int FILE_DIRECTORY_FILE ; 
 scalar_t__ FILE_DOES_NOT_EXIST ; 
 void* FILE_EXISTS ; 
 int FILE_NON_DIRECTORY_FILE ; 
 int FILE_NOTIFY_CHANGE_ATTRIBUTES ; 
 int FILE_NOTIFY_CHANGE_DIR_NAME ; 
 int FILE_NOTIFY_CHANGE_FILE_NAME ; 
 int FILE_NOTIFY_CHANGE_LAST_WRITE ; 
 int FILE_NOTIFY_CHANGE_SIZE ; 
 int FILE_OPEN ; 
 void* FILE_OPENED ; 
 int FILE_OPEN_BY_FILE_ID ; 
 int FILE_OPEN_IF ; 
 int FILE_OVERWRITE ; 
 int FILE_OVERWRITE_IF ; 
 scalar_t__ FILE_OVERWRITTEN ; 
 int FILE_SUPERSEDE ; 
 scalar_t__ FILE_SUPERSEDED ; 
 int FILE_VALID_OPTION_FLAGS ; 
 int FILE_WRITE_DATA ; 
 TYPE_61__ Fat ; 
 int /*<<< orphan*/  FsdSystemTimeToDosDateTime (TYPE_18__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IoCheckShareAccess (int,int /*<<< orphan*/ ,TYPE_16__*,int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_15__* IoGetCurrentIrpStackLocation (TYPE_14__*) ; 
 int /*<<< orphan*/  IoSetShareAccess (int,int /*<<< orphan*/ ,TYPE_16__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IoUpdateShareAccess (TYPE_16__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KeQuerySystemTime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MmFlushForWrite ; 
 int /*<<< orphan*/  MmFlushImageSection (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int NT_SUCCESS (scalar_t__) ; 
 int /*<<< orphan*/  RtlMoveMemory (int*,int*,size_t) ; 
 int SL_OPEN_PAGING_FILE ; 
 int SL_OPEN_TARGET_DIRECTORY ; 
 scalar_t__ STATUS_ACCESS_DENIED ; 
 scalar_t__ STATUS_CANNOT_DELETE ; 
 scalar_t__ STATUS_DELETE_PENDING ; 
 scalar_t__ STATUS_FILE_IS_A_DIRECTORY ; 
 scalar_t__ STATUS_INVALID_PARAMETER ; 
 scalar_t__ STATUS_NOT_A_DIRECTORY ; 
 scalar_t__ STATUS_NOT_IMPLEMENTED ; 
 scalar_t__ STATUS_OBJECT_NAME_COLLISION ; 
 scalar_t__ STATUS_OBJECT_NAME_INVALID ; 
 scalar_t__ STATUS_OBJECT_PATH_NOT_FOUND ; 
 scalar_t__ STATUS_SHARING_VIOLATION ; 
 scalar_t__ STATUS_SUCCESS ; 
 int /*<<< orphan*/  SetFlag (int,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  VCB_IS_SYS_OR_HAS_PAGE ; 
 int VCB_VOLUME_LOCKED ; 
 scalar_t__ VfatAddEntry (TYPE_18__*,TYPE_11__*,TYPE_12__**,TYPE_12__*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VfatCloseFile (TYPE_18__*,TYPE_16__*) ; 
 scalar_t__ VfatOpenFile (TYPE_18__*,TYPE_11__*,TYPE_16__*,int,int,TYPE_12__**) ; 
 scalar_t__ VfatSetAllocationSizeInformation (TYPE_16__*,TYPE_12__*,TYPE_18__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VfatSetExtendedAttributes (TYPE_16__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VfatUpdateEntry (TYPE_18__*,TYPE_12__*) ; 
 int /*<<< orphan*/  vfatAddToStat (TYPE_18__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ vfatAttachFCBToFileObject (TYPE_18__*,TYPE_12__*,TYPE_16__*) ; 
 scalar_t__ vfatFCBIsDirectory (TYPE_12__*) ; 
 scalar_t__ vfatGetFCBForFile (TYPE_18__*,TYPE_12__**,TYPE_12__**,TYPE_11__*) ; 
 int /*<<< orphan*/  vfatGrabFCB (TYPE_18__*,TYPE_12__*) ; 
 scalar_t__ vfatIsLongIllegal (int) ; 
 int /*<<< orphan*/  vfatReleaseFCB (TYPE_18__*,TYPE_12__*) ; 
 int /*<<< orphan*/  vfatReportChange (TYPE_18__*,TYPE_12__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfatSplitPathName (TYPE_11__*,int /*<<< orphan*/ *,TYPE_11__*) ; 
 scalar_t__ vfatVolumeIsFatX (TYPE_18__*) ; 

__attribute__((used)) static NTSTATUS
VfatCreateFile(
    PDEVICE_OBJECT DeviceObject,
    PIRP Irp)
{
    PIO_STACK_LOCATION Stack;
    PFILE_OBJECT FileObject;
    NTSTATUS Status = STATUS_SUCCESS;
    PDEVICE_EXTENSION DeviceExt;
    ULONG RequestedDisposition, RequestedOptions;
    PVFATFCB pFcb = NULL;
    PVFATFCB ParentFcb = NULL;
    PVFATCCB pCcb = NULL;
    PWCHAR c, last;
    BOOLEAN PagingFileCreate;
    BOOLEAN Dots;
    BOOLEAN OpenTargetDir;
    BOOLEAN TrailingBackslash;
    UNICODE_STRING FileNameU;
    UNICODE_STRING PathNameU;
    ULONG Attributes;

    /* Unpack the various parameters. */
    Stack = IoGetCurrentIrpStackLocation(Irp);
    RequestedDisposition = ((Stack->Parameters.Create.Options >> 24) & 0xff);
    RequestedOptions = Stack->Parameters.Create.Options & FILE_VALID_OPTION_FLAGS;
    PagingFileCreate = BooleanFlagOn(Stack->Flags, SL_OPEN_PAGING_FILE);
    OpenTargetDir = BooleanFlagOn(Stack->Flags, SL_OPEN_TARGET_DIRECTORY);

    FileObject = Stack->FileObject;
    DeviceExt = DeviceObject->DeviceExtension;

    if (BooleanFlagOn(Stack->Parameters.Create.Options, FILE_OPEN_BY_FILE_ID))
    {
        return STATUS_NOT_IMPLEMENTED;
    }

    /* Check their validity. */
    if (BooleanFlagOn(RequestedOptions, FILE_DIRECTORY_FILE) &&
        RequestedDisposition == FILE_SUPERSEDE)
    {
        return STATUS_INVALID_PARAMETER;
    }

    if (BooleanFlagOn(RequestedOptions, FILE_DIRECTORY_FILE) &&
        BooleanFlagOn(RequestedOptions, FILE_NON_DIRECTORY_FILE))
    {
        return STATUS_INVALID_PARAMETER;
    }

    /* Deny create if the volume is locked */
    if (BooleanFlagOn(DeviceExt->Flags, VCB_VOLUME_LOCKED))
    {
        return STATUS_ACCESS_DENIED;
    }

    /* This a open operation for the volume itself */
    if (FileObject->FileName.Length == 0 &&
        (FileObject->RelatedFileObject == NULL ||
         FileObject->RelatedFileObject->FsContext2 != NULL ||
         FileObject->RelatedFileObject->FsContext == DeviceExt->VolumeFcb))
    {
        DPRINT("Volume opening\n");

        if (RequestedDisposition != FILE_OPEN &&
            RequestedDisposition != FILE_OPEN_IF)
        {
            return STATUS_ACCESS_DENIED;
        }

        if (BooleanFlagOn(RequestedOptions, FILE_DIRECTORY_FILE) &&
            (FileObject->RelatedFileObject == NULL || FileObject->RelatedFileObject->FsContext2 == NULL || FileObject->RelatedFileObject->FsContext == DeviceExt->VolumeFcb))
        {
            return STATUS_NOT_A_DIRECTORY;
        }

        if (OpenTargetDir)
        {
            return STATUS_INVALID_PARAMETER;
        }

        if (BooleanFlagOn(RequestedOptions, FILE_DELETE_ON_CLOSE))
        {
            return STATUS_CANNOT_DELETE;
        }

        vfatAddToStat(DeviceExt, Fat.CreateHits, 1);

        pFcb = DeviceExt->VolumeFcb;

        if (pFcb->OpenHandleCount == 0)
        {
            IoSetShareAccess(Stack->Parameters.Create.SecurityContext->DesiredAccess,
                             Stack->Parameters.Create.ShareAccess,
                             FileObject,
                             &pFcb->FCBShareAccess);
        }
        else
        {
            Status = IoCheckShareAccess(Stack->Parameters.Create.SecurityContext->DesiredAccess,
                                        Stack->Parameters.Create.ShareAccess,
                                        FileObject,
                                        &pFcb->FCBShareAccess,
                                        TRUE);
            if (!NT_SUCCESS(Status))
            {
                vfatAddToStat(DeviceExt, Fat.FailedCreates, 1);
                return Status;
            }
        }

        vfatAttachFCBToFileObject(DeviceExt, pFcb, FileObject);
        DeviceExt->OpenHandleCount++;
        pFcb->OpenHandleCount++;
        vfatAddToStat(DeviceExt, Fat.SuccessfulCreates, 1);

        Irp->IoStatus.Information = FILE_OPENED;
        return STATUS_SUCCESS;
    }

    if (FileObject->RelatedFileObject != NULL &&
        FileObject->RelatedFileObject->FsContext == DeviceExt->VolumeFcb)
    {
        ASSERT(FileObject->FileName.Length != 0);
        return STATUS_OBJECT_PATH_NOT_FOUND;
    }

    /* Check for illegal characters and illegal dot sequences in the file name */
    PathNameU = FileObject->FileName;
    c = PathNameU.Buffer + PathNameU.Length / sizeof(WCHAR);
    last = c - 1;

    Dots = TRUE;
    while (c-- > PathNameU.Buffer)
    {
        if (*c == L'\\' || c == PathNameU.Buffer)
        {
            if (Dots && last > c)
            {
                return STATUS_OBJECT_NAME_INVALID;
            }
            if (*c == L'\\' && (c - 1) > PathNameU.Buffer &&
                *(c - 1) == L'\\')
            {
                return STATUS_OBJECT_NAME_INVALID;
            }

            last = c - 1;
            Dots = TRUE;
        }
        else if (*c != L'.')
        {
            Dots = FALSE;
        }

        if (*c != '\\' && vfatIsLongIllegal(*c))
        {
            return STATUS_OBJECT_NAME_INVALID;
        }
    }

    /* Check if we try to open target directory of root dir */
    if (OpenTargetDir && FileObject->RelatedFileObject == NULL && PathNameU.Length == sizeof(WCHAR) &&
        PathNameU.Buffer[0] == L'\\')
    {
        return STATUS_INVALID_PARAMETER;
    }

    if (FileObject->RelatedFileObject && PathNameU.Length >= sizeof(WCHAR) && PathNameU.Buffer[0] == L'\\')
    {
        return STATUS_OBJECT_NAME_INVALID;
    }

    TrailingBackslash = FALSE;
    if (PathNameU.Length > sizeof(WCHAR) && PathNameU.Buffer[PathNameU.Length/sizeof(WCHAR)-1] == L'\\')
    {
        PathNameU.Length -= sizeof(WCHAR);
        TrailingBackslash = TRUE;
    }

    if (PathNameU.Length > sizeof(WCHAR) && PathNameU.Buffer[PathNameU.Length/sizeof(WCHAR)-1] == L'\\')
    {
        return STATUS_OBJECT_NAME_INVALID;
    }

    /* Try opening the file. */
    if (!OpenTargetDir)
    {
        vfatAddToStat(DeviceExt, Fat.CreateHits, 1);

        Status = VfatOpenFile(DeviceExt, &PathNameU, FileObject, RequestedDisposition, RequestedOptions, &ParentFcb);
    }
    else
    {
        PVFATFCB TargetFcb;
        LONG idx, FileNameLen;

        vfatAddToStat(DeviceExt, Fat.CreateHits, 1);

        ParentFcb = (FileObject->RelatedFileObject != NULL) ? FileObject->RelatedFileObject->FsContext : NULL;
        if (ParentFcb)
        {
            vfatGrabFCB(DeviceExt, ParentFcb);
        }

        Status = vfatGetFCBForFile(DeviceExt, &ParentFcb, &TargetFcb, &PathNameU);
        if (NT_SUCCESS(Status))
        {
            vfatReleaseFCB(DeviceExt, TargetFcb);
            Irp->IoStatus.Information = FILE_EXISTS;
        }
        else
        {
            Irp->IoStatus.Information = FILE_DOES_NOT_EXIST;
        }

        idx = FileObject->FileName.Length / sizeof(WCHAR) - 1;

        /* Skip trailing \ - if any */
        if (PathNameU.Buffer[idx] == L'\\')
        {
            --idx;
            PathNameU.Length -= sizeof(WCHAR);
        }

        /* Get file name */
        while (idx >= 0 && PathNameU.Buffer[idx] != L'\\')
        {
            --idx;
        }

        if (idx > 0 || PathNameU.Buffer[0] == L'\\')
        {
            /* We don't want to include / in the name */
            FileNameLen = PathNameU.Length - ((idx + 1) * sizeof(WCHAR));

            /* Update FO just to keep file name */
            /* Skip first slash */
            ++idx;
            FileObject->FileName.Length = FileNameLen;
            RtlMoveMemory(&PathNameU.Buffer[0], &PathNameU.Buffer[idx], FileObject->FileName.Length);
#if 0
            /* Terminate the string at the last backslash */
            PathNameU.Buffer[idx + 1] = UNICODE_NULL;
            PathNameU.Length = (idx + 1) * sizeof(WCHAR);
            PathNameU.MaximumLength = PathNameU.Length + sizeof(WCHAR);

            /* Update the file object as well */
            FileObject->FileName.Length = PathNameU.Length;
            FileObject->FileName.MaximumLength = PathNameU.MaximumLength;
#endif
        }
        else
        {
            /* This is a relative open and we have only the filename, so open the parent directory
             * It is in RelatedFileObject
             */
            ASSERT(FileObject->RelatedFileObject != NULL);

            /* No need to modify the FO, it already has the name */
        }

        /* We're done with opening! */
        if (ParentFcb != NULL)
        {
            Status = vfatAttachFCBToFileObject(DeviceExt, ParentFcb, FileObject);
        }

        if (NT_SUCCESS(Status))
        {
            pFcb = FileObject->FsContext;
            ASSERT(pFcb == ParentFcb);

            if (pFcb->OpenHandleCount == 0)
            {
                IoSetShareAccess(Stack->Parameters.Create.SecurityContext->DesiredAccess,
                                 Stack->Parameters.Create.ShareAccess,
                                 FileObject,
                                 &pFcb->FCBShareAccess);
            }
            else
            {
                Status = IoCheckShareAccess(Stack->Parameters.Create.SecurityContext->DesiredAccess,
                                            Stack->Parameters.Create.ShareAccess,
                                            FileObject,
                                            &pFcb->FCBShareAccess,
                                            FALSE);
                if (!NT_SUCCESS(Status))
                {
                    VfatCloseFile(DeviceExt, FileObject);
                    vfatAddToStat(DeviceExt, Fat.FailedCreates, 1);
                    return Status;
                }
            }

            pCcb = FileObject->FsContext2;
            if (BooleanFlagOn(RequestedOptions, FILE_DELETE_ON_CLOSE))
            {
                pCcb->Flags |= CCB_DELETE_ON_CLOSE;
            }

            pFcb->OpenHandleCount++;
            DeviceExt->OpenHandleCount++;
        }
        else if (ParentFcb != NULL)
        {
            vfatReleaseFCB(DeviceExt, ParentFcb);
        }

        if (NT_SUCCESS(Status))
        {
            vfatAddToStat(DeviceExt, Fat.SuccessfulCreates, 1);
        }
        else
        {
            vfatAddToStat(DeviceExt, Fat.FailedCreates, 1);
        }

        return Status;
    }

    /*
     * If the directory containing the file to open doesn't exist then
     * fail immediately
     */
    if (Status == STATUS_OBJECT_PATH_NOT_FOUND ||
        Status == STATUS_INVALID_PARAMETER ||
        Status == STATUS_DELETE_PENDING ||
        Status == STATUS_ACCESS_DENIED ||
        Status == STATUS_OBJECT_NAME_COLLISION)
    {
        if (ParentFcb)
        {
            vfatReleaseFCB(DeviceExt, ParentFcb);
        }
        vfatAddToStat(DeviceExt, Fat.FailedCreates, 1);
        return Status;
    }

    if (!NT_SUCCESS(Status) && ParentFcb == NULL)
    {
        DPRINT1("VfatOpenFile failed for '%wZ', status %x\n", &PathNameU, Status);
        vfatAddToStat(DeviceExt, Fat.FailedCreates, 1);
        return Status;
    }

    Attributes = (Stack->Parameters.Create.FileAttributes & (FILE_ATTRIBUTE_ARCHIVE |
                                                             FILE_ATTRIBUTE_SYSTEM |
                                                             FILE_ATTRIBUTE_HIDDEN |
                                                             FILE_ATTRIBUTE_DIRECTORY |
                                                             FILE_ATTRIBUTE_READONLY));

    /* If the file open failed then create the required file */
    if (!NT_SUCCESS (Status))
    {
        if (RequestedDisposition == FILE_CREATE ||
            RequestedDisposition == FILE_OPEN_IF ||
            RequestedDisposition == FILE_OVERWRITE_IF ||
            RequestedDisposition == FILE_SUPERSEDE)
        {
            if (!BooleanFlagOn(RequestedOptions, FILE_DIRECTORY_FILE))
            {
                if (TrailingBackslash)
                {
                    vfatReleaseFCB(DeviceExt, ParentFcb);
                    vfatAddToStat(DeviceExt, Fat.FailedCreates, 1);
                    return STATUS_OBJECT_NAME_INVALID;
                }
                Attributes |= FILE_ATTRIBUTE_ARCHIVE;
            }
            vfatSplitPathName(&PathNameU, NULL, &FileNameU);
            Status = VfatAddEntry(DeviceExt, &FileNameU, &pFcb, ParentFcb, RequestedOptions,
                                  Attributes, NULL);
            vfatReleaseFCB(DeviceExt, ParentFcb);
            if (NT_SUCCESS(Status))
            {
                Status = vfatAttachFCBToFileObject(DeviceExt, pFcb, FileObject);
                if (!NT_SUCCESS(Status))
                {
                    vfatReleaseFCB(DeviceExt, pFcb);
                    vfatAddToStat(DeviceExt, Fat.FailedCreates, 1);
                    return Status;
                }

                Irp->IoStatus.Information = FILE_CREATED;
                VfatSetAllocationSizeInformation(FileObject,
                                                 pFcb,
                                                 DeviceExt,
                                                 &Irp->Overlay.AllocationSize);
                VfatSetExtendedAttributes(FileObject,
                                          Irp->AssociatedIrp.SystemBuffer,
                                          Stack->Parameters.Create.EaLength);

                if (PagingFileCreate)
                {
                    pFcb->Flags |= FCB_IS_PAGE_FILE;
                    SetFlag(DeviceExt->Flags, VCB_IS_SYS_OR_HAS_PAGE);
                }
            }
            else
            {
                vfatAddToStat(DeviceExt, Fat.FailedCreates, 1);
                return Status;
            }
        }
        else
        {
            vfatReleaseFCB(DeviceExt, ParentFcb);
            vfatAddToStat(DeviceExt, Fat.FailedCreates, 1);
            return Status;
        }
    }
    else
    {
        if (ParentFcb)
        {
            vfatReleaseFCB(DeviceExt, ParentFcb);
        }

        pFcb = FileObject->FsContext;

        /* Otherwise fail if the caller wanted to create a new file  */
        if (RequestedDisposition == FILE_CREATE)
        {
            VfatCloseFile(DeviceExt, FileObject);
            if (TrailingBackslash && !vfatFCBIsDirectory(pFcb))
            {
                vfatAddToStat(DeviceExt, Fat.FailedCreates, 1);
                return STATUS_OBJECT_NAME_INVALID;
            }
            Irp->IoStatus.Information = FILE_EXISTS;
            vfatAddToStat(DeviceExt, Fat.FailedCreates, 1);
            return STATUS_OBJECT_NAME_COLLISION;
        }

        if (pFcb->OpenHandleCount != 0)
        {
            Status = IoCheckShareAccess(Stack->Parameters.Create.SecurityContext->DesiredAccess,
                                        Stack->Parameters.Create.ShareAccess,
                                        FileObject,
                                        &pFcb->FCBShareAccess,
                                        FALSE);
            if (!NT_SUCCESS(Status))
            {
                VfatCloseFile(DeviceExt, FileObject);
                vfatAddToStat(DeviceExt, Fat.FailedCreates, 1);
                return Status;
            }
        }

        /*
         * Check the file has the requested attributes
         */
        if (BooleanFlagOn(RequestedOptions, FILE_NON_DIRECTORY_FILE) &&
            vfatFCBIsDirectory(pFcb))
        {
            VfatCloseFile (DeviceExt, FileObject);
            vfatAddToStat(DeviceExt, Fat.FailedCreates, 1);
            return STATUS_FILE_IS_A_DIRECTORY;
        }
        if (BooleanFlagOn(RequestedOptions, FILE_DIRECTORY_FILE) &&
            !vfatFCBIsDirectory(pFcb))
        {
            VfatCloseFile (DeviceExt, FileObject);
            vfatAddToStat(DeviceExt, Fat.FailedCreates, 1);
            return STATUS_NOT_A_DIRECTORY;
        }
        if (TrailingBackslash && !vfatFCBIsDirectory(pFcb))
        {
            VfatCloseFile (DeviceExt, FileObject);
            vfatAddToStat(DeviceExt, Fat.FailedCreates, 1);
            return STATUS_OBJECT_NAME_INVALID;
        }
#ifndef USE_ROS_CC_AND_FS
        if (!vfatFCBIsDirectory(pFcb))
        {
            if (BooleanFlagOn(Stack->Parameters.Create.SecurityContext->DesiredAccess, FILE_WRITE_DATA) ||
                RequestedDisposition == FILE_OVERWRITE ||
                RequestedDisposition == FILE_OVERWRITE_IF ||
                (RequestedOptions & FILE_DELETE_ON_CLOSE))
            {
                if (!MmFlushImageSection(&pFcb->SectionObjectPointers, MmFlushForWrite))
                {
                    DPRINT1("%wZ\n", &pFcb->PathNameU);
                    DPRINT1("%d %d %d\n", Stack->Parameters.Create.SecurityContext->DesiredAccess & FILE_WRITE_DATA,
                            RequestedDisposition == FILE_OVERWRITE, RequestedDisposition == FILE_OVERWRITE_IF);
                    VfatCloseFile (DeviceExt, FileObject);
                    vfatAddToStat(DeviceExt, Fat.FailedCreates, 1);
                    return (BooleanFlagOn(RequestedOptions, FILE_DELETE_ON_CLOSE)) ? STATUS_CANNOT_DELETE
                                                                                   : STATUS_SHARING_VIOLATION;
                }
            }
        }
#endif
        if (PagingFileCreate)
        {
            /* FIXME:
             *   Do more checking for page files. It is possible,
             *   that the file was opened and closed previously
             *   as a normal cached file. In this case, the cache
             *   manager has referenced the fileobject and the fcb
             *   is held in memory. Try to remove the fileobject
             *   from cache manager and use the fcb.
             */
            if (pFcb->RefCount > 1)
            {
                if(!BooleanFlagOn(pFcb->Flags, FCB_IS_PAGE_FILE))
                {
                    VfatCloseFile(DeviceExt, FileObject);
                    vfatAddToStat(DeviceExt, Fat.FailedCreates, 1);
                    return STATUS_INVALID_PARAMETER;
                }
            }
            else
            {
                pFcb->Flags |= FCB_IS_PAGE_FILE;
                SetFlag(DeviceExt->Flags, VCB_IS_SYS_OR_HAS_PAGE);
            }
        }
        else
        {
            if (BooleanFlagOn(pFcb->Flags, FCB_IS_PAGE_FILE))
            {
                VfatCloseFile(DeviceExt, FileObject);
                vfatAddToStat(DeviceExt, Fat.FailedCreates, 1);
                return STATUS_INVALID_PARAMETER;
            }
        }

        if (RequestedDisposition == FILE_OVERWRITE ||
            RequestedDisposition == FILE_OVERWRITE_IF ||
            RequestedDisposition == FILE_SUPERSEDE)
        {
            if ((BooleanFlagOn(*pFcb->Attributes, FILE_ATTRIBUTE_HIDDEN) && !BooleanFlagOn(Attributes, FILE_ATTRIBUTE_HIDDEN)) ||
                (BooleanFlagOn(*pFcb->Attributes, FILE_ATTRIBUTE_SYSTEM) && !BooleanFlagOn(Attributes, FILE_ATTRIBUTE_SYSTEM)))
            {
                VfatCloseFile(DeviceExt, FileObject);
                vfatAddToStat(DeviceExt, Fat.FailedCreates, 1);
                return STATUS_ACCESS_DENIED;
            }

            if (!vfatFCBIsDirectory(pFcb))
            {
                LARGE_INTEGER SystemTime;

                if (RequestedDisposition == FILE_SUPERSEDE)
                {
                    *pFcb->Attributes = Attributes;
                }
                else
                {
                    *pFcb->Attributes |= Attributes;
                }
                *pFcb->Attributes |= FILE_ATTRIBUTE_ARCHIVE;

                KeQuerySystemTime(&SystemTime);
                if (vfatVolumeIsFatX(DeviceExt))
                {
                    FsdSystemTimeToDosDateTime(DeviceExt,
                                               &SystemTime, &pFcb->entry.FatX.UpdateDate,
                                               &pFcb->entry.FatX.UpdateTime);
                }
                else
                {
                    FsdSystemTimeToDosDateTime(DeviceExt,
                                               &SystemTime, &pFcb->entry.Fat.UpdateDate,
                                               &pFcb->entry.Fat.UpdateTime);
                }

                VfatUpdateEntry(DeviceExt, pFcb);
            }

            ExAcquireResourceExclusiveLite(&(pFcb->MainResource), TRUE);
            Status = VfatSetAllocationSizeInformation(FileObject,
                                                      pFcb,
                                                      DeviceExt,
                                                      &Irp->Overlay.AllocationSize);
            ExReleaseResourceLite(&(pFcb->MainResource));
            if (!NT_SUCCESS (Status))
            {
                VfatCloseFile(DeviceExt, FileObject);
                vfatAddToStat(DeviceExt, Fat.FailedCreates, 1);
                return Status;
            }
        }

        if (RequestedDisposition == FILE_SUPERSEDE)
        {
            Irp->IoStatus.Information = FILE_SUPERSEDED;
        }
        else if (RequestedDisposition == FILE_OVERWRITE ||
                 RequestedDisposition == FILE_OVERWRITE_IF)
        {
            Irp->IoStatus.Information = FILE_OVERWRITTEN;
        }
        else
        {
            Irp->IoStatus.Information = FILE_OPENED;
        }
    }

    if (pFcb->OpenHandleCount == 0)
    {
        IoSetShareAccess(Stack->Parameters.Create.SecurityContext->DesiredAccess,
                         Stack->Parameters.Create.ShareAccess,
                         FileObject,
                         &pFcb->FCBShareAccess);
    }
    else
    {
        IoUpdateShareAccess(FileObject,
                            &pFcb->FCBShareAccess);
    }

    pCcb = FileObject->FsContext2;
    if (BooleanFlagOn(RequestedOptions, FILE_DELETE_ON_CLOSE))
    {
        pCcb->Flags |= CCB_DELETE_ON_CLOSE;
    }

    if (Irp->IoStatus.Information == FILE_CREATED)
    {
        vfatReportChange(DeviceExt,
                         pFcb,
                         (vfatFCBIsDirectory(pFcb) ?
                          FILE_NOTIFY_CHANGE_DIR_NAME : FILE_NOTIFY_CHANGE_FILE_NAME),
                         FILE_ACTION_ADDED);
    }
    else if (Irp->IoStatus.Information == FILE_OVERWRITTEN ||
             Irp->IoStatus.Information == FILE_SUPERSEDED)
    {
        vfatReportChange(DeviceExt,
                         pFcb,
                         FILE_NOTIFY_CHANGE_LAST_WRITE | FILE_NOTIFY_CHANGE_ATTRIBUTES | FILE_NOTIFY_CHANGE_SIZE,
                         FILE_ACTION_MODIFIED);
    }

    pFcb->OpenHandleCount++;
    DeviceExt->OpenHandleCount++;

    /* FIXME : test write access if requested */

    /* FIXME: That is broken, we cannot reach this code path with failure */
    ASSERT(NT_SUCCESS(Status));
    if (NT_SUCCESS(Status))
    {
        vfatAddToStat(DeviceExt, Fat.SuccessfulCreates, 1);
    }
    else
    {
        vfatAddToStat(DeviceExt, Fat.FailedCreates, 1);
    }

    return Status;
}