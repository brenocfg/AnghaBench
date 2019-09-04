#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int i_size; int i_file_acl; int /*<<< orphan*/  i_extra_isize; int /*<<< orphan*/  i_sb; int /*<<< orphan*/ * i_block; int /*<<< orphan*/  i_dtime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_generation; int /*<<< orphan*/  i_nlink; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; int /*<<< orphan*/  i_flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  l_i_file_acl_high; } ;
struct TYPE_4__ {TYPE_1__ linux2; } ;
struct ext3_inode {int /*<<< orphan*/  i_extra_isize; int /*<<< orphan*/ * i_block; int /*<<< orphan*/  i_dtime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_atime; TYPE_2__ osd2; void* i_file_acl_lo; void* i_size_high; void* i_size; int /*<<< orphan*/  i_generation; int /*<<< orphan*/  i_links_count; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; int /*<<< orphan*/  i_flags; int /*<<< orphan*/  i_mode; } ;
typedef  void* __u32 ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ EXT3_HAS_RO_COMPAT_FEATURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXT4_FEATURE_RO_COMPAT_EXTRA_ISIZE ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext3_inode_blocks_set (struct ext3_inode*,struct inode*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void Ext2EncodeInode(struct ext3_inode *dst,  struct inode *src)
{
    dst->i_mode = src->i_mode;
    dst->i_flags = src->i_flags;
    dst->i_uid = src->i_uid;
    dst->i_gid = src->i_gid;
    dst->i_links_count = src->i_nlink;
    dst->i_generation = src->i_generation;
    dst->i_size = (__u32)src->i_size;
    if (S_ISREG(src->i_mode)) {
        dst->i_size_high = (__u32)(src->i_size >> 32);
    }
    dst->i_file_acl_lo = (__u32)src->i_file_acl;
    dst->osd2.linux2.l_i_file_acl_high |= (__u16)(src->i_file_acl >> 32);
    dst->i_atime = src->i_atime;
    dst->i_ctime = src->i_ctime;
    dst->i_mtime = src->i_mtime;
    dst->i_dtime = src->i_dtime;
    dst->i_extra_isize = src->i_extra_isize;
    ASSERT(src->i_sb);
    ext3_inode_blocks_set(dst, src);
    memcpy(&dst->i_block[0], &src->i_block[0], sizeof(__u32) * 15);
    if (EXT3_HAS_RO_COMPAT_FEATURE(src->i_sb,
                                   EXT4_FEATURE_RO_COMPAT_EXTRA_ISIZE))
        dst->i_extra_isize = src->i_extra_isize;
}