#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ext4_xattr_ref {TYPE_2__* fs; TYPE_1__* inode_ref; int /*<<< orphan*/ * OnDiskInode; void* block_loaded; int /*<<< orphan*/ * block_bh; void* IsOnDiskInodeDirty; int /*<<< orphan*/  IrpContext; } ;
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_9__ {int /*<<< orphan*/  i_file_acl; } ;
struct TYPE_8__ {scalar_t__ InodeSize; } ;
struct TYPE_7__ {TYPE_3__ Inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int EIO ; 
 scalar_t__ EXT4_GOOD_OLD_INODE_SIZE ; 
 int /*<<< orphan*/  Ext2DestroyInode (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ Ext2SaveInode (int /*<<< orphan*/ ,TYPE_2__*,TYPE_3__*) ; 
 scalar_t__ Ext2SaveInodeXattr (int /*<<< orphan*/ ,TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 void* FALSE ; 
 int /*<<< orphan*/  ext4_xattr_purge_items (struct ext4_xattr_ref*) ; 
 int ext4_xattr_write_to_disk (struct ext4_xattr_ref*) ; 
 int /*<<< orphan*/  extents_bforget (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extents_brelse (int /*<<< orphan*/ *) ; 

int ext4_fs_put_xattr_ref(struct ext4_xattr_ref *ref)
{
	int ret;
	sector_t orig_file_acl = ref->inode_ref->Inode.i_file_acl;
	ret = ext4_xattr_write_to_disk(ref);
	if (ref->IsOnDiskInodeDirty) {
		ASSERT(ref->fs->InodeSize > EXT4_GOOD_OLD_INODE_SIZE);

		/* As we may do block allocation in ext4_xattr_write_to_disk */
		if (ret)
			ref->inode_ref->Inode.i_file_acl = orig_file_acl;

		if (!ret) {
			ret = Ext2SaveInode(ref->IrpContext, ref->fs, &ref->inode_ref->Inode)
				? 0 : -EIO;
			if (!ret) {
				ret = Ext2SaveInodeXattr(ref->IrpContext,
						ref->fs,
						&ref->inode_ref->Inode,
						ref->OnDiskInode)
					? 0 : -EIO;
			}
		}
		ref->IsOnDiskInodeDirty = FALSE;
	}
	if (ref->block_loaded) {
		if (!ret)
			extents_brelse(ref->block_bh);
		else
			extents_bforget(ref->block_bh);

		ref->block_bh = NULL;
		ref->block_loaded = FALSE;
	}
	ext4_xattr_purge_items(ref);
	Ext2DestroyInode(ref->fs, ref->OnDiskInode);
	ref->OnDiskInode = NULL;
	ref->inode_ref = NULL;
	ref->fs = NULL;
	return ret;
}