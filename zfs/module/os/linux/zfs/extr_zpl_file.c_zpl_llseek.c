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
struct inode {TYPE_2__* i_sb; } ;
struct file {TYPE_1__* f_mapping; } ;
typedef  int /*<<< orphan*/  loff_t ;
typedef  int /*<<< orphan*/  fstrans_cookie_t ;
struct TYPE_4__ {int /*<<< orphan*/  s_maxbytes; } ;
struct TYPE_3__ {struct inode* host; } ;

/* Variables and functions */
 int SEEK_DATA ; 
 int SEEK_HOLE ; 
 int /*<<< orphan*/  generic_file_llseek (struct file*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lseek_execute (struct file*,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spl_fstrans_mark () ; 
 int /*<<< orphan*/  spl_fstrans_unmark (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spl_inode_lock_shared (struct inode*) ; 
 int /*<<< orphan*/  spl_inode_unlock_shared (struct inode*) ; 
 int /*<<< orphan*/  zfs_holey (struct inode*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static loff_t
zpl_llseek(struct file *filp, loff_t offset, int whence)
{
#if defined(SEEK_HOLE) && defined(SEEK_DATA)
	fstrans_cookie_t cookie;

	if (whence == SEEK_DATA || whence == SEEK_HOLE) {
		struct inode *ip = filp->f_mapping->host;
		loff_t maxbytes = ip->i_sb->s_maxbytes;
		loff_t error;

		spl_inode_lock_shared(ip);
		cookie = spl_fstrans_mark();
		error = -zfs_holey(ip, whence, &offset);
		spl_fstrans_unmark(cookie);
		if (error == 0)
			error = lseek_execute(filp, ip, offset, maxbytes);
		spl_inode_unlock_shared(ip);

		return (error);
	}
#endif /* SEEK_HOLE && SEEK_DATA */

	return (generic_file_llseek(filp, offset, whence));
}