#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_19__ ;

/* Type definitions */
typedef  scalar_t__ ULONG_PTR ;
typedef  int ULONGLONG ;
typedef  scalar_t__ ULONG ;
struct TYPE_26__ {int /*<<< orphan*/  FileMFTIndex; TYPE_19__* pRecord; int /*<<< orphan*/  DataRunsMCB; } ;
struct TYPE_23__ {int HighestVCN; scalar_t__ MappingPairsOffset; } ;
struct TYPE_25__ {scalar_t__ Type; scalar_t__ Length; TYPE_3__ NonResident; } ;
struct TYPE_21__ {int ClusterCount; int /*<<< orphan*/  BytesPerCluster; int /*<<< orphan*/  BytesPerFileRecord; int /*<<< orphan*/  BytesPerSector; } ;
struct TYPE_24__ {TYPE_1__ NtfsInfo; int /*<<< orphan*/  FileRecLookasideList; } ;
struct TYPE_22__ {int HighestVCN; scalar_t__ MappingPairsOffset; } ;
struct TYPE_20__ {scalar_t__ Length; TYPE_2__ NonResident; int /*<<< orphan*/  IsNonResident; } ;
typedef  int /*<<< orphan*/  RTL_BITMAP ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  PULONG ;
typedef  int /*<<< orphan*/ * PUCHAR ;
typedef  TYPE_4__* PNTFS_VCB ;
typedef  TYPE_5__* PNTFS_ATTR_RECORD ;
typedef  TYPE_6__* PNTFS_ATTR_CONTEXT ;
typedef  int /*<<< orphan*/ * PFILE_RECORD_HEADER ;
typedef  int /*<<< orphan*/  PCHAR ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int LONGLONG ;

/* Variables and functions */
 scalar_t__ ALIGN_UP_BY (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  ATTR_RECORD_ALIGNMENT ; 
 int /*<<< orphan*/  AttributeData ; 
 int AttributeDataLength (TYPE_19__*) ; 
 scalar_t__ AttributeEnd ; 
 int /*<<< orphan*/  ConvertLargeMCBToDataRuns (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  DPRINT1 (char*,...) ; 
 int /*<<< orphan*/ * ExAllocateFromNPagedLookasideList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ExAllocatePoolWithTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExFreePoolWithTag (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExFreeToNPagedLookasideList (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FILE_RECORD_END ; 
 int /*<<< orphan*/  FindAttribute (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,TYPE_6__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FsRtlLookupLastLargeMcbEntry (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  FsRtlTruncateLargeMcb (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  NTFS_FILE_BITMAP ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NonPagedPool ; 
 int /*<<< orphan*/  NtfsDumpDataRuns (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ROUND_UP (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReadAttribute (TYPE_4__*,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ReadFileRecord (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseAttributeContext (TYPE_6__*) ; 
 int /*<<< orphan*/  RtlClearBits (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  RtlInitializeBitMap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  STATUS_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  STATUS_NO_MEMORY ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  SetFileRecordEnd (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG_NTFS ; 
 int ULONG_MAX ; 
 int /*<<< orphan*/  UpdateFileRecord (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WriteAttribute (TYPE_4__*,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,scalar_t__*,int /*<<< orphan*/ *) ; 
 void* min (int,int) ; 

NTSTATUS
FreeClusters(PNTFS_VCB Vcb,
             PNTFS_ATTR_CONTEXT AttrContext,
             ULONG AttrOffset,
             PFILE_RECORD_HEADER FileRecord,
             ULONG ClustersToFree)
{
    NTSTATUS Status = STATUS_SUCCESS;
    ULONG ClustersLeftToFree = ClustersToFree;

    PNTFS_ATTR_RECORD DestinationAttribute = (PNTFS_ATTR_RECORD)((ULONG_PTR)FileRecord + AttrOffset);
    ULONG NextAttributeOffset = AttrOffset + AttrContext->pRecord->Length;
    PNTFS_ATTR_RECORD NextAttribute = (PNTFS_ATTR_RECORD)((ULONG_PTR)FileRecord + NextAttributeOffset);

    PUCHAR RunBuffer;
    ULONG RunBufferSize = 0;

    PFILE_RECORD_HEADER BitmapRecord;
    PNTFS_ATTR_CONTEXT DataContext;
    ULONGLONG BitmapDataSize;
    PUCHAR BitmapData;
    RTL_BITMAP Bitmap;
    ULONG LengthWritten;

    if (!AttrContext->pRecord->IsNonResident)
    {
        return STATUS_INVALID_PARAMETER;
    }

    // Read the $Bitmap file
    BitmapRecord = ExAllocateFromNPagedLookasideList(&Vcb->FileRecLookasideList);
    if (BitmapRecord == NULL)
    {
        DPRINT1("Error: Unable to allocate memory for bitmap file record!\n");
        return STATUS_NO_MEMORY;
    }

    Status = ReadFileRecord(Vcb, NTFS_FILE_BITMAP, BitmapRecord);
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("Error: Unable to read file record for bitmap!\n");
        ExFreeToNPagedLookasideList(&Vcb->FileRecLookasideList, BitmapRecord);
        return 0;
    }

    Status = FindAttribute(Vcb, BitmapRecord, AttributeData, L"", 0, &DataContext, NULL);
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("Error: Unable to find data attribute for bitmap file!\n");
        ExFreeToNPagedLookasideList(&Vcb->FileRecLookasideList, BitmapRecord);
        return 0;
    }

    BitmapDataSize = AttributeDataLength(DataContext->pRecord);
    BitmapDataSize = min(BitmapDataSize, ULONG_MAX);
    ASSERT((BitmapDataSize * 8) >= Vcb->NtfsInfo.ClusterCount);
    BitmapData = ExAllocatePoolWithTag(NonPagedPool, ROUND_UP(BitmapDataSize, Vcb->NtfsInfo.BytesPerSector), TAG_NTFS);
    if (BitmapData == NULL)
    {
        DPRINT1("Error: Unable to allocate memory for bitmap file data!\n");
        ReleaseAttributeContext(DataContext);
        ExFreeToNPagedLookasideList(&Vcb->FileRecLookasideList, BitmapRecord);
        return 0;
    }

    ReadAttribute(Vcb, DataContext, 0, (PCHAR)BitmapData, (ULONG)BitmapDataSize);

    RtlInitializeBitMap(&Bitmap, (PULONG)BitmapData, Vcb->NtfsInfo.ClusterCount);
    
    // free clusters in $BITMAP file
    while (ClustersLeftToFree > 0)
    {
        LONGLONG LargeVbn, LargeLbn;

        if (!FsRtlLookupLastLargeMcbEntry(&AttrContext->DataRunsMCB, &LargeVbn, &LargeLbn))
        {
            Status = STATUS_INVALID_PARAMETER;
            DPRINT1("DRIVER ERROR: FreeClusters called to free %lu clusters, which is %lu more clusters than are assigned to attribute!",
                    ClustersToFree,
                    ClustersLeftToFree);
            break;
        }

        if (LargeLbn != -1)
        {
            // deallocate this cluster
            RtlClearBits(&Bitmap, LargeLbn, 1);
        }
        FsRtlTruncateLargeMcb(&AttrContext->DataRunsMCB, AttrContext->pRecord->NonResident.HighestVCN);

        // decrement HighestVCN, but don't let it go below 0
        AttrContext->pRecord->NonResident.HighestVCN = min(AttrContext->pRecord->NonResident.HighestVCN, AttrContext->pRecord->NonResident.HighestVCN - 1);
        ClustersLeftToFree--;
    }

    // update $BITMAP file on disk
    Status = WriteAttribute(Vcb, DataContext, 0, BitmapData, (ULONG)BitmapDataSize, &LengthWritten, FileRecord);
    if (!NT_SUCCESS(Status))
    {
        ReleaseAttributeContext(DataContext);
        ExFreePoolWithTag(BitmapData, TAG_NTFS);
        ExFreeToNPagedLookasideList(&Vcb->FileRecLookasideList, BitmapRecord);
        return Status;
    }

    ReleaseAttributeContext(DataContext);
    ExFreePoolWithTag(BitmapData, TAG_NTFS);
    ExFreeToNPagedLookasideList(&Vcb->FileRecLookasideList, BitmapRecord);
    
    // Save updated data runs to file record

    // Allocate some memory for a new RunBuffer
    RunBuffer = ExAllocatePoolWithTag(NonPagedPool, Vcb->NtfsInfo.BytesPerFileRecord, TAG_NTFS);
    if (!RunBuffer)
    {
        DPRINT1("ERROR: Couldn't allocate memory for data runs!\n");
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    // Convert the map control block back to encoded data runs
    ConvertLargeMCBToDataRuns(&AttrContext->DataRunsMCB, RunBuffer, Vcb->NtfsInfo.BytesPerCluster, &RunBufferSize);

    // Update HighestVCN
    DestinationAttribute->NonResident.HighestVCN = AttrContext->pRecord->NonResident.HighestVCN;

    // Write data runs to destination attribute
    RtlCopyMemory((PVOID)((ULONG_PTR)DestinationAttribute + DestinationAttribute->NonResident.MappingPairsOffset),
                  RunBuffer,
                  RunBufferSize);

    // Is DestinationAttribute the last attribute in the file record?
    if (NextAttribute->Type == AttributeEnd)
    {
        // update attribute length
        DestinationAttribute->Length = ALIGN_UP_BY(AttrContext->pRecord->NonResident.MappingPairsOffset + RunBufferSize,
                                                 ATTR_RECORD_ALIGNMENT);

        ASSERT(DestinationAttribute->Length <= AttrContext->pRecord->Length);

        AttrContext->pRecord->Length = DestinationAttribute->Length;

        // write end markers
        NextAttribute = (PNTFS_ATTR_RECORD)((ULONG_PTR)DestinationAttribute + DestinationAttribute->Length);
        SetFileRecordEnd(FileRecord, NextAttribute, FILE_RECORD_END);
    }

    // Update the file record
    Status = UpdateFileRecord(Vcb, AttrContext->FileMFTIndex, FileRecord);

    ExFreePoolWithTag(RunBuffer, TAG_NTFS);

    NtfsDumpDataRuns((PUCHAR)((ULONG_PTR)DestinationAttribute + DestinationAttribute->NonResident.MappingPairsOffset), 0);

    return Status;
}