#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  OpenHandleCount; } ;
struct TYPE_9__ {scalar_t__ Buffer; } ;
struct TYPE_11__ {TYPE_1__ FileName; int /*<<< orphan*/ * SectionObjectPointer; int /*<<< orphan*/ * FsContext; int /*<<< orphan*/ * FsContext2; } ;
struct TYPE_10__ {struct TYPE_10__* DirectorySearchPattern; } ;
typedef  scalar_t__ PNTFS_FCB ;
typedef  TYPE_2__* PNTFS_CCB ;
typedef  TYPE_3__* PFILE_OBJECT ;
typedef  TYPE_4__* PDEVICE_EXTENSION ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,...) ; 
 int /*<<< orphan*/  ExFreePool (TYPE_2__*) ; 
 int /*<<< orphan*/  NtfsReleaseFCB (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 

NTSTATUS
NtfsCloseFile(PDEVICE_EXTENSION DeviceExt,
              PFILE_OBJECT FileObject)
{
    PNTFS_CCB Ccb;
    PNTFS_FCB Fcb;

    DPRINT("NtfsCloseFile(DeviceExt %p, FileObject %p)\n",
           DeviceExt,
           FileObject);

    Ccb = (PNTFS_CCB)(FileObject->FsContext2);
    Fcb = (PNTFS_FCB)(FileObject->FsContext);

    DPRINT("Ccb %p\n", Ccb);
    if (Ccb == NULL)
    {
        return STATUS_SUCCESS;
    }

    FileObject->FsContext2 = NULL;
    FileObject->FsContext = NULL;
    FileObject->SectionObjectPointer = NULL;
    DeviceExt->OpenHandleCount--;

    if (FileObject->FileName.Buffer)
    {
        // This a FO, that was created outside from FSD.
        // Some FO's are created with IoCreateStreamFileObject() insid from FSD.
        // This FO's don't have a FileName.
        NtfsReleaseFCB(DeviceExt, Fcb);
    }

    if (Ccb->DirectorySearchPattern)
    {
        ExFreePool(Ccb->DirectorySearchPattern);
    }

    ExFreePool(Ccb);

    return STATUS_SUCCESS;
}