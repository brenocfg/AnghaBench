#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ext2_inode {int dummy; } ;
typedef  TYPE_1__* ext2_filsys ;
typedef  int /*<<< orphan*/  errcode_t ;
typedef  scalar_t__ blk_t ;
typedef  int blk64_t ;
struct TYPE_7__ {int blocksize; int /*<<< orphan*/  super; } ;

/* Variables and functions */
 int EXT2_BLOCK_SIZE_BITS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_zero_block (char*,int) ; 
 int /*<<< orphan*/  ext2fs_block_alloc_stats (TYPE_1__*,scalar_t__,int) ; 
 int /*<<< orphan*/  ext2fs_iblk_sub_blocks (TYPE_1__*,struct ext2_inode*,int) ; 
 int /*<<< orphan*/  ext2fs_read_ind_block (TYPE_1__*,scalar_t__,char*) ; 
 int /*<<< orphan*/  ext2fs_write_ind_block (TYPE_1__*,scalar_t__,char*) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 

__attribute__((used)) static errcode_t ind_punch(ext2_filsys fs, struct ext2_inode *inode,
			   char *block_buf, blk_t *p, int level,
			   blk64_t start, blk64_t count, int max)
{
	errcode_t	retval;
	blk_t		b;
	int		i;
	blk64_t		offset, incr;
	int		freed = 0;

#ifdef PUNCH_DEBUG
	printf("Entering ind_punch, level %d, start %llu, count %llu, "
	       "max %d\n", level, start, count, max);
#endif
	incr = 1ULL << ((EXT2_BLOCK_SIZE_BITS(fs->super) - 2) * level);
	for (i = 0, offset = 0; i < max; i++, p++, offset += incr) {
		if (offset >= start + count)
			break;
		if (*p == 0 || (offset+incr) <= start)
			continue;
		b = *p;
		if (level > 0) {
			blk_t start2;
#ifdef PUNCH_DEBUG
			printf("Reading indirect block %u\n", b);
#endif
			retval = ext2fs_read_ind_block(fs, b, block_buf);
			if (retval)
				return retval;
			start2 = (start > offset) ? start - offset : 0;
			retval = ind_punch(fs, inode, block_buf + fs->blocksize,
					   (blk_t *) block_buf, level - 1,
					   start2, count - offset,
					   fs->blocksize >> 2);
			if (retval)
				return retval;
			retval = ext2fs_write_ind_block(fs, b, block_buf);
			if (retval)
				return retval;
			if (!check_zero_block(block_buf, fs->blocksize))
				continue;
		}
#ifdef PUNCH_DEBUG
		printf("Freeing block %u (offset %llu)\n", b, offset);
#endif
		ext2fs_block_alloc_stats(fs, b, -1);
		*p = 0;
		freed++;
	}
#ifdef PUNCH_DEBUG
	printf("Freed %d blocks\n", freed);
#endif
	return ext2fs_iblk_sub_blocks(fs, inode, freed);
}