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
typedef  int /*<<< orphan*/  zfs_handle_t ;
struct zfs_open_bookmarks_cb_data {int /*<<< orphan*/ * zhp; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int EEXIST ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_get_name (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zfs_open_bookmarks_cb(zfs_handle_t *zhp, void *data)
{
	struct zfs_open_bookmarks_cb_data *dp = data;

	/*
	 * Is it the one we are looking for?
	 */
	if (strcmp(dp->path, zfs_get_name(zhp)) == 0) {
		/*
		 * We found it.  Save it and let the caller know we are done.
		 */
		dp->zhp = zhp;
		return (EEXIST);
	}

	/*
	 * Not found.  Close the handle and ask for another one.
	 */
	zfs_close(zhp);
	return (0);
}