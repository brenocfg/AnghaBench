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
typedef  int /*<<< orphan*/  fstrans_cookie_t ;

/* Variables and functions */
 int /*<<< orphan*/  spl_fstrans_mark () ; 
 int /*<<< orphan*/  spl_fstrans_unmark (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_dirty_inode (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
zpl_dirty_inode(struct inode *ip)
{
	fstrans_cookie_t cookie;

	cookie = spl_fstrans_mark();
	zfs_dirty_inode(ip, 0);
	spl_fstrans_unmark(cookie);
}