#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ext2_inode {int /*<<< orphan*/  i_atime; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */

void ext2fs_set_ea_inode_hash(struct ext2_inode *inode, __u32 hash)
{
	inode->i_atime = hash;
}