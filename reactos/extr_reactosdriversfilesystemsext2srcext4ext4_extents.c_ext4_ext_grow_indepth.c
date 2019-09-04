#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_sb; } ;
struct ext4_extent_header {scalar_t__ eh_depth; void* eh_max; void* eh_entries; void* eh_magic; } ;
struct buffer_head {int /*<<< orphan*/  b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  scalar_t__ ext4_fsblk_t ;
struct TYPE_8__ {int /*<<< orphan*/  i_block; } ;
struct TYPE_7__ {int /*<<< orphan*/  ee_block; } ;
struct TYPE_6__ {int /*<<< orphan*/  ei_block; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EXT4_EXT_MAGIC ; 
 TYPE_5__* EXT4_I (struct inode*) ; 
 TYPE_4__* EXT_FIRST_EXTENT (struct ext4_extent_header*) ; 
 TYPE_1__* EXT_FIRST_INDEX (struct ext4_extent_header*) ; 
 void* cpu_to_le16 (int) ; 
 int ext4_ext_space_block (struct inode*,int /*<<< orphan*/ ) ; 
 int ext4_ext_space_block_idx (struct inode*,int /*<<< orphan*/ ) ; 
 int ext4_ext_space_root_idx (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_extent_block_csum_set (struct inode*,struct ext4_extent_header*) ; 
 int ext4_handle_dirty_metadata (void*,int /*<<< orphan*/ *,struct inode*,struct buffer_head*) ; 
 scalar_t__ ext4_idx_pblock (TYPE_1__*) ; 
 int /*<<< orphan*/  ext4_idx_store_pblock (TYPE_1__*,scalar_t__) ; 
 scalar_t__ ext4_inode_to_goal_block (struct inode*) ; 
 int ext4_journal_get_create_access (void*,int /*<<< orphan*/ *,struct buffer_head*) ; 
 int /*<<< orphan*/  ext4_mark_inode_dirty (void*,int /*<<< orphan*/ *,struct inode*) ; 
 scalar_t__ ext4_new_meta_blocks (void*,int /*<<< orphan*/ *,struct inode*,scalar_t__,unsigned int,int /*<<< orphan*/ *,int*) ; 
 struct ext4_extent_header* ext_block_hdr (struct buffer_head*) ; 
 int /*<<< orphan*/  ext_debug (char*,void*,void*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ext_depth (struct inode*) ; 
 struct ext4_extent_header* ext_inode_hdr (struct inode*) ; 
 int /*<<< orphan*/  extents_brelse (struct buffer_head*) ; 
 struct buffer_head* extents_bwrite (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  le16_add_cpu (scalar_t__*,int) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 

__attribute__((used)) static int ext4_ext_grow_indepth(void *icb, handle_t *handle, struct inode *inode,
		unsigned int flags)
{
	struct ext4_extent_header *neh;
	struct buffer_head *bh;
	ext4_fsblk_t newblock, goal = 0;
	int err = 0;

	/* Try to prepend new index to old one */
	if (ext_depth(inode))
		goal = ext4_idx_pblock(EXT_FIRST_INDEX(ext_inode_hdr(inode)));
	goal = ext4_inode_to_goal_block(inode);
	newblock = ext4_new_meta_blocks(icb, handle, inode, goal, flags,
			NULL, &err);
	if (newblock == 0)
		return err;

	bh = extents_bwrite(inode->i_sb, newblock);
	if (!bh)
		return -ENOMEM;

	err = ext4_journal_get_create_access(icb, handle, bh);
	if (err)
		goto out;

	/* move top-level index/leaf into new block */
	memmove(bh->b_data, EXT4_I(inode)->i_block,
			sizeof(EXT4_I(inode)->i_block));

	/* set size of new block */
	neh = ext_block_hdr(bh);
	/* old root could have indexes or leaves
	 * so calculate e_max right way */
	if (ext_depth(inode))
		neh->eh_max = cpu_to_le16(ext4_ext_space_block_idx(inode, 0));
	else
		neh->eh_max = cpu_to_le16(ext4_ext_space_block(inode, 0));
	neh->eh_magic = cpu_to_le16(EXT4_EXT_MAGIC);
	ext4_extent_block_csum_set(inode, neh);
	set_buffer_uptodate(bh);

	err = ext4_handle_dirty_metadata(icb, handle, inode, bh);
	if (err)
		goto out;

	/* Update top-level index: num,max,pointer */
	neh = ext_inode_hdr(inode);
	neh->eh_entries = cpu_to_le16(1);
	ext4_idx_store_pblock(EXT_FIRST_INDEX(neh), newblock);
	if (neh->eh_depth == 0) {
		/* Root extent block becomes index block */
		neh->eh_max = cpu_to_le16(ext4_ext_space_root_idx(inode, 0));
		EXT_FIRST_INDEX(neh)->ei_block =
			EXT_FIRST_EXTENT(neh)->ee_block;
	}
	ext_debug("new root: num %d(%d), lblock %d, ptr %llu\n",
			(neh->eh_entries), (neh->eh_max),
			(EXT_FIRST_INDEX(neh)->ei_block),
			ext4_idx_pblock(EXT_FIRST_INDEX(neh)));

	le16_add_cpu(&neh->eh_depth, 1);
	ext4_mark_inode_dirty(icb, handle, inode);
out:
	extents_brelse(bh);

	return err;
}