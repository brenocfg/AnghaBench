#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONGLONG ;
typedef  int ULONG ;
struct TYPE_6__ {int QuadPart; } ;
struct TYPE_5__ {int /*<<< orphan*/  MediaHandle; } ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  int PUCHAR ;
typedef  TYPE_1__* PEXT2_FILESYS ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_2__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  IO_STATUS_BLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtReadFile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RtlAllocateHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  RtlFreeHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlGetProcessHeap () ; 
 int SECTOR_SIZE ; 
 int /*<<< orphan*/  STATUS_INSUFFICIENT_RESOURCES ; 

NTSTATUS
Ext2ReadDisk( PEXT2_FILESYS  Ext2Sys,
              ULONGLONG      Offset,
              ULONG          Length,
              PVOID          Buffer     )
{
    LARGE_INTEGER   Address;
    NTSTATUS        Status;
    ULONG           AlignedLength;

    IO_STATUS_BLOCK IoStatus;

    PVOID           NonPagedBuffer = NULL;

    ASSERT(Buffer != NULL);

#if 0
    if (Ext2Sys->bFile)
    {
        Address.QuadPart = Offset;

        Status = NtReadFile(  Ext2Sys->MediaHandle,
                              NULL,
                              NULL,
                              NULL,
                              &IoStatus,
                              Buffer,
                              Length,
                              &Address,
                              NULL );
    }
    else
#endif
    {
        Address.QuadPart = Offset & (~((ULONGLONG)SECTOR_SIZE - 1));

        AlignedLength = (Length + SECTOR_SIZE - 1)&(~(SECTOR_SIZE - 1));

        AlignedLength += ((ULONG)(Offset - Address.QuadPart) + SECTOR_SIZE - 1)
                         & (~(SECTOR_SIZE - 1));

        NonPagedBuffer = RtlAllocateHeap(RtlGetProcessHeap(), 0, AlignedLength);
        if (!NonPagedBuffer)
        {
            Status = STATUS_INSUFFICIENT_RESOURCES;
            goto errorout;
        }

        Status = NtReadFile( Ext2Sys->MediaHandle,
                             NULL,
                             NULL,
                             NULL,
                             &IoStatus,
                             NonPagedBuffer,
                             AlignedLength,
                             &Address,
                             NULL );

        if (!NT_SUCCESS(Status))
        {
            goto errorout;
        }

        RtlCopyMemory( Buffer,
                       (PUCHAR)NonPagedBuffer + (ULONG)(Offset - Address.QuadPart),
                       Length );
    }

errorout:

    if (NonPagedBuffer)
        RtlFreeHeap(RtlGetProcessHeap(), 0, NonPagedBuffer);

    return Status;
}