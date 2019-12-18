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
typedef  TYPE_1__* ext2_filsys ;
typedef  int /*<<< orphan*/  errcode_t ;
typedef  int /*<<< orphan*/  blk_t ;
struct TYPE_3__ {int blocksize; int flags; int /*<<< orphan*/  io; } ;

/* Variables and functions */
 int EXT2_FLAG_IMAGE_FILE ; 
 int /*<<< orphan*/  ext2fs_swab32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_channel_write_blk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void*) ; 

errcode_t ext2fs_write_ind_block(ext2_filsys fs, blk_t blk, void *buf)
{
#ifdef WORDS_BIGENDIAN
	blk_t		*block_nr;
	int		i;
	int		limit = fs->blocksize >> 2;
#endif

	if (fs->flags & EXT2_FLAG_IMAGE_FILE)
		return 0;

#ifdef WORDS_BIGENDIAN
	block_nr = (blk_t *) buf;
	for (i = 0; i < limit; i++, block_nr++)
		*block_nr = ext2fs_swab32(*block_nr);
#endif
	return io_channel_write_blk(fs->io, blk, 1, buf);
}