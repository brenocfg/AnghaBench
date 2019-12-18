#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  z_id; } ;
typedef  TYPE_2__ znode_t ;
struct TYPE_11__ {int /*<<< orphan*/ * z_log; TYPE_1__* z_os; } ;
typedef  TYPE_3__ zfsvfs_t ;
struct writeback_control {int sync_mode; } ;
struct address_space {int /*<<< orphan*/  host; } ;
typedef  enum writeback_sync_modes { ____Placeholder_writeback_sync_modes } writeback_sync_modes ;
struct TYPE_9__ {scalar_t__ os_sync; } ;

/* Variables and functions */
 TYPE_2__* ITOZ (int /*<<< orphan*/ ) ; 
 TYPE_3__* ITOZSB (int /*<<< orphan*/ ) ; 
 int WB_SYNC_ALL ; 
 int WB_SYNC_NONE ; 
 int /*<<< orphan*/  ZFS_ENTER (TYPE_3__*) ; 
 int /*<<< orphan*/  ZFS_EXIT (TYPE_3__*) ; 
 scalar_t__ ZFS_SYNC_ALWAYS ; 
 int /*<<< orphan*/  ZFS_VERIFY_ZP (TYPE_2__*) ; 
 int write_cache_pages (struct address_space*,struct writeback_control*,int /*<<< orphan*/ ,struct address_space*) ; 
 int /*<<< orphan*/  zil_commit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zpl_putpage ; 

__attribute__((used)) static int
zpl_writepages(struct address_space *mapping, struct writeback_control *wbc)
{
	znode_t		*zp = ITOZ(mapping->host);
	zfsvfs_t	*zfsvfs = ITOZSB(mapping->host);
	enum writeback_sync_modes sync_mode;
	int result;

	ZFS_ENTER(zfsvfs);
	if (zfsvfs->z_os->os_sync == ZFS_SYNC_ALWAYS)
		wbc->sync_mode = WB_SYNC_ALL;
	ZFS_EXIT(zfsvfs);
	sync_mode = wbc->sync_mode;

	/*
	 * We don't want to run write_cache_pages() in SYNC mode here, because
	 * that would make putpage() wait for a single page to be committed to
	 * disk every single time, resulting in atrocious performance. Instead
	 * we run it once in non-SYNC mode so that the ZIL gets all the data,
	 * and then we commit it all in one go.
	 */
	wbc->sync_mode = WB_SYNC_NONE;
	result = write_cache_pages(mapping, wbc, zpl_putpage, mapping);
	if (sync_mode != wbc->sync_mode) {
		ZFS_ENTER(zfsvfs);
		ZFS_VERIFY_ZP(zp);
		if (zfsvfs->z_log != NULL)
			zil_commit(zfsvfs->z_log, zp->z_id);
		ZFS_EXIT(zfsvfs);

		/*
		 * We need to call write_cache_pages() again (we can't just
		 * return after the commit) because the previous call in
		 * non-SYNC mode does not guarantee that we got all the dirty
		 * pages (see the implementation of write_cache_pages() for
		 * details). That being said, this is a no-op in most cases.
		 */
		wbc->sync_mode = sync_mode;
		result = write_cache_pages(mapping, wbc, zpl_putpage, mapping);
	}
	return (result);
}