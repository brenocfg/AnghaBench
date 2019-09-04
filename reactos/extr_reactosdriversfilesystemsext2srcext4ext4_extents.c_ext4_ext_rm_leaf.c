#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct inode {int dummy; } ;
struct ext4_extent_header {scalar_t__ eh_entries; } ;
struct ext4_extent {int /*<<< orphan*/  ee_block; void* ee_len; } ;
struct ext4_ext_path {int /*<<< orphan*/ * p_bh; struct ext4_extent* p_ext; struct ext4_extent_header* p_hdr; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct ext4_extent* EXT_FIRST_EXTENT (struct ext4_extent_header*) ; 
 struct ext4_extent* EXT_LAST_EXTENT (struct ext4_extent_header*) ; 
 unsigned long long EXT_MAX_BLOCKS ; 
 void* cpu_to_le16 (unsigned int) ; 
 int /*<<< orphan*/  cpu_to_le32 (unsigned int) ; 
 int ext4_ext_correct_indexes (void*,int /*<<< orphan*/ *,struct inode*,struct ext4_ext_path*) ; 
 int ext4_ext_dirty (void*,int /*<<< orphan*/ *,struct inode*,struct ext4_ext_path*) ; 
 int ext4_ext_get_access (void*,int /*<<< orphan*/ *,struct inode*,struct ext4_ext_path*) ; 
 unsigned short ext4_ext_get_actual_len (struct ext4_extent*) ; 
 int ext4_ext_rm_idx (void*,int /*<<< orphan*/ *,struct inode*,struct ext4_ext_path*) ; 
 int /*<<< orphan*/  ext4_ext_store_pblock (struct ext4_extent*,int /*<<< orphan*/ ) ; 
 int ext4_remove_blocks (void*,int /*<<< orphan*/ *,struct inode*,struct ext4_extent*,unsigned int,unsigned int) ; 
 struct ext4_extent_header* ext_block_hdr (int /*<<< orphan*/ *) ; 
 int ext_depth (struct inode*) ; 
 unsigned int le16_to_cpu (scalar_t__) ; 
 unsigned long le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ext4_ext_rm_leaf(void *icb, handle_t *handle, struct inode *inode,
		struct ext4_ext_path *path, unsigned long start)
{
	int err = 0, correct_index = 0;
	int depth = ext_depth(inode), credits;
	struct ext4_extent_header *eh;
	unsigned a, b, block, num;
	unsigned long ex_ee_block;
	unsigned short ex_ee_len;
	struct ext4_extent *ex;

	/* the header must be checked already in ext4_ext_remove_space() */
	if (!path[depth].p_hdr)
		path[depth].p_hdr = ext_block_hdr(path[depth].p_bh);
	eh = path[depth].p_hdr;
	BUG_ON(eh == NULL);

	/* find where to start removing */
	ex = EXT_LAST_EXTENT(eh);

	ex_ee_block = le32_to_cpu(ex->ee_block);
	ex_ee_len = ext4_ext_get_actual_len(ex);

	while (ex >= EXT_FIRST_EXTENT(eh) &&
			ex_ee_block + ex_ee_len > start) {
		path[depth].p_ext = ex;

		a = ex_ee_block > start ? ex_ee_block : start;
		b = (unsigned long long)ex_ee_block + ex_ee_len - 1 < 
			EXT_MAX_BLOCKS ? ex_ee_block + ex_ee_len - 1 : EXT_MAX_BLOCKS;


		if (a != ex_ee_block && b != ex_ee_block + ex_ee_len - 1) {
			block = 0;
			num = 0;
			BUG();
		} else if (a != ex_ee_block) {
			/* remove tail of the extent */
			block = ex_ee_block;
			num = a - block;
		} else if (b != ex_ee_block + ex_ee_len - 1) {
			/* remove head of the extent */
			block = a;
			num = b - a;
			/* there is no "make a hole" API yet */
			BUG();
		} else {
			/* remove whole extent: excellent! */
			block = ex_ee_block;
			num = 0;
			BUG_ON(a != ex_ee_block);
			BUG_ON(b != ex_ee_block + ex_ee_len - 1);
		}

		/* at present, extent can't cross block group */
		/* leaf + bitmap + group desc + sb + inode */
		credits = 5;
		if (ex == EXT_FIRST_EXTENT(eh)) {
			correct_index = 1;
			credits += (ext_depth(inode)) + 1;
		}

		/*handle = ext4_ext_journal_restart(icb, handle, credits);*/
		/*if (IS_ERR(icb, handle)) {*/
		/*err = PTR_ERR(icb, handle);*/
		/*goto out;*/
		/*}*/

		err = ext4_ext_get_access(icb, handle, inode, path + depth);
		if (err)
			goto out;

		err = ext4_remove_blocks(icb, handle, inode, ex, a, b);
		if (err)
			goto out;

		if (num == 0) {
			/* this extent is removed entirely mark slot unused */
			ext4_ext_store_pblock(ex, 0);
			eh->eh_entries = cpu_to_le16(le16_to_cpu(eh->eh_entries)-1);
		}

		ex->ee_block = cpu_to_le32(block);
		ex->ee_len = cpu_to_le16(num);

		err = ext4_ext_dirty(icb, handle, inode, path + depth);
		if (err)
			goto out;

		ex--;
		ex_ee_block = le32_to_cpu(ex->ee_block);
		ex_ee_len = ext4_ext_get_actual_len(ex);
	}

	if (correct_index && eh->eh_entries)
		err = ext4_ext_correct_indexes(icb, handle, inode, path);

	/* if this leaf is free, then we should
	 * remove it from index block above */
	if (err == 0 && eh->eh_entries == 0 && path[depth].p_bh != NULL)
		err = ext4_ext_rm_idx(icb, handle, inode, path + depth);

out:
	return err;
}