#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int zfs_type; } ;
typedef  TYPE_1__ zfs_handle_t ;
struct zfs_open_bookmarks_cb_data {char const* member_0; TYPE_1__* zhp; int /*<<< orphan*/ * member_1; } ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  int /*<<< orphan*/  errbuf ;
typedef  int /*<<< orphan*/  dsname ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  EZFS_BADTYPE ; 
 int /*<<< orphan*/  EZFS_INVALIDNAME ; 
 int /*<<< orphan*/  EZFS_NOENT ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int /*<<< orphan*/  assert (int) ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ errno ; 
 TYPE_1__* make_dataset_handle (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 int /*<<< orphan*/  zfs_close (TYPE_1__*) ; 
 int /*<<< orphan*/  zfs_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ zfs_iter_bookmarks (TYPE_1__*,int /*<<< orphan*/ ,struct zfs_open_bookmarks_cb_data*) ; 
 int /*<<< orphan*/  zfs_open_bookmarks_cb ; 
 int /*<<< orphan*/  zfs_standard_error (int /*<<< orphan*/ *,scalar_t__,char*) ; 
 int /*<<< orphan*/  zfs_validate_name (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ) ; 

zfs_handle_t *
zfs_open(libzfs_handle_t *hdl, const char *path, int types)
{
	zfs_handle_t *zhp;
	char errbuf[1024];
	char *bookp;

	(void) snprintf(errbuf, sizeof (errbuf),
	    dgettext(TEXT_DOMAIN, "cannot open '%s'"), path);

	/*
	 * Validate the name before we even try to open it.
	 */
	if (!zfs_validate_name(hdl, path, types, B_FALSE)) {
		(void) zfs_error(hdl, EZFS_INVALIDNAME, errbuf);
		return (NULL);
	}

	/*
	 * Bookmarks needs to be handled separately.
	 */
	bookp = strchr(path, '#');
	if (bookp == NULL) {
		/*
		 * Try to get stats for the dataset, which will tell us if it
		 * exists.
		 */
		errno = 0;
		if ((zhp = make_dataset_handle(hdl, path)) == NULL) {
			(void) zfs_standard_error(hdl, errno, errbuf);
			return (NULL);
		}
	} else {
		char dsname[ZFS_MAX_DATASET_NAME_LEN];
		zfs_handle_t *pzhp;
		struct zfs_open_bookmarks_cb_data cb_data = {path, NULL};

		/*
		 * We need to cut out '#' and everything after '#'
		 * to get the parent dataset name only.
		 */
		assert(bookp - path < sizeof (dsname));
		(void) strncpy(dsname, path, bookp - path);
		dsname[bookp - path] = '\0';

		/*
		 * Create handle for the parent dataset.
		 */
		errno = 0;
		if ((pzhp = make_dataset_handle(hdl, dsname)) == NULL) {
			(void) zfs_standard_error(hdl, errno, errbuf);
			return (NULL);
		}

		/*
		 * Iterate bookmarks to find the right one.
		 */
		errno = 0;
		if ((zfs_iter_bookmarks(pzhp, zfs_open_bookmarks_cb,
		    &cb_data) == 0) && (cb_data.zhp == NULL)) {
			(void) zfs_error(hdl, EZFS_NOENT, errbuf);
			zfs_close(pzhp);
			return (NULL);
		}
		if (cb_data.zhp == NULL) {
			(void) zfs_standard_error(hdl, errno, errbuf);
			zfs_close(pzhp);
			return (NULL);
		}
		zhp = cb_data.zhp;

		/*
		 * Cleanup.
		 */
		zfs_close(pzhp);
	}

	if (!(types & zhp->zfs_type)) {
		(void) zfs_error(hdl, EZFS_BADTYPE, errbuf);
		zfs_close(zhp);
		return (NULL);
	}

	return (zhp);
}