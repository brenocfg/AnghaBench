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
typedef  int /*<<< orphan*/  ext2_ino_t ;
typedef  int /*<<< orphan*/  ext2_filsys ;

/* Variables and functions */
 int /*<<< orphan*/  ext2fs_inode_alloc_stats2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void ext2fs_inode_alloc_stats(ext2_filsys fs, ext2_ino_t ino, int inuse)
{
	ext2fs_inode_alloc_stats2(fs, ino, inuse, 0);
}