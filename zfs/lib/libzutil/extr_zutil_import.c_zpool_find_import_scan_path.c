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
typedef  int /*<<< orphan*/  pthread_mutex_t ;
typedef  int /*<<< orphan*/  libpc_handle_t ;
typedef  int /*<<< orphan*/  avl_tree_t ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  EZFS_BADPATH ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 char* basename (char*) ; 
 int /*<<< orphan*/  dgettext (int /*<<< orphan*/ ,char*) ; 
 char* dirname (char*) ; 
 int errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * realpath (char*,char*) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int /*<<< orphan*/  zpool_find_import_scan_add_slice (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  zutil_error_aux (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zutil_error_fmt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 char* zutil_strdup (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int
zpool_find_import_scan_path(libpc_handle_t *hdl, pthread_mutex_t *lock,
    avl_tree_t *cache, const char *dir, int order)
{
	int error = 0;
	char path[MAXPATHLEN];
	char *d, *b;
	char *dpath, *name;

	/*
	 * Separate the directory part and last part of the
	 * path. We do this so that we can get the realpath of
	 * the directory. We don't get the realpath on the
	 * whole path because if it's a symlink, we want the
	 * path of the symlink not where it points to.
	 */
	d = zutil_strdup(hdl, dir);
	b = zutil_strdup(hdl, dir);
	dpath = dirname(d);
	name = basename(b);

	if (realpath(dpath, path) == NULL) {
		error = errno;
		if (error == ENOENT) {
			error = 0;
			goto out;
		}

		zutil_error_aux(hdl, strerror(error));
		(void) zutil_error_fmt(hdl, EZFS_BADPATH, dgettext(
		    TEXT_DOMAIN, "cannot resolve path '%s'"), dir);
		goto out;
	}

	zpool_find_import_scan_add_slice(hdl, lock, cache, path, name, order);

out:
	free(b);
	free(d);
	return (error);
}