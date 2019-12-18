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
struct ext2_super_block {unsigned long s_blocks_per_group; unsigned long s_first_data_block; } ;
typedef  TYPE_1__* ext2_filsys ;
struct TYPE_3__ {void* desc_blocks; struct ext2_super_block* super; } ;

/* Variables and functions */
 unsigned int EXT2_ADDR_PER_BLOCK (struct ext2_super_block*) ; 
 unsigned int EXT2_DESC_PER_BLOCK (struct ext2_super_block*) ; 
 int ext2fs_blocks_count (struct ext2_super_block*) ; 
 void* ext2fs_div_ceil (unsigned long,unsigned int) ; 
 int /*<<< orphan*/  printf (char*,unsigned long,unsigned long,unsigned int) ; 

__attribute__((used)) static unsigned int calc_reserved_gdt_blocks(ext2_filsys fs)
{
	struct ext2_super_block *sb = fs->super;
	unsigned long bpg = sb->s_blocks_per_group;
	unsigned int gdpb = EXT2_DESC_PER_BLOCK(sb);
	unsigned long max_blocks = 0xffffffff;
	unsigned long rsv_groups;
	unsigned int rsv_gdb;

	/* We set it at 1024x the current filesystem size, or
	 * the upper block count limit (2^32), whichever is lower.
	 */
	if (ext2fs_blocks_count(sb) < max_blocks / 1024)
		max_blocks = ext2fs_blocks_count(sb) * 1024;
	/*
	 * ext2fs_div64_ceil() is unnecessary because max_blocks is
	 * max _GDT_ blocks, which is limited to 32 bits.
	 */
	rsv_groups = ext2fs_div_ceil(max_blocks - sb->s_first_data_block, bpg);
	rsv_gdb = ext2fs_div_ceil(rsv_groups, gdpb) - fs->desc_blocks;
	if (rsv_gdb > EXT2_ADDR_PER_BLOCK(sb))
		rsv_gdb = EXT2_ADDR_PER_BLOCK(sb);
#ifdef RES_GDT_DEBUG
	printf("max_blocks %lu, rsv_groups = %lu, rsv_gdb = %u\n",
	       max_blocks, rsv_groups, rsv_gdb);
#endif

	return rsv_gdb;
}