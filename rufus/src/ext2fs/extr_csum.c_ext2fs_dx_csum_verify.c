#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ext2_dx_tail {int /*<<< orphan*/  dt_checksum; } ;
struct ext2_dx_entry {int dummy; } ;
struct ext2_dx_countlimit {int /*<<< orphan*/  count; int /*<<< orphan*/  limit; } ;
struct ext2_dir_entry {int dummy; } ;
typedef  int /*<<< orphan*/  ext2_ino_t ;
typedef  TYPE_1__* ext2_filsys ;
typedef  scalar_t__ errcode_t ;
typedef  scalar_t__ __u32 ;
struct TYPE_5__ {int blocksize; } ;

/* Variables and functions */
 scalar_t__ __get_dx_countlimit (TYPE_1__*,struct ext2_dir_entry*,struct ext2_dx_countlimit**,int*,int) ; 
 scalar_t__ ext2fs_dx_csum (TYPE_1__*,int /*<<< orphan*/ ,struct ext2_dir_entry*,scalar_t__*,int,int,struct ext2_dx_tail*) ; 
 int ext2fs_le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ ext2fs_le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ext2fs_dx_csum_verify(ext2_filsys fs, ext2_ino_t inum,
				 struct ext2_dir_entry *dirent)
{
	__u32 calculated;
	errcode_t retval;
	struct ext2_dx_countlimit *c;
	struct ext2_dx_tail *t;
	int count_offset, limit, count;

	retval = __get_dx_countlimit(fs, dirent, &c, &count_offset, 1);
	if (retval)
		return 1;
	limit = ext2fs_le16_to_cpu(c->limit);
	count = ext2fs_le16_to_cpu(c->count);
	if (count_offset + (limit * sizeof(struct ext2_dx_entry)) >
	    fs->blocksize - sizeof(struct ext2_dx_tail))
		return 0;
	/* htree structs are accessed in LE order */
	t = (struct ext2_dx_tail *)(((struct ext2_dx_entry *)c) + limit);
	retval = ext2fs_dx_csum(fs, inum, dirent, &calculated, count_offset,
				count, t);
	if (retval)
		return 0;

	return ext2fs_le32_to_cpu(t->dt_checksum) == calculated;
}