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
typedef  int /*<<< orphan*/  libzfs_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int /*<<< orphan*/  ZFS_TYPE_FILESYSTEM ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * make_dataset_handle (int /*<<< orphan*/ *,char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  zfs_close (int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_create (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ *,char*,char const*,char*) ; 
 scalar_t__ zfs_mount (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zfs_open (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_share (int /*<<< orphan*/ *) ; 

int
create_parents(libzfs_handle_t *hdl, char *target, int prefixlen)
{
	zfs_handle_t *h;
	char *cp;
	const char *opname;

	/* make sure prefix exists */
	cp = target + prefixlen;
	if (*cp != '/') {
		assert(strchr(cp, '/') == NULL);
		h = zfs_open(hdl, target, ZFS_TYPE_FILESYSTEM);
	} else {
		*cp = '\0';
		h = zfs_open(hdl, target, ZFS_TYPE_FILESYSTEM);
		*cp = '/';
	}
	if (h == NULL)
		return (-1);
	zfs_close(h);

	/*
	 * Attempt to create, mount, and share any ancestor filesystems,
	 * up to the prefixlen-long one.
	 */
	for (cp = target + prefixlen + 1;
	    (cp = strchr(cp, '/')) != NULL; *cp = '/', cp++) {

		*cp = '\0';

		h = make_dataset_handle(hdl, target);
		if (h) {
			/* it already exists, nothing to do here */
			zfs_close(h);
			continue;
		}

		if (zfs_create(hdl, target, ZFS_TYPE_FILESYSTEM,
		    NULL) != 0) {
			opname = dgettext(TEXT_DOMAIN, "create");
			goto ancestorerr;
		}

		h = zfs_open(hdl, target, ZFS_TYPE_FILESYSTEM);
		if (h == NULL) {
			opname = dgettext(TEXT_DOMAIN, "open");
			goto ancestorerr;
		}

		if (zfs_mount(h, NULL, 0) != 0) {
			opname = dgettext(TEXT_DOMAIN, "mount");
			goto ancestorerr;
		}

		if (zfs_share(h) != 0) {
			opname = dgettext(TEXT_DOMAIN, "share");
			goto ancestorerr;
		}

		zfs_close(h);
	}

	return (0);

ancestorerr:
	zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
	    "failed to %s ancestor '%s'"), opname, target);
	return (-1);
}