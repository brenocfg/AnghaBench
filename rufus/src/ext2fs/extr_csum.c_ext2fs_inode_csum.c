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
struct ext2_inode_large {void* i_checksum_hi; void* i_checksum_lo; int /*<<< orphan*/  i_generation; } ;
typedef  int /*<<< orphan*/  inum ;
typedef  int /*<<< orphan*/  gen ;
typedef  int /*<<< orphan*/  ext2_ino_t ;
typedef  TYPE_1__* ext2_filsys ;
typedef  int /*<<< orphan*/  errcode_t ;
typedef  int /*<<< orphan*/  __u32 ;
typedef  void* __u16 ;
struct TYPE_3__ {int /*<<< orphan*/  csum_seed; int /*<<< orphan*/  super; } ;

/* Variables and functions */
 size_t EXT2_INODE_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext2fs_cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext2fs_crc32c_le (int /*<<< orphan*/ ,unsigned char*,size_t) ; 

__attribute__((used)) static errcode_t ext2fs_inode_csum(ext2_filsys fs, ext2_ino_t inum,
			       struct ext2_inode_large *inode,
			       __u32 *crc, int has_hi)
{
	__u32 gen;
	struct ext2_inode_large *desc = inode;
	size_t size = EXT2_INODE_SIZE(fs->super);
	__u16 old_lo;
	__u16 old_hi = 0;

	old_lo = inode->i_checksum_lo;
	inode->i_checksum_lo = 0;
	if (has_hi) {
		old_hi = inode->i_checksum_hi;
		inode->i_checksum_hi = 0;
	}

	inum = ext2fs_cpu_to_le32(inum);
	gen = inode->i_generation;
	*crc = ext2fs_crc32c_le(fs->csum_seed, (unsigned char *)&inum,
				sizeof(inum));
	*crc = ext2fs_crc32c_le(*crc, (unsigned char *)&gen, sizeof(gen));
	*crc = ext2fs_crc32c_le(*crc, (unsigned char *)desc, size);

	inode->i_checksum_lo = old_lo;
	if (has_hi)
		inode->i_checksum_hi = old_hi;
	return 0;
}