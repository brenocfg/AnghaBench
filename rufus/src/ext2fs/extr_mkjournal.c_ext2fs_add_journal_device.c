#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_rdev; int /*<<< orphan*/  st_mode; } ;
struct TYPE_8__ {unsigned int h_magic; unsigned int h_blocktype; } ;
struct TYPE_9__ {int /*<<< orphan*/  s_uuid; int /*<<< orphan*/  s_nr_users; int /*<<< orphan*/ * s_users; int /*<<< orphan*/  s_blocksize; TYPE_1__ s_header; } ;
typedef  TYPE_2__ journal_superblock_t ;
typedef  TYPE_3__* ext2_filsys ;
typedef  int /*<<< orphan*/  errcode_t ;
typedef  int __u32 ;
struct TYPE_11__ {int /*<<< orphan*/  s_jnl_blocks; int /*<<< orphan*/ * s_journal_uuid; int /*<<< orphan*/  s_journal_dev; scalar_t__ s_journal_inum; int /*<<< orphan*/  s_uuid; } ;
struct TYPE_10__ {TYPE_4__* super; int /*<<< orphan*/  io; scalar_t__ blocksize; int /*<<< orphan*/  device_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2_ET_CORRUPT_JOURNAL_SB ; 
 int /*<<< orphan*/  EXT2_ET_JOURNAL_NOT_BLOCK ; 
 int /*<<< orphan*/  EXT2_ET_NO_JOURNAL_SB ; 
 int /*<<< orphan*/  EXT2_ET_UNEXPECTED_BLOCK_SIZE ; 
 int /*<<< orphan*/  JFS_MAGIC_NUMBER ; 
 int /*<<< orphan*/  JFS_SUPERBLOCK_V2 ; 
 int JFS_USERS_MAX ; 
 int SUPERBLOCK_SIZE ; 
 int /*<<< orphan*/  S_ISBLK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int ext2fs_journal_sb_start (scalar_t__) ; 
 int /*<<< orphan*/  ext2fs_mark_super_dirty (TYPE_3__*) ; 
 int /*<<< orphan*/  ext2fs_set_feature_journal (TYPE_4__*) ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  io_channel_read_blk64 (int /*<<< orphan*/ ,int,int,char*) ; 
 int /*<<< orphan*/  io_channel_write_blk64 (int /*<<< orphan*/ ,int,int,char*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 unsigned long ntohl (int /*<<< orphan*/ ) ; 
 scalar_t__ stat (int /*<<< orphan*/ ,struct stat*) ; 

errcode_t ext2fs_add_journal_device(ext2_filsys fs, ext2_filsys journal_dev)
{
	struct stat	st;
	errcode_t	retval;
	char		buf[SUPERBLOCK_SIZE];
	journal_superblock_t	*jsb;
	int		start;
	__u32		i, nr_users;

	/* Make sure the device exists and is a block device */
	if (stat(journal_dev->device_name, &st) < 0)
		return errno;

	if (!S_ISBLK(st.st_mode))
		return EXT2_ET_JOURNAL_NOT_BLOCK; /* Must be a block device */

	/* Get the journal superblock */
	start = ext2fs_journal_sb_start(journal_dev->blocksize);
	if ((retval = io_channel_read_blk64(journal_dev->io, start,
					    -SUPERBLOCK_SIZE,
					    buf)))
		return retval;

	jsb = (journal_superblock_t *) buf;
	if ((jsb->s_header.h_magic != (unsigned) ntohl(JFS_MAGIC_NUMBER)) ||
	    (jsb->s_header.h_blocktype != (unsigned) ntohl(JFS_SUPERBLOCK_V2)))
		return EXT2_ET_NO_JOURNAL_SB;

	if (ntohl(jsb->s_blocksize) != (unsigned long) fs->blocksize)
		return EXT2_ET_UNEXPECTED_BLOCK_SIZE;

	/* Check and see if this filesystem has already been added */
	nr_users = ntohl(jsb->s_nr_users);
	if (nr_users > JFS_USERS_MAX)
		return EXT2_ET_CORRUPT_JOURNAL_SB;
	for (i=0; i < nr_users; i++) {
		if (memcmp(fs->super->s_uuid,
			   &jsb->s_users[i*16], 16) == 0)
			break;
	}
	if (i >= nr_users) {
		memcpy(&jsb->s_users[nr_users*16],
		       fs->super->s_uuid, 16);
		jsb->s_nr_users = htonl(nr_users+1);
	}

	/* Writeback the journal superblock */
	if ((retval = io_channel_write_blk64(journal_dev->io, start,
					    -SUPERBLOCK_SIZE, buf)))
		return retval;

	fs->super->s_journal_inum = 0;
	fs->super->s_journal_dev = st.st_rdev;
	memcpy(fs->super->s_journal_uuid, jsb->s_uuid,
	       sizeof(fs->super->s_journal_uuid));
	memset(fs->super->s_jnl_blocks, 0, sizeof(fs->super->s_jnl_blocks));
	ext2fs_set_feature_journal(fs->super);
	ext2fs_mark_super_dirty(fs);
	return 0;
}