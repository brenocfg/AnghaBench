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
struct ext2_inode_large {scalar_t__ i_extra_isize; int /*<<< orphan*/  i_checksum_hi; int /*<<< orphan*/  i_checksum_lo; } ;
struct ext2_inode {int dummy; } ;
typedef  int /*<<< orphan*/  ext2_ino_t ;
typedef  TYPE_1__* ext2_filsys ;
typedef  scalar_t__ errcode_t ;
typedef  int __u32 ;
struct TYPE_4__ {int /*<<< orphan*/  super; } ;

/* Variables and functions */
 scalar_t__ EXT2_GOOD_OLD_INODE_SIZE ; 
 scalar_t__ EXT2_INODE_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ EXT4_INODE_CSUM_HI_EXTRA_END ; 
 int /*<<< orphan*/  ext2fs_has_feature_metadata_csum (int /*<<< orphan*/ ) ; 
 scalar_t__ ext2fs_inode_csum (TYPE_1__*,int /*<<< orphan*/ ,struct ext2_inode_large*,int*,unsigned int) ; 
 int ext2fs_le16_to_cpu (int /*<<< orphan*/ ) ; 

int ext2fs_inode_csum_verify(ext2_filsys fs, ext2_ino_t inum,
			     struct ext2_inode_large *inode)
{
	errcode_t retval;
	__u32 provided, calculated;
	unsigned int i, has_hi;
	char *cp;

	if (!ext2fs_has_feature_metadata_csum(fs->super))
		return 1;

	has_hi = (EXT2_INODE_SIZE(fs->super) > EXT2_GOOD_OLD_INODE_SIZE &&
		  inode->i_extra_isize >= EXT4_INODE_CSUM_HI_EXTRA_END);

	provided = ext2fs_le16_to_cpu(inode->i_checksum_lo);
	retval = ext2fs_inode_csum(fs, inum, inode, &calculated, has_hi);
	if (retval)
		return 0;
	if (has_hi) {
		__u32 hi = ext2fs_le16_to_cpu(inode->i_checksum_hi);
		provided |= hi << 16;
	} else
		calculated &= 0xFFFF;

	if (provided == calculated)
		return 1;

	/*
	 * If the checksum didn't match, it's possible it was due to
	 * the inode being all zero's.  It's unlikely this is the
	 * case, but it can happen.  So check for it here.  (We only
	 * check the base inode since that's good enough, and it's not
	 * worth the bother to figure out how much of the extended
	 * inode, if any, is present.)
	 */
	for (cp = (char *) inode, i = 0;
	     i < sizeof(struct ext2_inode);
	     cp++, i++)
		if (*cp)
			return 0;
	return 1;		/* Inode must have been all zero's */
}