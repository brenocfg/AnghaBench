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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  ext4_fsblk_t ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 struct buffer_head* ERR_PTR (int) ; 
 int __ext4_ext_check (char const*,unsigned int,struct inode*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 scalar_t__ buffer_verified (struct buffer_head*) ; 
 int /*<<< orphan*/  ext_block_hdr (struct buffer_head*) ; 
 struct buffer_head* extents_bread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extents_brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  set_buffer_verified (struct buffer_head*) ; 

__attribute__((used)) static struct buffer_head *
__read_extent_tree_block(const char *function, unsigned int line,
		struct inode *inode, ext4_fsblk_t pblk, int depth,
		int flags)
{
	struct buffer_head		*bh;
	int				err;

	bh = extents_bread(inode->i_sb, pblk);
	if (!bh)
		return ERR_PTR(-ENOMEM);

	if (!buffer_uptodate(bh)) {
		err = -EIO;
		goto errout;
	}
	if (buffer_verified(bh))
		return bh;
	err = __ext4_ext_check(function, line, inode,
			ext_block_hdr(bh), depth, pblk);
	if (err)
		goto errout;
	set_buffer_verified(bh);
	return bh;
errout:
	extents_brelse(bh);
	return ERR_PTR(err);

}