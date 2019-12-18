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
struct kiocb {struct file* ki_filp; } ;
struct iovec {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mode; } ;
struct file {struct address_space* f_mapping; } ;
struct address_space {struct inode* host; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int S_ISBLK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UIO_USERSPACE ; 
 int /*<<< orphan*/  VERIFY_READ ; 
 scalar_t__ generic_segment_checks (struct iovec const*,unsigned long*,size_t*,int /*<<< orphan*/ ) ; 
 scalar_t__ generic_write_checks (struct file*,int /*<<< orphan*/ *,size_t*,int) ; 
 scalar_t__ zpl_iter_write_common (struct kiocb*,struct iovec const*,unsigned long,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
zpl_aio_write(struct kiocb *kiocb, const struct iovec *iovp,
    unsigned long nr_segs, loff_t pos)
{
	struct file *file = kiocb->ki_filp;
	struct address_space *mapping = file->f_mapping;
	struct inode *ip = mapping->host;
	int isblk = S_ISBLK(ip->i_mode);
	size_t count;
	ssize_t ret;

	ret = generic_segment_checks(iovp, &nr_segs, &count, VERIFY_READ);
	if (ret)
		return (ret);

	ret = generic_write_checks(file, &pos, &count, isblk);
	if (ret)
		return (ret);

	return (zpl_iter_write_common(kiocb, iovp, nr_segs, count,
	    UIO_USERSPACE, 0));
}