#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG ;
struct TYPE_25__ {int /*<<< orphan*/  DirResource; } ;
struct TYPE_24__ {TYPE_9__* DeviceExtension; } ;
struct TYPE_18__ {int FsInformationClass; scalar_t__ Length; } ;
struct TYPE_19__ {TYPE_2__ QueryVolume; } ;
struct TYPE_23__ {TYPE_3__ Parameters; } ;
struct TYPE_20__ {scalar_t__ Information; } ;
struct TYPE_17__ {int SystemBuffer; } ;
struct TYPE_22__ {TYPE_4__ IoStatus; TYPE_1__ AssociatedIrp; } ;
struct TYPE_21__ {int /*<<< orphan*/  Flags; TYPE_7__* Stack; TYPE_8__* DeviceObject; TYPE_6__* Irp; } ;
typedef  int PVOID ;
typedef  TYPE_5__* PNTFS_IRP_CONTEXT ;
typedef  TYPE_6__* PIRP ;
typedef  TYPE_7__* PIO_STACK_LOCATION ;
typedef  TYPE_8__* PDEVICE_OBJECT ;
typedef  TYPE_9__* PDEVICE_EXTENSION ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int FS_INFORMATION_CLASS ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (TYPE_5__*) ; 
 int /*<<< orphan*/  BooleanFlagOn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT (char*,...) ; 
 int /*<<< orphan*/  ExAcquireResourceSharedLite (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExReleaseResourceLite (int /*<<< orphan*/ *) ; 
#define  FileFsAttributeInformation 131 
#define  FileFsDeviceInformation 130 
#define  FileFsSizeInformation 129 
#define  FileFsVolumeInformation 128 
 int /*<<< orphan*/  IRPCONTEXT_CANWAIT ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtfsGetFsAttributeInformation (TYPE_9__*,int,scalar_t__*) ; 
 int /*<<< orphan*/  NtfsGetFsDeviceInformation (TYPE_8__*,int,scalar_t__*) ; 
 int /*<<< orphan*/  NtfsGetFsSizeInformation (TYPE_8__*,int,scalar_t__*) ; 
 int /*<<< orphan*/  NtfsGetFsVolumeInformation (TYPE_8__*,int,scalar_t__*) ; 
 int /*<<< orphan*/  NtfsMarkIrpContextForQueue (TYPE_5__*) ; 
 int /*<<< orphan*/  RtlZeroMemory (int,scalar_t__) ; 
 int /*<<< orphan*/  STATUS_NOT_SUPPORTED ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 

NTSTATUS
NtfsQueryVolumeInformation(PNTFS_IRP_CONTEXT IrpContext)
{
    PIRP Irp;
    PDEVICE_OBJECT DeviceObject;
    FS_INFORMATION_CLASS FsInformationClass;
    PIO_STACK_LOCATION Stack;
    NTSTATUS Status = STATUS_SUCCESS;
    PVOID SystemBuffer;
    ULONG BufferLength;
    PDEVICE_EXTENSION DeviceExt;

    DPRINT("NtfsQueryVolumeInformation() called\n");

    ASSERT(IrpContext);

    Irp = IrpContext->Irp;
    DeviceObject = IrpContext->DeviceObject;
    DeviceExt = DeviceObject->DeviceExtension;
    Stack = IrpContext->Stack;

    if (!ExAcquireResourceSharedLite(&DeviceExt->DirResource,
                                     BooleanFlagOn(IrpContext->Flags, IRPCONTEXT_CANWAIT)))
    {
        return NtfsMarkIrpContextForQueue(IrpContext);
    }

    FsInformationClass = Stack->Parameters.QueryVolume.FsInformationClass;
    BufferLength = Stack->Parameters.QueryVolume.Length;
    SystemBuffer = Irp->AssociatedIrp.SystemBuffer;
    RtlZeroMemory(SystemBuffer, BufferLength);

    DPRINT("FsInformationClass %d\n", FsInformationClass);
    DPRINT("SystemBuffer %p\n", SystemBuffer);

    switch (FsInformationClass)
    {
        case FileFsVolumeInformation:
            Status = NtfsGetFsVolumeInformation(DeviceObject,
                                                SystemBuffer,
                                                &BufferLength);
            break;

        case FileFsAttributeInformation:
            Status = NtfsGetFsAttributeInformation(DeviceObject->DeviceExtension,
                                                   SystemBuffer,
                                                   &BufferLength);
            break;

        case FileFsSizeInformation:
            Status = NtfsGetFsSizeInformation(DeviceObject,
                                              SystemBuffer,
                                              &BufferLength);
            break;

        case FileFsDeviceInformation:
            Status = NtfsGetFsDeviceInformation(DeviceObject,
                                                SystemBuffer,
                                                &BufferLength);
            break;

        default:
            Status = STATUS_NOT_SUPPORTED;
    }

    ExReleaseResourceLite(&DeviceExt->DirResource);

    if (NT_SUCCESS(Status))
        Irp->IoStatus.Information =
            Stack->Parameters.QueryVolume.Length - BufferLength;
    else
        Irp->IoStatus.Information = 0;

    return Status;
}