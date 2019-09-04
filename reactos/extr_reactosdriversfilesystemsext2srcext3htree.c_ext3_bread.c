#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct inode {TYPE_2__* i_sb; } ;
struct ext2_icb {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_8__ {int /*<<< orphan*/  s_priv; } ;
struct TYPE_7__ {int /*<<< orphan*/  Inode; struct TYPE_7__* Target; } ;
typedef  TYPE_1__* PEXT2_MCB ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 TYPE_1__* CONTAINING_RECORD (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EXT2_MCB ; 
 int Ext2LinuxError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Ext2MapExtent (struct ext2_icb*,int /*<<< orphan*/ ,TYPE_1__*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Ext2MapIndirect (struct ext2_icb*,int /*<<< orphan*/ ,TYPE_1__*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ INODE_HAS_EXTENT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Inode ; 
 scalar_t__ IsMcbSymLink (TYPE_1__*) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  __brelse (struct buffer_head*) ; 
 int bh_submit_read (struct buffer_head*) ; 
 scalar_t__ buffer_uptodate (struct buffer_head*) ; 
 struct buffer_head* sb_getblk (TYPE_2__*,int /*<<< orphan*/ ) ; 

struct buffer_head *ext3_bread(struct ext2_icb *icb, struct inode *inode,
                                           unsigned long block, int *err)
{
    struct buffer_head * bh = NULL;
    NTSTATUS    status = STATUS_SUCCESS;
    ULONG       lbn = 0, num = 0;

    PEXT2_MCB   Mcb = CONTAINING_RECORD(inode, EXT2_MCB, Inode);

    /* for symlink file, read it's target instead */
    if (NULL != Mcb && IsMcbSymLink(Mcb))
        Mcb = Mcb->Target;
    if (NULL == Mcb) {
        *err = -EINVAL;
        return NULL;
    }

    /* mapping file offset to ext2 block */
    if (INODE_HAS_EXTENT(&Mcb->Inode)) {
        status = Ext2MapExtent(icb, inode->i_sb->s_priv,
                               Mcb, block, FALSE,
                               &lbn, &num);
    } else {
        status = Ext2MapIndirect(icb, inode->i_sb->s_priv,
                                 Mcb, block, FALSE,
                                 &lbn, &num);
    }

    if (!NT_SUCCESS(status)) {
        *err = Ext2LinuxError(status);
        return bh;
    }

    bh = sb_getblk(inode->i_sb, lbn);
    if (!bh) {
        *err = -ENOMEM;
        return bh;
    }
    if (buffer_uptodate(bh))
        return bh;

    *err = bh_submit_read(bh);
    if (*err) {
	    __brelse(bh);
	    return NULL;
    }
    return bh;
}