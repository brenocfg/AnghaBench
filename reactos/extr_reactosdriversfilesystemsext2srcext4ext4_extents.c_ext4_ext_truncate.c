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
struct inode {int dummy; } ;

/* Variables and functions */
 int ext4_ext_remove_space (void*,struct inode*,unsigned long) ; 
 int ext4_mark_inode_dirty (void*,int /*<<< orphan*/ *,struct inode*) ; 

int ext4_ext_truncate(void *icb, struct inode *inode, unsigned long start)
{
    int ret = ext4_ext_remove_space(icb, inode, start);

	/* Save modifications on i_blocks field of the inode. */
	if (!ret)
		ret = ext4_mark_inode_dirty(icb, NULL, inode);

	return ret;
}