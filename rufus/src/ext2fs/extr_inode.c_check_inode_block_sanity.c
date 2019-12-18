#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ext2_inode_large {int dummy; } ;
typedef  TYPE_1__* ext2_inode_scan ;
typedef  unsigned int ext2_ino_t ;
typedef  unsigned int blk64_t ;
struct TYPE_8__ {unsigned int blocksize; int /*<<< orphan*/  super; } ;
struct TYPE_7__ {int scan_flags; unsigned int inodes_left; unsigned int inode_size; unsigned int current_inode; TYPE_2__* fs; scalar_t__ inode_buffer; int /*<<< orphan*/  inode_buffer_blocks; } ;

/* Variables and functions */
 unsigned int EXT2_INODES_PER_BLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXT2_INODE_SIZE (int /*<<< orphan*/ ) ; 
 int EXT2_SF_WARN_GARBAGE_INODES ; 
 char IBLOCK_STATUS_CSUMS_OK ; 
 char IBLOCK_STATUS_INSANE ; 
 char* SCAN_BLOCK_STATUS (TYPE_1__*) ; 
 scalar_t__ block_map_looks_insane (TYPE_2__*,struct ext2_inode_large*) ; 
 int /*<<< orphan*/  ext2fs_free_mem (struct ext2_inode_large**) ; 
 scalar_t__ ext2fs_get_mem (int /*<<< orphan*/ ,struct ext2_inode_large**) ; 
 scalar_t__ ext2fs_inode_csum_verify (TYPE_2__*,unsigned int,struct ext2_inode_large*) ; 
 int /*<<< orphan*/  ext2fs_swap_inode_full (TYPE_2__*,struct ext2_inode_large*,struct ext2_inode_large*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ extent_head_looks_insane (struct ext2_inode_large*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void check_inode_block_sanity(ext2_inode_scan scan, blk64_t num_blocks)
{
	ext2_ino_t	ino, inodes_to_scan;
	unsigned int	badness, checksum_failures;
	unsigned int	inodes_in_buf, inodes_per_block;
	char		*p;
	struct ext2_inode_large *inode;
	char		*block_status;
	unsigned int	blk, bad_csum;

	if (!(scan->scan_flags & EXT2_SF_WARN_GARBAGE_INODES))
		return;

	inodes_to_scan = scan->inodes_left;
	inodes_in_buf = num_blocks * scan->fs->blocksize / scan->inode_size;
	if (inodes_to_scan > inodes_in_buf)
		inodes_to_scan = inodes_in_buf;

	p = (char *) scan->inode_buffer;
	ino = scan->current_inode + 1;
	checksum_failures = badness = 0;
	block_status = SCAN_BLOCK_STATUS(scan);
	memset(block_status, 0, scan->inode_buffer_blocks);
	inodes_per_block = EXT2_INODES_PER_BLOCK(scan->fs->super);

	if (inodes_per_block < 2)
		return;

#ifdef WORDS_BIGENDIAN
	if (ext2fs_get_mem(EXT2_INODE_SIZE(scan->fs->super), &inode))
		return;
#endif

	while (inodes_to_scan > 0) {
		blk = (p - (char *)scan->inode_buffer) / scan->fs->blocksize;
		bad_csum = ext2fs_inode_csum_verify(scan->fs, ino,
				(struct ext2_inode_large *) p) == 0;

#ifdef WORDS_BIGENDIAN
		ext2fs_swap_inode_full(scan->fs,
			       (struct ext2_inode_large *) inode,
			       (struct ext2_inode_large *) p,
			       0, EXT2_INODE_SIZE(scan->fs->super));
#else
		inode = (struct ext2_inode_large *) p;
#endif

		/* Is this inode insane? */
		if (bad_csum) {
			checksum_failures++;
			badness++;
		} else if (extent_head_looks_insane(inode) ||
			   block_map_looks_insane(scan->fs, inode))
			badness++;

		/* If more than half are insane, declare the whole block bad */
		if (badness > inodes_per_block / 2) {
			unsigned int ino_adj;

			block_status[blk] |= IBLOCK_STATUS_INSANE;
			ino_adj = inodes_per_block -
						((ino - 1) % inodes_per_block);
			if (ino_adj > inodes_to_scan)
				ino_adj = inodes_to_scan;
			inodes_to_scan -= ino_adj;
			p += scan->inode_size * ino_adj;
			ino += ino_adj;
			checksum_failures = badness = 0;
			continue;
		}

		if ((ino % inodes_per_block) == 0) {
			if (checksum_failures == 0)
				block_status[blk] |= IBLOCK_STATUS_CSUMS_OK;
			checksum_failures = badness = 0;
		}
		inodes_to_scan--;
		p += scan->inode_size;
		ino++;
	};

#ifdef WORDS_BIGENDIAN
	ext2fs_free_mem(&inode);
#endif
}