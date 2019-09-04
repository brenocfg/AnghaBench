#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_40__   TYPE_4__ ;
typedef  struct TYPE_39__   TYPE_3__ ;
typedef  struct TYPE_38__   TYPE_2__ ;
typedef  struct TYPE_37__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_37__ {int Length; int MaximumLength; int* Buffer; } ;
typedef  TYPE_1__ UNICODE_STRING ;
typedef  int ULONG ;
struct TYPE_40__ {TYPE_1__ FileName; TYPE_2__* FsContext; } ;
struct TYPE_39__ {int* FileName; int FileNameLength; int /*<<< orphan*/ * RootDirectory; int /*<<< orphan*/  ReplaceIfExists; } ;
struct TYPE_38__ {int RefCount; struct TYPE_38__* parentFcb; int /*<<< orphan*/  ParentListHead; TYPE_1__ PathNameU; TYPE_1__ DirNameU; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_2__* PVFATFCB ;
typedef  TYPE_3__* PFILE_RENAME_INFORMATION ;
typedef  TYPE_4__* PFILE_OBJECT ;
typedef  int /*<<< orphan*/  PDEVICE_EXTENSION ;
typedef  int /*<<< orphan*/  OBJECT_ATTRIBUTES ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  IO_STATUS_BLOCK ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  CreateFileTypeNone ; 
 int /*<<< orphan*/  DPRINT (char*,...) ; 
 void* ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExFreePoolWithTag (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExGetPreviousMode () ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FILE_ACTION_ADDED ; 
 int /*<<< orphan*/  FILE_ACTION_MODIFIED ; 
 int /*<<< orphan*/  FILE_ACTION_REMOVED ; 
 int /*<<< orphan*/  FILE_ACTION_RENAMED_NEW_NAME ; 
 int /*<<< orphan*/  FILE_ACTION_RENAMED_OLD_NAME ; 
 int FILE_NOTIFY_CHANGE_ATTRIBUTES ; 
 int FILE_NOTIFY_CHANGE_CREATION ; 
 int FILE_NOTIFY_CHANGE_DIR_NAME ; 
 int FILE_NOTIFY_CHANGE_EA ; 
 int FILE_NOTIFY_CHANGE_FILE_NAME ; 
 int FILE_NOTIFY_CHANGE_LAST_ACCESS ; 
 int FILE_NOTIFY_CHANGE_LAST_WRITE ; 
 int FILE_NOTIFY_CHANGE_SIZE ; 
 int /*<<< orphan*/  FILE_OPEN ; 
 int /*<<< orphan*/  FILE_OPEN_FOR_BACKUP_INTENT ; 
 int FILE_READ_DATA ; 
 int FILE_SHARE_READ ; 
 int FILE_SHARE_WRITE ; 
 int FILE_WRITE_DATA ; 
 scalar_t__ FsRtlAreNamesEqual (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int IO_FORCE_ACCESS_CHECK ; 
 int IO_OPEN_TARGET_DIRECTORY ; 
 int /*<<< orphan*/  InitializeObjectAttributes (int /*<<< orphan*/ *,TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IoCreateFile (int /*<<< orphan*/ **,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * IoFileObjectType ; 
 scalar_t__ IoGetRelatedDeviceObject (TYPE_4__*) ; 
 int /*<<< orphan*/  IsListEmpty (int /*<<< orphan*/ *) ; 
 scalar_t__ IsThereAChildOpened (TYPE_2__*) ; 
 int /*<<< orphan*/  KernelMode ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NonPagedPool ; 
 int OBJ_CASE_INSENSITIVE ; 
 int OBJ_KERNEL_HANDLE ; 
 int /*<<< orphan*/  ObDereferenceObject (TYPE_4__*) ; 
 int /*<<< orphan*/  ObReferenceObjectByHandle (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlAppendUnicodeStringToString (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  RtlCopyUnicodeString (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  RtlInitEmptyUnicodeString (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_ACCESS_DENIED ; 
 int /*<<< orphan*/  STATUS_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  STATUS_NOT_SAME_DEVICE ; 
 int /*<<< orphan*/  STATUS_OBJECT_NAME_INVALID ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int SYNCHRONIZE ; 
 int /*<<< orphan*/  TAG_NAME ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VfatMoveEntry (int /*<<< orphan*/ ,TYPE_2__*,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  VfatRenameChildFCB (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ZwClose (int /*<<< orphan*/ *) ; 
 scalar_t__ vfatFCBIsDirectory (TYPE_2__*) ; 
 scalar_t__ vfatFCBIsRoot (TYPE_2__*) ; 
 int /*<<< orphan*/  vfatGrabFCB (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  vfatPrepareTargetForRename (int /*<<< orphan*/ ,TYPE_2__**,TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__*,scalar_t__*) ; 
 int /*<<< orphan*/  vfatReleaseFCB (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  vfatRenameEntry (int /*<<< orphan*/ ,TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfatReportChange (int /*<<< orphan*/ ,TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfatSplitPathName (TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static
NTSTATUS
VfatSetRenameInformation(
    PFILE_OBJECT FileObject,
    PVFATFCB FCB,
    PDEVICE_EXTENSION DeviceExt,
    PFILE_RENAME_INFORMATION RenameInfo,
    PFILE_OBJECT TargetFileObject)
{
#ifdef NASSERTS_RENAME
#pragma push_macro("ASSERT")
#undef ASSERT
#define ASSERT(x) ((VOID) 0)
#endif
    NTSTATUS Status;
    UNICODE_STRING NewName;
    UNICODE_STRING SourcePath;
    UNICODE_STRING SourceFile;
    UNICODE_STRING NewPath;
    UNICODE_STRING NewFile;
    PFILE_OBJECT RootFileObject;
    PVFATFCB RootFCB;
    UNICODE_STRING RenameInfoString;
    PVFATFCB ParentFCB;
    IO_STATUS_BLOCK IoStatusBlock;
    OBJECT_ATTRIBUTES ObjectAttributes;
    HANDLE TargetHandle;
    BOOLEAN DeletedTarget;
    ULONG OldReferences, NewReferences;
    PVFATFCB OldParent;

    DPRINT("VfatSetRenameInfo(%p, %p, %p, %p, %p)\n", FileObject, FCB, DeviceExt, RenameInfo, TargetFileObject);

    /* Disallow renaming root */
    if (vfatFCBIsRoot(FCB))
    {
        return STATUS_INVALID_PARAMETER;
    }

    OldReferences = FCB->parentFcb->RefCount;
#ifdef NASSERTS_RENAME
    UNREFERENCED_PARAMETER(OldReferences);
#endif

    /* If we are performing relative opening for rename, get FO for getting FCB and path name */
    if (RenameInfo->RootDirectory != NULL)
    {
        /* We cannot tolerate relative opening with a full path */
        if (RenameInfo->FileName[0] == L'\\')
        {
            return STATUS_OBJECT_NAME_INVALID;
        }

        Status = ObReferenceObjectByHandle(RenameInfo->RootDirectory,
                                           FILE_READ_DATA,
                                           *IoFileObjectType,
                                           ExGetPreviousMode(),
                                           (PVOID *)&RootFileObject,
                                           NULL);
        if (!NT_SUCCESS(Status))
        {
            return Status;
        }

        RootFCB = RootFileObject->FsContext;
    }

    RtlInitEmptyUnicodeString(&NewName, NULL, 0);
    ParentFCB = NULL;

    if (TargetFileObject == NULL)
    {
        /* If we don't have target file object, construct paths thanks to relative FCB, if any, and with
         * information supplied by the user
         */

        /* First, setup a string we'll work on */
        RenameInfoString.Length = RenameInfo->FileNameLength;
        RenameInfoString.MaximumLength = RenameInfo->FileNameLength;
        RenameInfoString.Buffer = RenameInfo->FileName;

        /* Check whether we have FQN */
        if (RenameInfoString.Length > 6 * sizeof(WCHAR))
        {
            if (RenameInfoString.Buffer[0] == L'\\' && RenameInfoString.Buffer[1] == L'?' &&
                RenameInfoString.Buffer[2] == L'?' && RenameInfoString.Buffer[3] == L'\\' &&
                RenameInfoString.Buffer[5] == L':' && (RenameInfoString.Buffer[4] >= L'A' &&
                RenameInfoString.Buffer[4] <= L'Z'))
            {
                /* If so, open its target directory */
                InitializeObjectAttributes(&ObjectAttributes,
                                           &RenameInfoString,
                                           OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE,
                                           NULL, NULL);

                Status = IoCreateFile(&TargetHandle,
                                      FILE_WRITE_DATA | SYNCHRONIZE,
                                      &ObjectAttributes,
                                      &IoStatusBlock,
                                      NULL, 0,
                                      FILE_SHARE_READ | FILE_SHARE_WRITE,
                                      FILE_OPEN,
                                      FILE_OPEN_FOR_BACKUP_INTENT,
                                      NULL, 0,
                                      CreateFileTypeNone,
                                      NULL,
                                      IO_FORCE_ACCESS_CHECK | IO_OPEN_TARGET_DIRECTORY);
                if (!NT_SUCCESS(Status))
                {
                    goto Cleanup;
                }

                /* Get its FO to get the FCB */
                Status = ObReferenceObjectByHandle(TargetHandle,
                                                   FILE_WRITE_DATA,
                                                   *IoFileObjectType,
                                                   KernelMode,
                                                   (PVOID *)&TargetFileObject,
                                                   NULL);
                if (!NT_SUCCESS(Status))
                {
                    ZwClose(TargetHandle);
                    goto Cleanup;
                }

                /* Are we working on the same volume? */
                if (IoGetRelatedDeviceObject(TargetFileObject) != IoGetRelatedDeviceObject(FileObject))
                {
                    ObDereferenceObject(TargetFileObject);
                    ZwClose(TargetHandle);
                    TargetFileObject = NULL;
                    Status = STATUS_NOT_SAME_DEVICE;
                    goto Cleanup;
                }
            }
        }

        NewName.Length = 0;
        NewName.MaximumLength = RenameInfo->FileNameLength;
        if (RenameInfo->RootDirectory != NULL)
        {
            NewName.MaximumLength += sizeof(WCHAR) + RootFCB->PathNameU.Length;
        }
        else if (RenameInfo->FileName[0] != L'\\')
        {
            /* We don't have full path, and we don't have root directory:
             * => we move inside the same directory
             */
            NewName.MaximumLength += sizeof(WCHAR) + FCB->DirNameU.Length;
        }
        else if (TargetFileObject != NULL)
        {
            /* We had a FQN:
             * => we need to use its correct path
             */
            NewName.MaximumLength += sizeof(WCHAR) + ((PVFATFCB)TargetFileObject->FsContext)->PathNameU.Length;
        }

        NewName.Buffer = ExAllocatePoolWithTag(NonPagedPool, NewName.MaximumLength, TAG_NAME);
        if (NewName.Buffer == NULL)
        {
            if (TargetFileObject != NULL)
            {
                ObDereferenceObject(TargetFileObject);
                ZwClose(TargetHandle);
                TargetFileObject = NULL;
            }
            Status = STATUS_INSUFFICIENT_RESOURCES;
            goto Cleanup;
        }

        if (RenameInfo->RootDirectory != NULL)
        {
            /* Here, copy first absolute and then append relative */ 
            RtlCopyUnicodeString(&NewName, &RootFCB->PathNameU);
            NewName.Buffer[NewName.Length / sizeof(WCHAR)] = L'\\';
            NewName.Length += sizeof(WCHAR);
            RtlAppendUnicodeStringToString(&NewName, &RenameInfoString);
        }
        else if (RenameInfo->FileName[0] != L'\\')
        {
            /* Here, copy first work directory and then append filename */
            RtlCopyUnicodeString(&NewName, &FCB->DirNameU);
            NewName.Buffer[NewName.Length / sizeof(WCHAR)] = L'\\';
            NewName.Length += sizeof(WCHAR);
            RtlAppendUnicodeStringToString(&NewName, &RenameInfoString);
        }
        else if (TargetFileObject != NULL)
        {
            /* Here, copy first path name and then append filename */
            RtlCopyUnicodeString(&NewName, &((PVFATFCB)TargetFileObject->FsContext)->PathNameU);
            NewName.Buffer[NewName.Length / sizeof(WCHAR)] = L'\\';
            NewName.Length += sizeof(WCHAR);
            RtlAppendUnicodeStringToString(&NewName, &RenameInfoString);
        }
        else
        {
            /* Here we should have full path, so simply copy it */
            RtlCopyUnicodeString(&NewName, &RenameInfoString);
        }

        /* Do we have to cleanup some stuff? */
        if (TargetFileObject != NULL)
        {
            ObDereferenceObject(TargetFileObject);
            ZwClose(TargetHandle);
            TargetFileObject = NULL;
        }
    }
    else
    {
        /* At that point, we shouldn't care about whether we are relative opening
         * Target FO FCB should already have full path
         */

        /* Before constructing string, just make a sanity check (just to be sure!) */
        if (IoGetRelatedDeviceObject(TargetFileObject) != IoGetRelatedDeviceObject(FileObject))
        {
            Status = STATUS_NOT_SAME_DEVICE;
            goto Cleanup;
        }

        NewName.Length = 0;
        NewName.MaximumLength = TargetFileObject->FileName.Length + ((PVFATFCB)TargetFileObject->FsContext)->PathNameU.Length + sizeof(WCHAR);
        NewName.Buffer = ExAllocatePoolWithTag(NonPagedPool, NewName.MaximumLength, TAG_NAME);
        if (NewName.Buffer == NULL)
        {
            Status = STATUS_INSUFFICIENT_RESOURCES;
            goto Cleanup;
        }

        RtlCopyUnicodeString(&NewName, &((PVFATFCB)TargetFileObject->FsContext)->PathNameU);
        /* If \, it's already backslash terminated, don't add it */
        if (!vfatFCBIsRoot(TargetFileObject->FsContext))
        {
            NewName.Buffer[NewName.Length / sizeof(WCHAR)] = L'\\';
            NewName.Length += sizeof(WCHAR);
        }
        RtlAppendUnicodeStringToString(&NewName, &TargetFileObject->FileName);
    }

    /* Explode our paths to get path & filename */
    vfatSplitPathName(&FCB->PathNameU, &SourcePath, &SourceFile);
    DPRINT("Old dir: %wZ, Old file: %wZ\n", &SourcePath, &SourceFile);
    vfatSplitPathName(&NewName, &NewPath, &NewFile);
    DPRINT("New dir: %wZ, New file: %wZ\n", &NewPath, &NewFile);

    if (vfatFCBIsDirectory(FCB) && !IsListEmpty(&FCB->ParentListHead))
    {
        if (IsThereAChildOpened(FCB))
        {
            Status = STATUS_ACCESS_DENIED;
            ASSERT(OldReferences == FCB->parentFcb->RefCount);
            goto Cleanup;
        }
    }

    /* Are we working in place? */
    if (FsRtlAreNamesEqual(&SourcePath, &NewPath, TRUE, NULL))
    {
        if (FsRtlAreNamesEqual(&SourceFile, &NewFile, FALSE, NULL))
        {
            Status = STATUS_SUCCESS;
            ASSERT(OldReferences == FCB->parentFcb->RefCount);
            goto Cleanup;
        }

        if (FsRtlAreNamesEqual(&SourceFile, &NewFile, TRUE, NULL))
        {
            vfatReportChange(DeviceExt,
                             FCB,
                             (vfatFCBIsDirectory(FCB) ?
                              FILE_NOTIFY_CHANGE_DIR_NAME : FILE_NOTIFY_CHANGE_FILE_NAME),
                             FILE_ACTION_RENAMED_OLD_NAME);
            Status = vfatRenameEntry(DeviceExt, FCB, &NewFile, TRUE);
            if (NT_SUCCESS(Status))
            {
                vfatReportChange(DeviceExt,
                                 FCB,
                                 (vfatFCBIsDirectory(FCB) ?
                                  FILE_NOTIFY_CHANGE_DIR_NAME : FILE_NOTIFY_CHANGE_FILE_NAME),
                                 FILE_ACTION_RENAMED_NEW_NAME);
            }
        }
        else
        {
            /* Try to find target */
            ParentFCB = FCB->parentFcb;
            vfatGrabFCB(DeviceExt, ParentFCB);
            Status = vfatPrepareTargetForRename(DeviceExt,
                                                &ParentFCB,
                                                &NewFile,
                                                RenameInfo->ReplaceIfExists,
                                                &NewPath,
                                                &DeletedTarget);
            if (!NT_SUCCESS(Status))
            {
                ASSERT(OldReferences == FCB->parentFcb->RefCount - 1);
                ASSERT(OldReferences == ParentFCB->RefCount - 1);
                goto Cleanup;
            }

            vfatReportChange(DeviceExt,
                             FCB,
                             (vfatFCBIsDirectory(FCB) ?
                              FILE_NOTIFY_CHANGE_DIR_NAME : FILE_NOTIFY_CHANGE_FILE_NAME),
                             (DeletedTarget ? FILE_ACTION_REMOVED : FILE_ACTION_RENAMED_OLD_NAME));
            Status = vfatRenameEntry(DeviceExt, FCB, &NewFile, FALSE);
            if (NT_SUCCESS(Status))
            {
                if (DeletedTarget)
                {
                    vfatReportChange(DeviceExt,
                                     FCB,
                                     FILE_NOTIFY_CHANGE_ATTRIBUTES | FILE_NOTIFY_CHANGE_SIZE | FILE_NOTIFY_CHANGE_LAST_WRITE
                                     | FILE_NOTIFY_CHANGE_LAST_ACCESS | FILE_NOTIFY_CHANGE_CREATION | FILE_NOTIFY_CHANGE_EA,
                                     FILE_ACTION_MODIFIED);
                }
                else
                {
                    vfatReportChange(DeviceExt,
                                     FCB,
                                     (vfatFCBIsDirectory(FCB) ?
                                      FILE_NOTIFY_CHANGE_DIR_NAME : FILE_NOTIFY_CHANGE_FILE_NAME),
                                     FILE_ACTION_RENAMED_NEW_NAME);
                }
            }
        }

        ASSERT(OldReferences == FCB->parentFcb->RefCount - 1); // extra grab
        ASSERT(OldReferences == ParentFCB->RefCount - 1); // extra grab
    }
    else
    {

        /* Try to find target */
        ParentFCB = NULL;
        OldParent = FCB->parentFcb;
#ifdef NASSERTS_RENAME
        UNREFERENCED_PARAMETER(OldParent);
#endif
        Status = vfatPrepareTargetForRename(DeviceExt,
                                            &ParentFCB,
                                            &NewName,
                                            RenameInfo->ReplaceIfExists,
                                            &NewPath,
                                            &DeletedTarget);
        if (!NT_SUCCESS(Status))
        {
            ASSERT(OldReferences == FCB->parentFcb->RefCount);
            goto Cleanup;
        }

        NewReferences = ParentFCB->RefCount;
#ifdef NASSERTS_RENAME
        UNREFERENCED_PARAMETER(NewReferences);
#endif

        vfatReportChange(DeviceExt,
                         FCB,
                         (vfatFCBIsDirectory(FCB) ?
                          FILE_NOTIFY_CHANGE_DIR_NAME : FILE_NOTIFY_CHANGE_FILE_NAME),
                         FILE_ACTION_REMOVED);
        Status = VfatMoveEntry(DeviceExt, FCB, &NewFile, ParentFCB);
        if (NT_SUCCESS(Status))
        {
            if (DeletedTarget)
            {
                vfatReportChange(DeviceExt,
                                 FCB,
                                 FILE_NOTIFY_CHANGE_ATTRIBUTES | FILE_NOTIFY_CHANGE_SIZE | FILE_NOTIFY_CHANGE_LAST_WRITE
                                 | FILE_NOTIFY_CHANGE_LAST_ACCESS | FILE_NOTIFY_CHANGE_CREATION | FILE_NOTIFY_CHANGE_EA,
                                 FILE_ACTION_MODIFIED);
            }
            else
            {
                vfatReportChange(DeviceExt,
                                 FCB,
                                 (vfatFCBIsDirectory(FCB) ?
                                  FILE_NOTIFY_CHANGE_DIR_NAME : FILE_NOTIFY_CHANGE_FILE_NAME),
                                 FILE_ACTION_ADDED);
            }
        }
    }

    if (NT_SUCCESS(Status) && vfatFCBIsDirectory(FCB))
    {
        VfatRenameChildFCB(DeviceExt, FCB);
    }

    ASSERT(OldReferences == OldParent->RefCount + 1); // removed file
    ASSERT(NewReferences == ParentFCB->RefCount - 1); // new file
Cleanup:
    if (ParentFCB != NULL) vfatReleaseFCB(DeviceExt, ParentFCB);
    if (NewName.Buffer != NULL) ExFreePoolWithTag(NewName.Buffer, TAG_NAME);
    if (RenameInfo->RootDirectory != NULL) ObDereferenceObject(RootFileObject);

    return Status;
#ifdef NASSERTS_RENAME
#pragma pop_macro("ASSERT")
#endif
}