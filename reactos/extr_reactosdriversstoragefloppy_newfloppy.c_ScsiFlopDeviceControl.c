#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_82__   TYPE_9__ ;
typedef  struct TYPE_81__   TYPE_8__ ;
typedef  struct TYPE_80__   TYPE_7__ ;
typedef  struct TYPE_79__   TYPE_6__ ;
typedef  struct TYPE_78__   TYPE_5__ ;
typedef  struct TYPE_77__   TYPE_4__ ;
typedef  struct TYPE_76__   TYPE_45__ ;
typedef  struct TYPE_75__   TYPE_44__ ;
typedef  struct TYPE_74__   TYPE_3__ ;
typedef  struct TYPE_73__   TYPE_32__ ;
typedef  struct TYPE_72__   TYPE_2__ ;
typedef  struct TYPE_71__   TYPE_23__ ;
typedef  struct TYPE_70__   TYPE_22__ ;
typedef  struct TYPE_69__   TYPE_21__ ;
typedef  struct TYPE_68__   TYPE_20__ ;
typedef  struct TYPE_67__   TYPE_1__ ;
typedef  struct TYPE_66__   TYPE_19__ ;
typedef  struct TYPE_65__   TYPE_18__ ;
typedef  struct TYPE_64__   TYPE_17__ ;
typedef  struct TYPE_63__   TYPE_16__ ;
typedef  struct TYPE_62__   TYPE_15__ ;
typedef  struct TYPE_61__   TYPE_13__ ;
typedef  struct TYPE_60__   TYPE_12__ ;
typedef  struct TYPE_59__   TYPE_11__ ;
typedef  struct TYPE_58__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VERIFY_INFORMATION ;
typedef  int /*<<< orphan*/  USHORT ;
typedef  int ULONGLONG ;
typedef  size_t ULONG ;
typedef  size_t UCHAR ;
struct TYPE_82__ {int QuadPart; } ;
struct TYPE_80__ {int IoControlCode; int InputBufferLength; int OutputBufferLength; } ;
struct TYPE_81__ {TYPE_7__ DeviceIoControl; } ;
struct TYPE_79__ {TYPE_12__* SystemBuffer; } ;
struct TYPE_78__ {int Information; scalar_t__ Status; } ;
struct TYPE_77__ {int /*<<< orphan*/  BusType; } ;
struct TYPE_76__ {int /*<<< orphan*/  BytesPerSector; int /*<<< orphan*/  SectorsPerTrack; int /*<<< orphan*/  NumberOfHeads; int /*<<< orphan*/  MaximumTrack; int /*<<< orphan*/  MediaType; } ;
struct TYPE_75__ {scalar_t__ HighestDriveMediaType; scalar_t__ LowestDriveMediaType; } ;
struct TYPE_74__ {int /*<<< orphan*/  HighPart; int /*<<< orphan*/  LowPart; } ;
struct TYPE_73__ {int /*<<< orphan*/  MediaType; } ;
struct TYPE_72__ {int /*<<< orphan*/  TransferBlocksLsb; int /*<<< orphan*/  TransferBlocksMsb; int /*<<< orphan*/  LogicalBlockByte3; int /*<<< orphan*/  LogicalBlockByte2; int /*<<< orphan*/  LogicalBlockByte1; int /*<<< orphan*/  LogicalBlockByte0; int /*<<< orphan*/  OperationCode; } ;
struct TYPE_71__ {int QuadPart; } ;
struct TYPE_70__ {TYPE_2__ CDB10; } ;
struct TYPE_69__ {TYPE_17__* DeviceExtension; } ;
struct TYPE_68__ {int /*<<< orphan*/  BytesPerSector; int /*<<< orphan*/  SectorsPerTrack; int /*<<< orphan*/  TracksPerCylinder; TYPE_3__ Cylinders; int /*<<< orphan*/  MediaType; } ;
struct TYPE_67__ {int QuadPart; } ;
struct TYPE_66__ {int /*<<< orphan*/  MediaType; int /*<<< orphan*/  StartHeadNumber; int /*<<< orphan*/  StartCylinderNumber; } ;
struct TYPE_65__ {int /*<<< orphan*/  Byte0; int /*<<< orphan*/  Byte1; int /*<<< orphan*/  Byte2; int /*<<< orphan*/  Byte3; } ;
struct TYPE_58__ {TYPE_1__ StartingOffset; TYPE_9__ PartitionLength; } ;
struct TYPE_64__ {int SectorShift; int TimeOutValue; TYPE_32__ DiskGeometry; TYPE_4__* AdapterDescriptor; TYPE_10__ CommonExtension; } ;
struct TYPE_63__ {int /*<<< orphan*/  Flags; TYPE_8__ Parameters; } ;
struct TYPE_62__ {TYPE_5__ IoStatus; TYPE_6__ AssociatedIrp; } ;
struct TYPE_61__ {int CdbLength; int TimeOutValue; int DeviceSpecificParameter; scalar_t__ Cdb; } ;
struct TYPE_59__ {int QuadPart; } ;
struct TYPE_60__ {int Length; TYPE_11__ StartingOffset; } ;
typedef  TYPE_12__* PVERIFY_INFORMATION ;
typedef  TYPE_13__* PSCSI_REQUEST_BLOCK ;
typedef  TYPE_13__* PMODE_PARAMETER_HEADER ;
typedef  TYPE_15__* PIRP ;
typedef  TYPE_16__* PIO_STACK_LOCATION ;
typedef  TYPE_17__* PFUNCTIONAL_DEVICE_EXTENSION ;
typedef  TYPE_18__* PFOUR_BYTE ;
typedef  TYPE_19__* PFORMAT_PARAMETERS ;
typedef  TYPE_20__* PDISK_GEOMETRY ;
typedef  TYPE_21__* PDEVICE_OBJECT ;
typedef  int /*<<< orphan*/  PCHAR ;
typedef  TYPE_22__* PCDB ;
typedef  scalar_t__ NTSTATUS ;
typedef  int /*<<< orphan*/  MODE_PARAMETER_HEADER ;
typedef  TYPE_23__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  KIRQL ;
typedef  int /*<<< orphan*/  FORMAT_PARAMETERS ;
typedef  scalar_t__ DRIVE_MEDIA_TYPE ;
typedef  int /*<<< orphan*/  DISK_GEOMETRY ;

/* Variables and functions */
 int /*<<< orphan*/  BusTypeUsb ; 
 int /*<<< orphan*/  ClassCompleteRequest (TYPE_21__*,TYPE_15__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ClassDeviceControl (TYPE_21__*,TYPE_15__*) ; 
 size_t ClassModeSense (TYPE_21__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ClassReleaseRemoveLock (TYPE_21__*,TYPE_15__*) ; 
 scalar_t__ ClassSendSrbAsynchronous (TYPE_21__*,TYPE_13__*,TYPE_15__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DISPATCH_LEVEL ; 
 size_t DRIVE_TYPE_NONE ; 
 int /*<<< orphan*/  DebugPrint (int) ; 
 size_t DetermineDriveType (TYPE_21__*) ; 
 scalar_t__ DetermineMediaType (TYPE_21__*) ; 
 TYPE_45__* DriveMediaConstants ; 
 TYPE_44__* DriveMediaLimits ; 
 TYPE_13__* ExAllocatePool (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExFreePool (TYPE_13__*) ; 
 int /*<<< orphan*/  F3_120M_512 ; 
 int /*<<< orphan*/  F3_20Pt8_512 ; 
 int /*<<< orphan*/  F3_32M_512 ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FlCheckFormatParameters (TYPE_21__*,TYPE_19__*) ; 
 scalar_t__ FlopticalFormatMedia (TYPE_21__*,TYPE_19__*) ; 
 scalar_t__ FormatMedia (TYPE_21__*,int /*<<< orphan*/ ) ; 
#define  IOCTL_DISK_FORMAT_TRACKS 133 
#define  IOCTL_DISK_GET_DRIVE_GEOMETRY 132 
#define  IOCTL_DISK_GET_MEDIA_TYPES 131 
#define  IOCTL_DISK_GET_PARTITION_INFO 130 
#define  IOCTL_DISK_IS_WRITABLE 129 
#define  IOCTL_DISK_VERIFY 128 
 TYPE_16__* IoGetCurrentIrpStackLocation (TYPE_15__*) ; 
 scalar_t__ IoIsErrorUserInduced (scalar_t__) ; 
 int /*<<< orphan*/  IoSetHardErrorOrVerifyDevice (TYPE_15__*,TYPE_21__*) ; 
 int /*<<< orphan*/  KeLowerIrql (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KeRaiseIrql (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MODE_DATA_SIZE ; 
 int MODE_DSP_WRITE_PROTECT ; 
 int /*<<< orphan*/  MODE_SENSE_RETURN_ALL ; 
 int /*<<< orphan*/  NOTHING ; 
 int /*<<< orphan*/  NT_SUCCESS (scalar_t__) ; 
 int /*<<< orphan*/  NonPagedPoolNx ; 
 int /*<<< orphan*/  NonPagedPoolNxCacheAligned ; 
 int /*<<< orphan*/  RtlMoveMemory (TYPE_12__*,TYPE_32__*,int) ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_13__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCSIOP_VERIFY ; 
 int /*<<< orphan*/  SCSI_REQUEST_BLOCK_SIZE ; 
 int /*<<< orphan*/  SL_OVERRIDE_VERIFY_VOLUME ; 
 scalar_t__ STATUS_BUFFER_OVERFLOW ; 
 scalar_t__ STATUS_BUFFER_TOO_SMALL ; 
 scalar_t__ STATUS_INFO_LENGTH_MISMATCH ; 
 scalar_t__ STATUS_INSUFFICIENT_RESOURCES ; 
 scalar_t__ STATUS_INVALID_DEVICE_REQUEST ; 
 scalar_t__ STATUS_INVALID_PARAMETER ; 
 scalar_t__ STATUS_IO_DEVICE_ERROR ; 
 scalar_t__ STATUS_MEDIA_WRITE_PROTECTED ; 
 scalar_t__ STATUS_NONEXISTENT_SECTOR ; 
 scalar_t__ STATUS_SUCCESS ; 
 scalar_t__ STATUS_UNRECOGNIZED_MEDIA ; 
 scalar_t__ STATUS_VERIFY_REQUIRED ; 
 scalar_t__ TEST_FLAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ USBFlopFormatTracks (TYPE_21__*,TYPE_15__*) ; 
 scalar_t__ USBFlopGetMediaTypes (TYPE_21__*,TYPE_15__*) ; 

NTSTATUS
#ifdef __REACTOS__
NTAPI
#endif
ScsiFlopDeviceControl(
    PDEVICE_OBJECT DeviceObject,
    PIRP Irp
    )

/*++

Routine Description:

Arguments:

Return Value:

    Status is returned.

--*/

{
    KIRQL currentIrql;
    PIO_STACK_LOCATION irpStack = IoGetCurrentIrpStackLocation(Irp);
    PFUNCTIONAL_DEVICE_EXTENSION fdoExtension = DeviceObject->DeviceExtension;
    PSCSI_REQUEST_BLOCK srb;
    PCDB cdb;
    NTSTATUS status;
    PDISK_GEOMETRY outputBuffer;
    ULONG outputBufferLength;
    ULONG i;
    DRIVE_MEDIA_TYPE lowestDriveMediaType;
    DRIVE_MEDIA_TYPE highestDriveMediaType;
    PFORMAT_PARAMETERS formatParameters;
    PMODE_PARAMETER_HEADER modeData;
    ULONG length;

    //
    // Initialize the information field
    //
    Irp->IoStatus.Information = 0;

#ifndef __REACTOS__
    srb = ExAllocatePool(NonPagedPoolNx, SCSI_REQUEST_BLOCK_SIZE);
#else
    srb = ExAllocatePool(NonPagedPool, SCSI_REQUEST_BLOCK_SIZE);
#endif

    if (srb == NULL) {

        Irp->IoStatus.Status = STATUS_INSUFFICIENT_RESOURCES;
        if (IoIsErrorUserInduced(Irp->IoStatus.Status)) {

            IoSetHardErrorOrVerifyDevice(Irp, DeviceObject);
        }

        KeRaiseIrql(DISPATCH_LEVEL, &currentIrql);
        ClassReleaseRemoveLock(DeviceObject, Irp);
        ClassCompleteRequest(DeviceObject, Irp, 0);
        KeLowerIrql(currentIrql);

        return(STATUS_INSUFFICIENT_RESOURCES);
    }

    //
    // Write zeros to Srb.
    //

    RtlZeroMemory(srb, SCSI_REQUEST_BLOCK_SIZE);

    cdb = (PCDB)srb->Cdb;

    switch (irpStack->Parameters.DeviceIoControl.IoControlCode) {


    case IOCTL_DISK_VERIFY: {

       PVERIFY_INFORMATION verifyInfo = Irp->AssociatedIrp.SystemBuffer;
       LARGE_INTEGER byteOffset;
       ULONG         sectorOffset;
       USHORT        sectorCount;

       //
       // Validate buffer length.
       //

       if (irpStack->Parameters.DeviceIoControl.InputBufferLength <
           sizeof(VERIFY_INFORMATION)) {

           status = STATUS_INFO_LENGTH_MISMATCH;
           break;
       }

       //
       // Perform a bounds check on the sector range
       //
       if ((verifyInfo->StartingOffset.QuadPart > fdoExtension->CommonExtension.PartitionLength.QuadPart) ||
           (verifyInfo->StartingOffset.QuadPart < 0))
       {
           status = STATUS_NONEXISTENT_SECTOR;
           break;
       }
       else
       {
           ULONGLONG bytesRemaining = fdoExtension->CommonExtension.PartitionLength.QuadPart - verifyInfo->StartingOffset.QuadPart;

           if ((ULONGLONG)verifyInfo->Length > bytesRemaining)
           {
               status = STATUS_NONEXISTENT_SECTOR;
               break;
           }
       }

       //
       // Verify sectors
       //

       srb->CdbLength = 10;

       cdb->CDB10.OperationCode = SCSIOP_VERIFY;

       //
       // Add disk offset to starting sector.
       //

       byteOffset.QuadPart = fdoExtension->CommonExtension.StartingOffset.QuadPart +
                       verifyInfo->StartingOffset.QuadPart;

       //
       // Convert byte offset to sector offset.
       //

       sectorOffset = (ULONG)(byteOffset.QuadPart >> fdoExtension->SectorShift);

       //
       // Convert ULONG byte count to USHORT sector count.
       //

       sectorCount = (USHORT)(verifyInfo->Length >> fdoExtension->SectorShift);

       //
       // Move little endian values into CDB in big endian format.
       //

       cdb->CDB10.LogicalBlockByte0 = ((PFOUR_BYTE)&sectorOffset)->Byte3;
       cdb->CDB10.LogicalBlockByte1 = ((PFOUR_BYTE)&sectorOffset)->Byte2;
       cdb->CDB10.LogicalBlockByte2 = ((PFOUR_BYTE)&sectorOffset)->Byte1;
       cdb->CDB10.LogicalBlockByte3 = ((PFOUR_BYTE)&sectorOffset)->Byte0;

       cdb->CDB10.TransferBlocksMsb = ((PFOUR_BYTE)&sectorCount)->Byte1;
       cdb->CDB10.TransferBlocksLsb = ((PFOUR_BYTE)&sectorCount)->Byte0;

       //
       // The verify command is used by the NT FORMAT utility and
       // requests are sent down for 5% of the volume size. The
       // request timeout value is calculated based on the number of
       // sectors verified.
       //

       srb->TimeOutValue = ((sectorCount + 0x7F) >> 7) *
                             fdoExtension->TimeOutValue;

       status = ClassSendSrbAsynchronous(DeviceObject,
                                         srb,
                                         Irp,
                                         NULL,
                                         0,
                                         FALSE);
       return(status);

    }

    case IOCTL_DISK_GET_PARTITION_INFO: {

        if (fdoExtension->AdapterDescriptor->BusType == BusTypeUsb) {

            USBFlopGetMediaTypes(DeviceObject, NULL);

            // Don't need to propagate any error if one occurs
            //
            status = STATUS_SUCCESS;

        } else {

            status = DetermineMediaType(DeviceObject);
        }

        if (!NT_SUCCESS(status)) {
            // so will propogate error
            NOTHING;
        } else if (fdoExtension->DiskGeometry.MediaType == F3_120M_512) {
            //so that the format code will not try to partition it.
            status = STATUS_INVALID_DEVICE_REQUEST;
        } else {
           //
           // Free the Srb, since it is not needed.
           //

           ExFreePool(srb);

           //
           // Pass the request to the common device control routine.
           //

           return(ClassDeviceControl(DeviceObject, Irp));
        }
        break;
    }

    case IOCTL_DISK_GET_DRIVE_GEOMETRY: {

        DebugPrint((3,"ScsiDeviceIoControl: Get drive geometry\n"));

        if (fdoExtension->AdapterDescriptor->BusType == BusTypeUsb)
        {
            status = USBFlopGetMediaTypes(DeviceObject,
                                          Irp);
            break;
        }

        //
        // If there's not enough room to write the
        // data, then fail the request.
        //

        if ( irpStack->Parameters.DeviceIoControl.OutputBufferLength <
            sizeof( DISK_GEOMETRY ) ) {

            status = STATUS_INVALID_PARAMETER;
            break;
        }

        status = DetermineMediaType(DeviceObject);

        if (!NT_SUCCESS(status)) {

            Irp->IoStatus.Information = 0;
            Irp->IoStatus.Status = status;

        } else {

            //
            // Copy drive geometry information from device extension.
            //

            RtlMoveMemory(Irp->AssociatedIrp.SystemBuffer,
                          &(fdoExtension->DiskGeometry),
                          sizeof(DISK_GEOMETRY));

            Irp->IoStatus.Information = sizeof(DISK_GEOMETRY);
            status = STATUS_SUCCESS;

        }

        break;
    }

    case IOCTL_DISK_GET_MEDIA_TYPES: {

        if (fdoExtension->AdapterDescriptor->BusType == BusTypeUsb)
        {
            status = USBFlopGetMediaTypes(DeviceObject,
                                          Irp);
            break;
        }

        i = DetermineDriveType(DeviceObject);

        if (i == DRIVE_TYPE_NONE) {
            status = STATUS_UNRECOGNIZED_MEDIA;
            break;
        }

        lowestDriveMediaType = DriveMediaLimits[i].LowestDriveMediaType;
        highestDriveMediaType = DriveMediaLimits[i].HighestDriveMediaType;

        outputBufferLength =
        irpStack->Parameters.DeviceIoControl.OutputBufferLength;

        //
        // Make sure that the input buffer has enough room to return
        // at least one descriptions of a supported media type.
        //

        if ( outputBufferLength < ( sizeof( DISK_GEOMETRY ) ) ) {

            status = STATUS_BUFFER_TOO_SMALL;
            break;
        }

        //
        // Assume success, although we might modify it to a buffer
        // overflow warning below (if the buffer isn't big enough
        // to hold ALL of the media descriptions).
        //

        status = STATUS_SUCCESS;

        if (outputBufferLength < ( sizeof( DISK_GEOMETRY ) *
            ( highestDriveMediaType - lowestDriveMediaType + 1 ) ) ) {

            //
            // The buffer is too small for all of the descriptions;
            // calculate what CAN fit in the buffer.
            //

            status = STATUS_BUFFER_OVERFLOW;

            highestDriveMediaType = (DRIVE_MEDIA_TYPE)( ( lowestDriveMediaType - 1 ) +
                ( outputBufferLength /
                sizeof( DISK_GEOMETRY ) ) );
        }

        outputBuffer = (PDISK_GEOMETRY) Irp->AssociatedIrp.SystemBuffer;

        for (i = (UCHAR)lowestDriveMediaType;i <= (UCHAR)highestDriveMediaType;i++ ) {

             outputBuffer->MediaType = DriveMediaConstants[i].MediaType;
             outputBuffer->Cylinders.LowPart =
                 DriveMediaConstants[i].MaximumTrack + 1;
             outputBuffer->Cylinders.HighPart = 0;
             outputBuffer->TracksPerCylinder =
                 DriveMediaConstants[i].NumberOfHeads;
             outputBuffer->SectorsPerTrack =
                 DriveMediaConstants[i].SectorsPerTrack;
             outputBuffer->BytesPerSector =
                 DriveMediaConstants[i].BytesPerSector;
             outputBuffer++;

             Irp->IoStatus.Information += sizeof( DISK_GEOMETRY );
        }

        break;
    }

    case IOCTL_DISK_FORMAT_TRACKS: {

        if (fdoExtension->AdapterDescriptor->BusType == BusTypeUsb)
        {
            status = USBFlopFormatTracks(DeviceObject,
                                         Irp);
            break;
        }

        //
        // Make sure that we got all the necessary format parameters.
        //

        if ( irpStack->Parameters.DeviceIoControl.InputBufferLength <sizeof( FORMAT_PARAMETERS ) ) {

            status = STATUS_INVALID_PARAMETER;
            break;
        }

        formatParameters = (PFORMAT_PARAMETERS) Irp->AssociatedIrp.SystemBuffer;

        //
        // Make sure the parameters we got are reasonable.
        //

        if ( !FlCheckFormatParameters(DeviceObject, formatParameters)) {

            status = STATUS_INVALID_PARAMETER;
            break;
        }

        //
        // If this request is for a 20.8 MB floppy then call a special
        // floppy format routine.
        //

        if (formatParameters->MediaType == F3_20Pt8_512) {
            status = FlopticalFormatMedia(DeviceObject,
                                          formatParameters
                                          );

            break;
        }

        //
        // All the work is done in the pass.  If this is not the first pass,
        // then complete the request and return;
        //

        if (formatParameters->StartCylinderNumber != 0 || formatParameters->StartHeadNumber != 0) {

            status = STATUS_SUCCESS;
            break;
        }

        status = FormatMedia( DeviceObject, formatParameters->MediaType);
        break;
    }

    case IOCTL_DISK_IS_WRITABLE: {

        if ((fdoExtension->DiskGeometry.MediaType) == F3_32M_512) {

            //
            // 32MB media is READ ONLY. Just return
            // STATUS_MEDIA_WRITE_PROTECTED
            //

            status = STATUS_MEDIA_WRITE_PROTECTED;

            break;
        }

        //
        // Determine if the device is writable.
        //

#ifndef __REACTOS__
        modeData = ExAllocatePool(NonPagedPoolNxCacheAligned, MODE_DATA_SIZE);
#else
        modeData = ExAllocatePool(NonPagedPoolCacheAligned, MODE_DATA_SIZE);
#endif

        if (modeData == NULL) {
            status = STATUS_INSUFFICIENT_RESOURCES;
            break;
        }

        RtlZeroMemory(modeData, MODE_DATA_SIZE);

        length = ClassModeSense(DeviceObject,
                                (PCHAR) modeData,
                                MODE_DATA_SIZE,
                                MODE_SENSE_RETURN_ALL);

        if (length < sizeof(MODE_PARAMETER_HEADER)) {

            //
            // Retry the request in case of a check condition.
            //

            length = ClassModeSense(DeviceObject,
                                    (PCHAR) modeData,
                                    MODE_DATA_SIZE,
                                    MODE_SENSE_RETURN_ALL);

            if (length < sizeof(MODE_PARAMETER_HEADER)) {
                status = STATUS_IO_DEVICE_ERROR;
                ExFreePool(modeData);
                break;
            }
        }

        if (modeData->DeviceSpecificParameter & MODE_DSP_WRITE_PROTECT) {
            status = STATUS_MEDIA_WRITE_PROTECTED;
        } else {
            status = STATUS_SUCCESS;
        }

        DebugPrint((2,"IOCTL_DISK_IS_WRITABLE returns %08X\n", status));

        ExFreePool(modeData);
        break;
    }

    default: {

        DebugPrint((3,"ScsiIoDeviceControl: Unsupported device IOCTL\n"));

        //
        // Free the Srb, since it is not needed.
        //

        ExFreePool(srb);

        //
        // Pass the request to the common device control routine.
        //

        return(ClassDeviceControl(DeviceObject, Irp));

        break;
    }

    } // end switch( ...

    //
    // Check if SL_OVERRIDE_VERIFY_VOLUME flag is set in the IRP.
    // If so, do not return STATUS_VERIFY_REQUIRED
    //
    if ((status == STATUS_VERIFY_REQUIRED) &&
        (TEST_FLAG(irpStack->Flags, SL_OVERRIDE_VERIFY_VOLUME))) {

        status = STATUS_IO_DEVICE_ERROR;

    }

    Irp->IoStatus.Status = status;

    if (!NT_SUCCESS(status) && IoIsErrorUserInduced(status)) {

        IoSetHardErrorOrVerifyDevice(Irp, DeviceObject);
    }

    KeRaiseIrql(DISPATCH_LEVEL, &currentIrql);
    ClassReleaseRemoveLock(DeviceObject, Irp);
    ClassCompleteRequest(DeviceObject, Irp, 0);
    KeLowerIrql(currentIrql);

    ExFreePool(srb);

    return status;

}