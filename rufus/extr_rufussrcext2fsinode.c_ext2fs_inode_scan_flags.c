#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ext2_inode_scan ;
struct TYPE_3__ {scalar_t__ magic; int scan_flags; } ;

/* Variables and functions */
 scalar_t__ EXT2_ET_MAGIC_INODE_SCAN ; 

int ext2fs_inode_scan_flags(ext2_inode_scan scan, int set_flags,
			    int clear_flags)
{
	int	old_flags;

	if (!scan || (scan->magic != EXT2_ET_MAGIC_INODE_SCAN))
		return 0;

	old_flags = scan->scan_flags;
	scan->scan_flags &= ~clear_flags;
	scan->scan_flags |= set_flags;
	return old_flags;
}