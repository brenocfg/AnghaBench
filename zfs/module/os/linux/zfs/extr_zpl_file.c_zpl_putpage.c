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
struct writeback_control {int dummy; } ;
struct page {int dummy; } ;
struct address_space {int /*<<< orphan*/  host; } ;
typedef  int /*<<< orphan*/  fstrans_cookie_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int PageLocked (struct page*) ; 
 int /*<<< orphan*/  PageWriteback (struct page*) ; 
 int /*<<< orphan*/  spl_fstrans_mark () ; 
 int /*<<< orphan*/  spl_fstrans_unmark (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_putpage (int /*<<< orphan*/ ,struct page*,struct writeback_control*) ; 

int
zpl_putpage(struct page *pp, struct writeback_control *wbc, void *data)
{
	struct address_space *mapping = data;
	fstrans_cookie_t cookie;

	ASSERT(PageLocked(pp));
	ASSERT(!PageWriteback(pp));

	cookie = spl_fstrans_mark();
	(void) zfs_putpage(mapping->host, pp, wbc);
	spl_fstrans_unmark(cookie);

	return (0);
}