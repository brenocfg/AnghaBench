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
struct ext2_super_block {int s_free_blocks_hi; scalar_t__ s_free_blocks_count; } ;
typedef  scalar_t__ blk64_t ;
typedef  int __u64 ;

/* Variables and functions */
 scalar_t__ ext2fs_has_feature_64bit (struct ext2_super_block*) ; 

void ext2fs_free_blocks_count_set(struct ext2_super_block *super, blk64_t blk)
{
	super->s_free_blocks_count = blk;
	if (ext2fs_has_feature_64bit(super))
		super->s_free_blocks_hi = (__u64) blk >> 32;
}