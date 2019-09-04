#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int USHORT ;
typedef  scalar_t__ ULONG_PTR ;
typedef  scalar_t__ ULONG ;
struct TYPE_18__ {int /*<<< orphan*/  CompressedSize; } ;
struct TYPE_17__ {scalar_t__ BytesInUse; int /*<<< orphan*/  NextAttributeNumber; } ;
struct TYPE_14__ {scalar_t__ HighestVCN; scalar_t__ MappingPairsOffset; } ;
struct TYPE_16__ {scalar_t__ Type; scalar_t__ Length; int NameLength; TYPE_2__ NonResident; scalar_t__ Instance; scalar_t__ NameOffset; int /*<<< orphan*/  IsNonResident; } ;
struct TYPE_13__ {scalar_t__ BytesPerFileRecord; } ;
struct TYPE_15__ {TYPE_1__ NtfsInfo; } ;
typedef  TYPE_3__* PNTFS_VCB ;
typedef  TYPE_4__* PNTFS_ATTR_RECORD ;
typedef  TYPE_5__* PFILE_RECORD_HEADER ;
typedef  int /*<<< orphan*/  PCWSTR ;
typedef  int /*<<< orphan*/  PCHAR ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  scalar_t__ LONGLONG ;

/* Variables and functions */
 scalar_t__ ALIGN_UP_BY (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATTR_RECORD_ALIGNMENT ; 
 scalar_t__ AttributeEnd ; 
 scalar_t__ AttributeIndexAllocation ; 
 int /*<<< orphan*/  DATA_RUN_ALIGNMENT ; 
 int /*<<< orphan*/  DPRINT1 (char*) ; 
 scalar_t__ FIELD_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NTFS_ATTR_RECORD ; 
 TYPE_9__ NonResident ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  STATUS_NOT_IMPLEMENTED ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  SetFileRecordEnd (TYPE_5__*,TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 

NTSTATUS
AddIndexAllocation(PNTFS_VCB Vcb,
                   PFILE_RECORD_HEADER FileRecord,
                   PNTFS_ATTR_RECORD AttributeAddress,
                   PCWSTR Name,
                   USHORT NameLength)
{
    ULONG RecordLength;
    ULONG FileRecordEnd;
    ULONG NameOffset;
    ULONG DataRunOffset;
    ULONG BytesAvailable;

    if (AttributeAddress->Type != AttributeEnd)
    {
        DPRINT1("FIXME: Can only add $INDEX_ALLOCATION attribute to the end of a file record.\n");
        return STATUS_NOT_IMPLEMENTED;
    }

    // Calculate the name offset
    NameOffset = FIELD_OFFSET(NTFS_ATTR_RECORD, NonResident.CompressedSize);

    // Calculate the offset to the first data run
    DataRunOffset = (sizeof(WCHAR) * NameLength) + NameOffset;
    // The data run offset must be aligned to a 4-byte boundary
    DataRunOffset = ALIGN_UP_BY(DataRunOffset, DATA_RUN_ALIGNMENT);

    // Calculate the length of the new attribute; the empty data run will consist of a single byte
    RecordLength = DataRunOffset + 1;

    // The size of the attribute itself must be aligned to an 8 - byte boundary
    RecordLength = ALIGN_UP_BY(RecordLength, ATTR_RECORD_ALIGNMENT);

    // Back up the last 4-bytes of the file record (even though this value doesn't matter)
    FileRecordEnd = AttributeAddress->Length;

    // Make sure the file record can contain the new attribute
    BytesAvailable = Vcb->NtfsInfo.BytesPerFileRecord - FileRecord->BytesInUse;
    if (BytesAvailable < RecordLength)
    {
        DPRINT1("FIXME: Not enough room in file record for index allocation attribute!\n");
        return STATUS_NOT_IMPLEMENTED;
    }

    // Set fields of attribute header
    RtlZeroMemory(AttributeAddress, RecordLength);
    
    AttributeAddress->Type = AttributeIndexAllocation;
    AttributeAddress->Length = RecordLength;
    AttributeAddress->IsNonResident = TRUE;
    AttributeAddress->NameLength = NameLength;
    AttributeAddress->NameOffset = NameOffset;
    AttributeAddress->Instance = FileRecord->NextAttributeNumber++;

    AttributeAddress->NonResident.MappingPairsOffset = DataRunOffset;
    AttributeAddress->NonResident.HighestVCN = (LONGLONG)-1;

    // Set the name
    RtlCopyMemory((PCHAR)((ULONG_PTR)AttributeAddress + NameOffset), Name, NameLength * sizeof(WCHAR));

    // move the attribute-end and file-record-end markers to the end of the file record
    AttributeAddress = (PNTFS_ATTR_RECORD)((ULONG_PTR)AttributeAddress + AttributeAddress->Length);
    SetFileRecordEnd(FileRecord, AttributeAddress, FileRecordEnd);

    return STATUS_SUCCESS;
}