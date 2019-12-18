#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct path {TYPE_1__* dentry; } ;
struct kstat {int /*<<< orphan*/  atime; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int /*<<< orphan*/  generic_fillattr (struct inode*,struct kstat*) ; 

__attribute__((used)) static int
zpl_root_getattr_impl(const struct path *path, struct kstat *stat,
    u32 request_mask, unsigned int query_flags)
{
	struct inode *ip = path->dentry->d_inode;

	generic_fillattr(ip, stat);
	stat->atime = current_time(ip);

	return (0);
}