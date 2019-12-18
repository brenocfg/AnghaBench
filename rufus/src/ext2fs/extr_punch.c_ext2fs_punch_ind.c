#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ext2_inode {int* i_block; } ;
typedef  TYPE_1__* ext2_filsys ;
typedef  scalar_t__ errcode_t ;
typedef  int blk_t ;
typedef  scalar_t__ blk64_t ;
struct TYPE_4__ {scalar_t__ blocksize; } ;

/* Variables and functions */
 scalar_t__ BLK_T_MAX ; 
 void* EXT2_NDIR_BLOCKS ; 
 int /*<<< orphan*/  ext2fs_free_mem (char**) ; 
 scalar_t__ ext2fs_get_array (int,scalar_t__,char**) ; 
 scalar_t__ ind_punch (TYPE_1__*,struct ext2_inode*,char*,int*,int,scalar_t__,int,int) ; 
 int /*<<< orphan*/  printf (char*,int,scalar_t__,int,scalar_t__,int) ; 

__attribute__((used)) static errcode_t ext2fs_punch_ind(ext2_filsys fs, struct ext2_inode *inode,
				  char *block_buf, blk64_t start, blk64_t end)
{
	errcode_t		retval;
	char			*buf = 0;
	int			level;
	int			num = EXT2_NDIR_BLOCKS;
	blk_t			*bp = inode->i_block;
	blk_t			addr_per_block;
	blk64_t			max = EXT2_NDIR_BLOCKS;
	blk_t			count;

	/* Check start/end don't overflow the 2^32-1 indirect block limit */
	if (start > BLK_T_MAX)
		return 0;
	if (end >= BLK_T_MAX || end - start + 1 >= BLK_T_MAX)
		count = BLK_T_MAX - start;
	else
		count = end - start + 1;

	if (!block_buf) {
		retval = ext2fs_get_array(3, fs->blocksize, &buf);
		if (retval)
			return retval;
		block_buf = buf;
	}

	addr_per_block = (blk_t)fs->blocksize >> 2;

	for (level = 0; level < 4; level++, max *= (blk64_t)addr_per_block) {
#ifdef PUNCH_DEBUG
		printf("Main loop level %d, start %llu count %u "
		       "max %llu num %d\n", level, start, count, max, num);
#endif
		if (start < max) {
			retval = ind_punch(fs, inode, block_buf, bp, level,
					   start, count, num);
			if (retval)
				goto errout;
			if (count > max)
				count -= max - start;
			else
				break;
			start = 0;
		} else
			start -= max;
		bp += num;
		if (level == 0) {
			num = 1;
			max = 1;
		}
	}
	retval = 0;
errout:
	if (buf)
		ext2fs_free_mem(&buf);
	return retval;
}