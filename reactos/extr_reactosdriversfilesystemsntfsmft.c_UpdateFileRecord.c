#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONGLONG ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_12__ {int BytesPerFileRecord; } ;
struct TYPE_14__ {TYPE_1__ NtfsInfo; int /*<<< orphan*/  MFTContext; } ;
struct TYPE_13__ {int /*<<< orphan*/  Ntfs; } ;
typedef  int /*<<< orphan*/  PUCHAR ;
typedef  TYPE_2__* PFILE_RECORD_HEADER ;
typedef  TYPE_3__* PDEVICE_EXTENSION ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  AddFixupArray (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DPRINT (char*,TYPE_3__*,int,TYPE_2__*) ; 
 int /*<<< orphan*/  DPRINT1 (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FixupUpdateSequenceArray (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  WriteAttribute (TYPE_3__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const,int,int /*<<< orphan*/ *,TYPE_2__*) ; 

NTSTATUS
UpdateFileRecord(PDEVICE_EXTENSION Vcb,
                 ULONGLONG MftIndex,
                 PFILE_RECORD_HEADER FileRecord)
{
    ULONG BytesWritten;
    NTSTATUS Status = STATUS_SUCCESS;

    DPRINT("UpdateFileRecord(%p, 0x%I64x, %p)\n", Vcb, MftIndex, FileRecord);

    // Add the fixup array to prepare the data for writing to disk
    AddFixupArray(Vcb, &FileRecord->Ntfs);

    // write the file record to the master file table
    Status = WriteAttribute(Vcb, 
                            Vcb->MFTContext,
                            MftIndex * Vcb->NtfsInfo.BytesPerFileRecord,
                            (const PUCHAR)FileRecord,
                            Vcb->NtfsInfo.BytesPerFileRecord,
                            &BytesWritten,
                            FileRecord);

    if (!NT_SUCCESS(Status))
    {
        DPRINT1("UpdateFileRecord failed: %lu written, %lu expected\n", BytesWritten, Vcb->NtfsInfo.BytesPerFileRecord);
    }

    // remove the fixup array (so the file record pointer can still be used)
    FixupUpdateSequenceArray(Vcb, &FileRecord->Ntfs);

    return Status;
}