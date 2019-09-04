#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ loff_t ;
typedef  int ULONGLONG ;
typedef  scalar_t__ ULONG ;
struct TYPE_15__ {scalar_t__ i_size; } ;
struct TYPE_14__ {TYPE_4__ Inode; int /*<<< orphan*/  Extents; int /*<<< orphan*/  Flags; } ;
struct TYPE_13__ {scalar_t__ max_data_blocks; } ;
struct TYPE_12__ {int QuadPart; } ;
typedef  TYPE_1__* PLARGE_INTEGER ;
typedef  TYPE_2__* PEXT2_VCB ;
typedef  TYPE_3__* PEXT2_MCB ;
typedef  int /*<<< orphan*/  PEXT2_IRP_CONTEXT ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int BLOCK_BITS ; 
 int BLOCK_SIZE ; 
 int /*<<< orphan*/  ClearFlag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Ext2ClearAllExtents (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Ext2RemoveBlockExtent (TYPE_2__*,TYPE_3__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  Ext2SaveInode (int /*<<< orphan*/ ,TYPE_2__*,TYPE_4__*) ; 
 int /*<<< orphan*/  MCB_ZONE_INITED ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int ext4_ext_truncate (int /*<<< orphan*/ ,TYPE_4__*,scalar_t__) ; 

NTSTATUS
Ext2TruncateExtent(
    PEXT2_IRP_CONTEXT IrpContext,
    PEXT2_VCB         Vcb,
    PEXT2_MCB         Mcb,
    PLARGE_INTEGER    Size
    )
{
    NTSTATUS Status = STATUS_SUCCESS;

    ULONG    Extra = 0;
    ULONG    Wanted = 0;
    ULONG    End;
    ULONG    Removed;
    int      err;

    /* translate file size to block */
    End = Vcb->max_data_blocks;
    Wanted = (ULONG)((Size->QuadPart + BLOCK_SIZE - 1) >> BLOCK_BITS);

    /* calculate blocks to be freed */
    Extra = End - Wanted;

    err = ext4_ext_truncate(IrpContext, &Mcb->Inode, Wanted);
    if (err == 0) {
        if (!Ext2RemoveBlockExtent(Vcb, Mcb, Wanted, Extra)) {
            ClearFlag(Mcb->Flags, MCB_ZONE_INITED);
            Ext2ClearAllExtents(&Mcb->Extents);
        }
        Extra = 0;
    } else {
        Status = STATUS_INSUFFICIENT_RESOURCES;
    }

    if (!NT_SUCCESS(Status)) {
        Size->QuadPart += ((ULONGLONG)Extra << BLOCK_BITS);
    }

    if (Mcb->Inode.i_size > (loff_t)(Size->QuadPart))
        Mcb->Inode.i_size = (loff_t)(Size->QuadPart);

    /* Save modifications on i_blocks field and i_size field of the inode. */
    Ext2SaveInode(IrpContext, Vcb, &Mcb->Inode);

    return Status;
}