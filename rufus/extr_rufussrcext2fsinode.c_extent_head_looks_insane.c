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
struct ext2_inode_large {int i_flags; int /*<<< orphan*/  i_block; } ;

/* Variables and functions */
 int EXT4_EXTENTS_FL ; 
 scalar_t__ ext2fs_extent_header_verify (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int extent_head_looks_insane(struct ext2_inode_large *inode)
{
	if (!(inode->i_flags & EXT4_EXTENTS_FL) ||
	    ext2fs_extent_header_verify(inode->i_block,
					sizeof(inode->i_block)) == 0)
		return 0;
	return 1;
}