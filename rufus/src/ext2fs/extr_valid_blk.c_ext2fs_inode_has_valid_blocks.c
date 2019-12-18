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
struct ext2_inode {int dummy; } ;

/* Variables and functions */
 int ext2fs_inode_has_valid_blocks2 (int /*<<< orphan*/ *,struct ext2_inode*) ; 

int ext2fs_inode_has_valid_blocks(struct ext2_inode *inode)
{
	return ext2fs_inode_has_valid_blocks2(NULL, inode);
}