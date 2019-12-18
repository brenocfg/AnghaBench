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
typedef  int /*<<< orphan*/  ext2_filsys ;
typedef  int /*<<< orphan*/  errcode_t ;
typedef  int /*<<< orphan*/  blk_t ;

/* Variables and functions */
 int /*<<< orphan*/  ext2fs_add_journal_inode2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long,int) ; 

errcode_t ext2fs_add_journal_inode(ext2_filsys fs, blk_t num_blocks, int flags)
{
	return ext2fs_add_journal_inode2(fs, num_blocks, ~0ULL, flags);
}