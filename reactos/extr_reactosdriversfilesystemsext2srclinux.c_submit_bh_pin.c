#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct buffer_head {int b_size; scalar_t__ b_blocknr; scalar_t__ b_bcb; scalar_t__ b_data; struct block_device* b_bdev; } ;
struct block_device {TYPE_3__* bd_priv; } ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_10__ {int QuadPart; } ;
struct TYPE_7__ {scalar_t__ Type; } ;
struct TYPE_9__ {TYPE_2__* Volume; TYPE_1__ Identifier; } ;
struct TYPE_8__ {int /*<<< orphan*/  Flags; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_3__* PEXT2_VCB ;
typedef  int LONGLONG ;
typedef  TYPE_4__ LARGE_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int BLOCK_BITS ; 
 int /*<<< orphan*/  CcSetDirtyPinnedData (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ EXT2VCB ; 
 int /*<<< orphan*/  Ext2AddBlockExtent (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FO_FILE_MODIFIED ; 
 scalar_t__ IsVcbReadOnly (TYPE_3__*) ; 
 int /*<<< orphan*/  SetFlag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int WRITE ; 
 int /*<<< orphan*/  put_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 

int submit_bh_pin(int rw, struct buffer_head *bh)
{
    struct block_device *bdev = bh->b_bdev;
    PEXT2_VCB            Vcb  = bdev->bd_priv;
    PVOID                Buffer;
    LARGE_INTEGER        Offset;

    ASSERT(Vcb->Identifier.Type == EXT2VCB);
    ASSERT(bh->b_data && bh->b_bcb);

    if (rw == WRITE) {

        if (IsVcbReadOnly(Vcb)) {
            goto errorout;
        }

        SetFlag(Vcb->Volume->Flags, FO_FILE_MODIFIED);
        Offset.QuadPart = ((LONGLONG)bh->b_blocknr) << BLOCK_BITS;

        CcSetDirtyPinnedData(bh->b_bcb, NULL);
        Ext2AddBlockExtent( Vcb, NULL,
                            (ULONG)bh->b_blocknr,
                            (ULONG)bh->b_blocknr,
                            (bh->b_size >> BLOCK_BITS));
    } else {
    }

errorout:

    unlock_buffer(bh);
    put_bh(bh);
    return 0;
}