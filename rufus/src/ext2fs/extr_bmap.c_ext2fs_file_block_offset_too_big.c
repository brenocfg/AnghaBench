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
struct ext2_inode {int i_flags; } ;
typedef  TYPE_1__* ext2_filsys ;
typedef  unsigned long long blk64_t ;
struct TYPE_3__ {int blocksize; } ;

/* Variables and functions */
 int EXT4_EXTENTS_FL ; 

int ext2fs_file_block_offset_too_big(ext2_filsys fs,
				     struct ext2_inode *inode,
				     blk64_t offset)
{
	blk64_t addr_per_block, max_map_block;

	/* Kernel seems to cut us off at 4294967294 blocks */
	if (offset >= (1ULL << 32) - 1)
		return 1;

	if (inode->i_flags & EXT4_EXTENTS_FL)
		return 0;

	addr_per_block = fs->blocksize >> 2;
	max_map_block = addr_per_block;
	max_map_block += addr_per_block * addr_per_block;
	max_map_block += addr_per_block * addr_per_block * addr_per_block;
	max_map_block += 12;

	return offset >= max_map_block;
}