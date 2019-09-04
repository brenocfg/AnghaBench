#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_11__ ;

/* Type definitions */
typedef  scalar_t__ ULONG ;
struct TYPE_24__ {int /*<<< orphan*/  DirResource; } ;
struct TYPE_23__ {TYPE_6__* Stack; TYPE_3__* Irp; TYPE_11__* DeviceObject; int /*<<< orphan*/  Flags; } ;
struct TYPE_20__ {int FsInformationClass; scalar_t__ Length; } ;
struct TYPE_21__ {TYPE_4__ QueryVolume; } ;
struct TYPE_22__ {TYPE_5__ Parameters; } ;
struct TYPE_18__ {scalar_t__ Information; } ;
struct TYPE_17__ {int SystemBuffer; } ;
struct TYPE_19__ {TYPE_2__ IoStatus; TYPE_1__ AssociatedIrp; } ;
struct TYPE_16__ {scalar_t__ DeviceExtension; } ;
typedef  int PVOID ;
typedef  TYPE_7__* PVFAT_IRP_CONTEXT ;
typedef  TYPE_8__* PDEVICE_EXTENSION ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int FS_INFORMATION_CLASS ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (TYPE_7__*) ; 
 int /*<<< orphan*/  BooleanFlagOn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT (char*,...) ; 
 int /*<<< orphan*/  DPRINT1 (char*) ; 
 int /*<<< orphan*/  ExAcquireResourceSharedLite (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExReleaseResourceLite (int /*<<< orphan*/ *) ; 
#define  FileFsAttributeInformation 132 
#define  FileFsDeviceInformation 131 
#define  FileFsFullSizeInformation 130 
#define  FileFsSizeInformation 129 
#define  FileFsVolumeInformation 128 
 int /*<<< orphan*/  FsdGetFsAttributeInformation (scalar_t__,int,scalar_t__*) ; 
 int /*<<< orphan*/  FsdGetFsDeviceInformation (TYPE_11__*,int,scalar_t__*) ; 
 int /*<<< orphan*/  FsdGetFsFullSizeInformation (TYPE_11__*,int,scalar_t__*) ; 
 int /*<<< orphan*/  FsdGetFsSizeInformation (TYPE_11__*,int,scalar_t__*) ; 
 int /*<<< orphan*/  FsdGetFsVolumeInformation (TYPE_11__*,int,scalar_t__*) ; 
 int /*<<< orphan*/  IRPCONTEXT_CANWAIT ; 
 int /*<<< orphan*/  STATUS_NOT_SUPPORTED ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  VfatMarkIrpContextForQueue (TYPE_7__*) ; 

NTSTATUS
VfatQueryVolumeInformation(
    PVFAT_IRP_CONTEXT IrpContext)
{
    FS_INFORMATION_CLASS FsInformationClass;
    NTSTATUS RC = STATUS_SUCCESS;
    PVOID SystemBuffer;
    ULONG BufferLength;

    /* PRECONDITION */
    ASSERT(IrpContext);

    DPRINT("VfatQueryVolumeInformation(IrpContext %p)\n", IrpContext);

    if (!ExAcquireResourceSharedLite(&((PDEVICE_EXTENSION)IrpContext->DeviceObject->DeviceExtension)->DirResource,
                                     BooleanFlagOn(IrpContext->Flags, IRPCONTEXT_CANWAIT)))
    {
        DPRINT1("DirResource failed!\n");
        return VfatMarkIrpContextForQueue(IrpContext);
    }

    /* INITIALIZATION */
    FsInformationClass = IrpContext->Stack->Parameters.QueryVolume.FsInformationClass;
    BufferLength = IrpContext->Stack->Parameters.QueryVolume.Length;
    SystemBuffer = IrpContext->Irp->AssociatedIrp.SystemBuffer;

    DPRINT("FsInformationClass %d\n", FsInformationClass);
    DPRINT("SystemBuffer %p\n", SystemBuffer);

    switch (FsInformationClass)
    {
        case FileFsVolumeInformation:
            RC = FsdGetFsVolumeInformation(IrpContext->DeviceObject,
                                           SystemBuffer,
                                           &BufferLength);
            break;

        case FileFsAttributeInformation:
            RC = FsdGetFsAttributeInformation(IrpContext->DeviceObject->DeviceExtension,
                                              SystemBuffer,
                                              &BufferLength);
            break;

        case FileFsSizeInformation:
            RC = FsdGetFsSizeInformation(IrpContext->DeviceObject,
                                         SystemBuffer,
                                         &BufferLength);
            break;

        case FileFsDeviceInformation:
            RC = FsdGetFsDeviceInformation(IrpContext->DeviceObject,
                                           SystemBuffer,
                                           &BufferLength);
            break;

        case FileFsFullSizeInformation:
            RC = FsdGetFsFullSizeInformation(IrpContext->DeviceObject,
                                             SystemBuffer,
                                             &BufferLength);
            break;

        default:
            RC = STATUS_NOT_SUPPORTED;
    }

    ExReleaseResourceLite(&((PDEVICE_EXTENSION)IrpContext->DeviceObject->DeviceExtension)->DirResource);

    IrpContext->Irp->IoStatus.Information =
        IrpContext->Stack->Parameters.QueryVolume.Length - BufferLength;

    return RC;
}