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
typedef  int /*<<< orphan*/  ext2_filsys ;
typedef  int /*<<< orphan*/  errcode_t ;
typedef  int blk64_t ;

/* Variables and functions */
 int EXT2FS_CLUSTER_RATIO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext2fs_block_alloc_stats_range (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  ext2fs_iblk_add_blocks (int /*<<< orphan*/ ,struct ext2_inode*,int) ; 

__attribute__((used)) static errcode_t claim_range(ext2_filsys fs, struct ext2_inode *inode,
			     blk64_t blk, blk64_t len)
{
	blk64_t	clusters;

	clusters = (len + EXT2FS_CLUSTER_RATIO(fs) - 1) /
		   EXT2FS_CLUSTER_RATIO(fs);
	ext2fs_block_alloc_stats_range(fs, blk,
			clusters * EXT2FS_CLUSTER_RATIO(fs), +1);
	return ext2fs_iblk_add_blocks(fs, inode, clusters);
}