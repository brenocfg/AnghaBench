#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_47__   TYPE_9__ ;
typedef  struct TYPE_46__   TYPE_8__ ;
typedef  struct TYPE_45__   TYPE_7__ ;
typedef  struct TYPE_44__   TYPE_6__ ;
typedef  struct TYPE_43__   TYPE_5__ ;
typedef  struct TYPE_42__   TYPE_4__ ;
typedef  struct TYPE_41__   TYPE_3__ ;
typedef  struct TYPE_40__   TYPE_2__ ;
typedef  struct TYPE_39__   TYPE_1__ ;
typedef  struct TYPE_38__   TYPE_17__ ;
typedef  struct TYPE_37__   TYPE_16__ ;
typedef  struct TYPE_36__   TYPE_15__ ;
typedef  struct TYPE_35__   TYPE_14__ ;
typedef  struct TYPE_34__   TYPE_13__ ;
typedef  struct TYPE_33__   TYPE_12__ ;
typedef  struct TYPE_32__   TYPE_11__ ;

/* Type definitions */
typedef  scalar_t__ ULONG_PTR ;
typedef  int ULONGLONG ;
typedef  int ULONG ;
struct TYPE_47__ {int /*<<< orphan*/  Flags; int /*<<< orphan*/  MinorVersion; int /*<<< orphan*/  MajorVersion; } ;
struct TYPE_46__ {int SectorCount; int MftLocation; int MftMirrLocation; int SerialNumber; int ClustersPerMftRecord; int ClustersPerIndexRecord; } ;
struct TYPE_45__ {int BytesPerSector; int SectorsPerCluster; } ;
struct TYPE_44__ {scalar_t__ ValueLength; scalar_t__ ValueOffset; } ;
struct TYPE_42__ {int QuadPart; } ;
struct TYPE_43__ {TYPE_4__ FileSize; TYPE_4__ AllocationSize; TYPE_4__ ValidDataLength; } ;
struct TYPE_40__ {int LowPart; } ;
struct TYPE_41__ {int QuadPart; TYPE_2__ u; } ;
struct TYPE_39__ {int QuadPart; } ;
struct TYPE_38__ {int BytesPerSector; } ;
struct TYPE_37__ {TYPE_8__ EBPB; TYPE_7__ BPB; } ;
struct TYPE_32__ {int BytesPerSector; int SectorsPerCluster; int BytesPerCluster; int SectorCount; int ClusterCount; int SerialNumber; int BytesPerFileRecord; int BytesPerIndexRecord; char* VolumeLabel; int /*<<< orphan*/  MftZoneReservation; int /*<<< orphan*/  Flags; int /*<<< orphan*/  MinorVersion; int /*<<< orphan*/  MajorVersion; scalar_t__ VolumeLabelLength; TYPE_3__ MftStart; TYPE_1__ MftMirrStart; } ;
struct TYPE_36__ {int /*<<< orphan*/  FileRecLookasideList; TYPE_12__* VolumeFcb; TYPE_11__ NtfsInfo; int /*<<< orphan*/ * MasterFileTable; int /*<<< orphan*/  StorageDevice; int /*<<< orphan*/  MftDataOffset; TYPE_14__* MFTContext; } ;
struct TYPE_35__ {TYPE_13__* pRecord; } ;
struct TYPE_34__ {TYPE_6__ Resident; } ;
struct TYPE_33__ {scalar_t__ MFTIndex; TYPE_5__ RFCB; int /*<<< orphan*/  Flags; } ;
typedef  char* PWSTR ;
typedef  TYPE_9__* PVOLINFO_ATTRIBUTE ;
typedef  TYPE_9__* PVOID ;
typedef  TYPE_11__* PNTFS_INFO ;
typedef  TYPE_12__* PNTFS_FCB ;
typedef  TYPE_13__* PNTFS_ATTR_RECORD ;
typedef  TYPE_14__* PNTFS_ATTR_CONTEXT ;
typedef  int /*<<< orphan*/ * PFILE_RECORD_HEADER ;
typedef  int /*<<< orphan*/  PDEVICE_OBJECT ;
typedef  TYPE_15__* PDEVICE_EXTENSION ;
typedef  TYPE_16__* PBOOT_SECTOR ;
typedef  int NTSTATUS ;
typedef  TYPE_17__ DISK_GEOMETRY ;

/* Variables and functions */
 int /*<<< orphan*/  AttributeData ; 
 int AttributeDataLength (TYPE_13__*) ; 
 int /*<<< orphan*/  AttributeVolumeInformation ; 
 int /*<<< orphan*/  AttributeVolumeName ; 
 int /*<<< orphan*/  DPRINT (char*,...) ; 
 int /*<<< orphan*/  DPRINT1 (char*) ; 
 void* ExAllocateFromNPagedLookasideList (int /*<<< orphan*/ *) ; 
 TYPE_16__* ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExDeleteNPagedLookasideList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExFreePool (TYPE_16__*) ; 
 int /*<<< orphan*/  ExFreeToNPagedLookasideList (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExInitializeNPagedLookasideList (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FCB_IS_VOLUME ; 
 int FindAttribute (TYPE_15__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,TYPE_14__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IOCTL_DISK_GET_DRIVE_GEOMETRY ; 
 int /*<<< orphan*/  MAXIMUM_VOLUME_LABEL_LENGTH ; 
 int /*<<< orphan*/  NTFS_FILE_VOLUME ; 
 scalar_t__ NT_SUCCESS (int) ; 
 int /*<<< orphan*/  NonPagedPool ; 
 TYPE_12__* NtfsCreateFCB (char*,int /*<<< orphan*/ *,TYPE_15__*) ; 
 int NtfsDeviceIoControl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_17__*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtfsDumpFileAttributes (TYPE_15__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NtfsQueryMftZoneReservation () ; 
 int NtfsReadSectors (int /*<<< orphan*/ ,int,int,int,TYPE_9__*,int /*<<< orphan*/ ) ; 
 int ReadFileRecord (TYPE_15__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseAttributeContext (TYPE_14__*) ; 
 int /*<<< orphan*/  RtlCopyMemory (char*,TYPE_9__*,scalar_t__) ; 
 int STATUS_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  TAG_FILE_REC ; 
 int /*<<< orphan*/  TAG_NTFS ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ min (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
NTSTATUS
NtfsGetVolumeData(PDEVICE_OBJECT DeviceObject,
                  PDEVICE_EXTENSION DeviceExt)
{
    DISK_GEOMETRY DiskGeometry;
    PFILE_RECORD_HEADER VolumeRecord;
    PVOLINFO_ATTRIBUTE VolumeInfo;
    PBOOT_SECTOR BootSector;
    ULONG Size;
    PNTFS_INFO NtfsInfo = &DeviceExt->NtfsInfo;
    NTSTATUS Status;
    PNTFS_ATTR_CONTEXT AttrCtxt;
    PNTFS_ATTR_RECORD Attribute;
    PNTFS_FCB VolumeFcb;
    PWSTR VolumeNameU;

    DPRINT("NtfsGetVolumeData() called\n");

    Size = sizeof(DISK_GEOMETRY);
    Status = NtfsDeviceIoControl(DeviceObject,
                                 IOCTL_DISK_GET_DRIVE_GEOMETRY,
                                 NULL,
                                 0,
                                 &DiskGeometry,
                                 &Size,
                                 TRUE);
    if (!NT_SUCCESS(Status))
    {
        DPRINT("NtfsDeviceIoControl() failed (Status %lx)\n", Status);
        return Status;
    }

    DPRINT("BytesPerSector: %lu\n", DiskGeometry.BytesPerSector);
    BootSector = ExAllocatePoolWithTag(NonPagedPool,
                                       DiskGeometry.BytesPerSector,
                                       TAG_NTFS);
    if (BootSector == NULL)
    {
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    Status = NtfsReadSectors(DeviceObject,
                             0, /* Partition boot sector */
                             1,
                             DiskGeometry.BytesPerSector,
                             (PVOID)BootSector,
                             TRUE);
    if (!NT_SUCCESS(Status))
    {
        ExFreePool(BootSector);
        return Status;
    }

    /* Read data from the bootsector */
    NtfsInfo->BytesPerSector = BootSector->BPB.BytesPerSector;
    NtfsInfo->SectorsPerCluster = BootSector->BPB.SectorsPerCluster;
    NtfsInfo->BytesPerCluster = BootSector->BPB.BytesPerSector * BootSector->BPB.SectorsPerCluster;
    NtfsInfo->SectorCount = BootSector->EBPB.SectorCount;
    NtfsInfo->ClusterCount = DeviceExt->NtfsInfo.SectorCount / (ULONGLONG)DeviceExt->NtfsInfo.SectorsPerCluster;

    NtfsInfo->MftStart.QuadPart = BootSector->EBPB.MftLocation;
    NtfsInfo->MftMirrStart.QuadPart = BootSector->EBPB.MftMirrLocation;
    NtfsInfo->SerialNumber = BootSector->EBPB.SerialNumber;
    if (BootSector->EBPB.ClustersPerMftRecord > 0)
        NtfsInfo->BytesPerFileRecord = BootSector->EBPB.ClustersPerMftRecord * NtfsInfo->BytesPerCluster;
    else
        NtfsInfo->BytesPerFileRecord = 1 << (-BootSector->EBPB.ClustersPerMftRecord);
    if (BootSector->EBPB.ClustersPerIndexRecord > 0)
        NtfsInfo->BytesPerIndexRecord = BootSector->EBPB.ClustersPerIndexRecord * NtfsInfo->BytesPerCluster;
    else
        NtfsInfo->BytesPerIndexRecord = 1 << (-BootSector->EBPB.ClustersPerIndexRecord);

    DPRINT("Boot sector information:\n");
    DPRINT("  BytesPerSector:         %hu\n", BootSector->BPB.BytesPerSector);
    DPRINT("  SectorsPerCluster:      %hu\n", BootSector->BPB.SectorsPerCluster);
    DPRINT("  SectorCount:            %I64u\n", BootSector->EBPB.SectorCount);
    DPRINT("  MftStart:               %I64u\n", BootSector->EBPB.MftLocation);
    DPRINT("  MftMirrStart:           %I64u\n", BootSector->EBPB.MftMirrLocation);
    DPRINT("  ClustersPerMftRecord:   %lx\n", BootSector->EBPB.ClustersPerMftRecord);
    DPRINT("  ClustersPerIndexRecord: %lx\n", BootSector->EBPB.ClustersPerIndexRecord);
    DPRINT("  SerialNumber:           %I64x\n", BootSector->EBPB.SerialNumber);

    ExFreePool(BootSector);

    ExInitializeNPagedLookasideList(&DeviceExt->FileRecLookasideList,
                                    NULL, NULL, 0, NtfsInfo->BytesPerFileRecord, TAG_FILE_REC, 0);

    DeviceExt->MasterFileTable = ExAllocateFromNPagedLookasideList(&DeviceExt->FileRecLookasideList);
    if (DeviceExt->MasterFileTable == NULL)
    {
        ExDeleteNPagedLookasideList(&DeviceExt->FileRecLookasideList);
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    Status = NtfsReadSectors(DeviceObject,
                             NtfsInfo->MftStart.u.LowPart * NtfsInfo->SectorsPerCluster,
                             NtfsInfo->BytesPerFileRecord / NtfsInfo->BytesPerSector,
                             NtfsInfo->BytesPerSector,
                             (PVOID)DeviceExt->MasterFileTable,
                             TRUE);
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("Failed reading MFT.\n");
        ExFreeToNPagedLookasideList(&DeviceExt->FileRecLookasideList, DeviceExt->MasterFileTable);
        ExDeleteNPagedLookasideList(&DeviceExt->FileRecLookasideList);
        return Status;
    }

    Status = FindAttribute(DeviceExt,
                           DeviceExt->MasterFileTable,
                           AttributeData,
                           L"",
                           0,
                           &DeviceExt->MFTContext,
                           &DeviceExt->MftDataOffset);
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("Can't find data attribute for Master File Table.\n");
        ExFreeToNPagedLookasideList(&DeviceExt->FileRecLookasideList, DeviceExt->MasterFileTable);
        ExDeleteNPagedLookasideList(&DeviceExt->FileRecLookasideList);
        return Status;
    }

    VolumeRecord = ExAllocateFromNPagedLookasideList(&DeviceExt->FileRecLookasideList);
    if (VolumeRecord == NULL)
    {
        DPRINT1("Allocation failed for volume record\n");
        ExFreeToNPagedLookasideList(&DeviceExt->FileRecLookasideList, DeviceExt->MasterFileTable);
        ExDeleteNPagedLookasideList(&DeviceExt->FileRecLookasideList);
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    /* Read Volume File (MFT index 3) */
    DeviceExt->StorageDevice = DeviceObject;
    Status = ReadFileRecord(DeviceExt,
                            NTFS_FILE_VOLUME,
                            VolumeRecord);
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("Failed reading volume file\n");
        ExFreeToNPagedLookasideList(&DeviceExt->FileRecLookasideList, VolumeRecord);
        ExFreeToNPagedLookasideList(&DeviceExt->FileRecLookasideList, DeviceExt->MasterFileTable);
        ExDeleteNPagedLookasideList(&DeviceExt->FileRecLookasideList);
        return Status;
    }

    /* Enumerate attributes */
    NtfsDumpFileAttributes(DeviceExt, DeviceExt->MasterFileTable);

    /* Enumerate attributes */
    NtfsDumpFileAttributes(DeviceExt, VolumeRecord);

    /* Get volume name */
    Status = FindAttribute(DeviceExt, VolumeRecord, AttributeVolumeName, L"", 0, &AttrCtxt, NULL);

    if (NT_SUCCESS(Status) && AttrCtxt->pRecord->Resident.ValueLength != 0)
    {
        Attribute = AttrCtxt->pRecord;
        DPRINT("Data length %lu\n", AttributeDataLength(Attribute));
        NtfsInfo->VolumeLabelLength =
           min (Attribute->Resident.ValueLength, MAXIMUM_VOLUME_LABEL_LENGTH);
        RtlCopyMemory(NtfsInfo->VolumeLabel,
                      (PVOID)((ULONG_PTR)Attribute + Attribute->Resident.ValueOffset),
                      NtfsInfo->VolumeLabelLength);
        VolumeNameU = NtfsInfo->VolumeLabel;
    }
    else
    {
        NtfsInfo->VolumeLabelLength = 0;
        VolumeNameU = L"\0";
    }

    if (NT_SUCCESS(Status))
    {
        ReleaseAttributeContext(AttrCtxt);
    }

    VolumeFcb = NtfsCreateFCB(VolumeNameU, NULL, DeviceExt);
    if (VolumeFcb == NULL)
    {
        DPRINT1("Failed allocating volume FCB\n");
        ExFreeToNPagedLookasideList(&DeviceExt->FileRecLookasideList, VolumeRecord);
        ExFreeToNPagedLookasideList(&DeviceExt->FileRecLookasideList, DeviceExt->MasterFileTable);
        ExDeleteNPagedLookasideList(&DeviceExt->FileRecLookasideList);
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    VolumeFcb->Flags = FCB_IS_VOLUME;
    VolumeFcb->RFCB.FileSize.QuadPart = DeviceExt->NtfsInfo.SectorCount * DeviceExt->NtfsInfo.BytesPerSector;
    VolumeFcb->RFCB.ValidDataLength = VolumeFcb->RFCB.FileSize;
    VolumeFcb->RFCB.AllocationSize = VolumeFcb->RFCB.FileSize;
    VolumeFcb->MFTIndex = 0;
    DeviceExt->VolumeFcb = VolumeFcb;

    /* Get volume information */
    Status = FindAttribute(DeviceExt, VolumeRecord, AttributeVolumeInformation, L"", 0, &AttrCtxt, NULL);

    if (NT_SUCCESS(Status) && AttrCtxt->pRecord->Resident.ValueLength != 0)
    {
        Attribute = AttrCtxt->pRecord;
        DPRINT("Data length %lu\n", AttributeDataLength (Attribute));
        VolumeInfo = (PVOID)((ULONG_PTR)Attribute + Attribute->Resident.ValueOffset);

        NtfsInfo->MajorVersion = VolumeInfo->MajorVersion;
        NtfsInfo->MinorVersion = VolumeInfo->MinorVersion;
        NtfsInfo->Flags = VolumeInfo->Flags;
    }

    if (NT_SUCCESS(Status))
    {
        ReleaseAttributeContext(AttrCtxt);
    }

    ExFreeToNPagedLookasideList(&DeviceExt->FileRecLookasideList, VolumeRecord);

    NtfsInfo->MftZoneReservation = NtfsQueryMftZoneReservation();

    return Status;
}