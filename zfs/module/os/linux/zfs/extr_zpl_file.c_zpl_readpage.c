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
struct page {TYPE_1__* mapping; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  fstrans_cookie_t ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ClearPageError (struct page*) ; 
 int /*<<< orphan*/  ClearPageUptodate (struct page*) ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int /*<<< orphan*/  SetPageError (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  flush_dcache_page (struct page*) ; 
 int /*<<< orphan*/  spl_fstrans_mark () ; 
 int /*<<< orphan*/  spl_fstrans_unmark (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int zfs_getpage (struct inode*,struct page**,int) ; 

__attribute__((used)) static int
zpl_readpage(struct file *filp, struct page *pp)
{
	struct inode *ip;
	struct page *pl[1];
	int error = 0;
	fstrans_cookie_t cookie;

	ASSERT(PageLocked(pp));
	ip = pp->mapping->host;
	pl[0] = pp;

	cookie = spl_fstrans_mark();
	error = -zfs_getpage(ip, pl, 1);
	spl_fstrans_unmark(cookie);

	if (error) {
		SetPageError(pp);
		ClearPageUptodate(pp);
	} else {
		ClearPageError(pp);
		SetPageUptodate(pp);
		flush_dcache_page(pp);
	}

	unlock_page(pp);
	return (error);
}