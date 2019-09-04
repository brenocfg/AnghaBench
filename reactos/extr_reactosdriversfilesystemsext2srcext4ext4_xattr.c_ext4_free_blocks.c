#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct inode {int i_blocks; TYPE_1__* i_sb; } ;
typedef  scalar_t__ ext4_fsblk_t ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_2__ {int s_blocksize; int /*<<< orphan*/  s_priv; } ;
typedef  int /*<<< orphan*/  PEXT2_IRP_CONTEXT ;

/* Variables and functions */
 int /*<<< orphan*/  Ext2FreeBlock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ext4_free_blocks(void *icb, struct inode *inode,
	ext4_fsblk_t block, int count, int flags)
{
	Ext2FreeBlock((PEXT2_IRP_CONTEXT)icb, inode->i_sb->s_priv, (ULONG)block, count);
	inode->i_blocks -= count * (inode->i_sb->s_blocksize >> 9);
	return;
}