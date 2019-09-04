#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  __u32 ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_6__ {int /*<<< orphan*/ * i_block; scalar_t__ i_size; scalar_t__ i_blocks; } ;
struct TYPE_7__ {TYPE_1__ Inode; int /*<<< orphan*/  Flags; int /*<<< orphan*/  MetaExts; int /*<<< orphan*/  Extents; } ;
typedef  int /*<<< orphan*/  PEXT2_VCB ;
typedef  TYPE_2__* PEXT2_MCB ;
typedef  int /*<<< orphan*/  PEXT2_IRP_CONTEXT ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int LONGLONG ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ClearFlag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ClearLongFlag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DbgBreak () ; 
 int /*<<< orphan*/  Ext2ClearAllExtents (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Ext2FreeBlock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Ext2InitializeZone (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ FsRtlGetNextLargeMcbEntry (int /*<<< orphan*/ *,int,int*,int*,int*) ; 
 scalar_t__ FsRtlNumberOfRunsInLargeMcb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IsZoneInited (TYPE_2__*) ; 
 int /*<<< orphan*/  MCB_ZONE_INITED ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

NTSTATUS
Ext2TruncateIndirectFast(
    PEXT2_IRP_CONTEXT IrpContext,
    PEXT2_VCB         Vcb,
    PEXT2_MCB         Mcb
    )
{
    LONGLONG            Vba;
    LONGLONG            Lba;
    LONGLONG            Length;
    NTSTATUS            Status = STATUS_SUCCESS;
    int                 i;

    /* try to load all indirect blocks if mcb zone is not initialized */
    if (!IsZoneInited(Mcb)) {
        Status = Ext2InitializeZone(IrpContext, Vcb, Mcb);
        if (!NT_SUCCESS(Status)) {
            DbgBreak();
            ClearLongFlag(Mcb->Flags, MCB_ZONE_INITED);
            goto errorout;
        }
    }

    ASSERT (IsZoneInited(Mcb));

    /* delete all data blocks here */
    if (FsRtlNumberOfRunsInLargeMcb(&Mcb->Extents) != 0) {
        for (i = 0; FsRtlGetNextLargeMcbEntry(&Mcb->Extents, i, &Vba, &Lba, &Length); i++) {
            /* ignore the non-existing runs */
            if (-1 == Lba || Vba == 0 || Length <= 0)
                continue;
            /* now do data block free */
            Ext2FreeBlock(IrpContext, Vcb, (ULONG)(Lba - 1), (ULONG)Length);
        }
    }

    /* delete all meta blocks here */
    if (FsRtlNumberOfRunsInLargeMcb(&Mcb->MetaExts) != 0) {
        for (i = 0; FsRtlGetNextLargeMcbEntry(&Mcb->MetaExts, i, &Vba, &Lba, &Length); i++) {
            /* ignore the non-existing runs */
            if (-1 == Lba || Vba == 0 || Length <= 0)
                continue;
            /* now do meta block free */
            Ext2FreeBlock(IrpContext, Vcb, (ULONG)(Lba - 1), (ULONG)Length);
        }
    }

    /* clear data and meta extents */
    Ext2ClearAllExtents(&Mcb->Extents);
    Ext2ClearAllExtents(&Mcb->MetaExts);
    ClearFlag(Mcb->Flags, MCB_ZONE_INITED);

    /* clear inode blocks & sizes */
    Mcb->Inode.i_blocks = 0;
    Mcb->Inode.i_size = 0;
    memset(&Mcb->Inode.i_block[0], 0, sizeof(__u32) * 15);

    /* the caller will do inode save */

errorout:

    return Status;
}