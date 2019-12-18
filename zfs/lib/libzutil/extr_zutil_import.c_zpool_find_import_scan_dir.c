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
struct dirent64 {char* d_name; } ;
typedef  int /*<<< orphan*/  pthread_mutex_t ;
typedef  int /*<<< orphan*/  libpc_handle_t ;
typedef  int /*<<< orphan*/  avl_tree_t ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  EZFS_BADPATH ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dgettext (int /*<<< orphan*/ ,char*) ; 
 int errno ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 struct dirent64* readdir64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * realpath (char const*,char*) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int /*<<< orphan*/  zpool_find_import_scan_add_slice (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char const*,int) ; 
 int /*<<< orphan*/  zutil_error_aux (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zutil_error_fmt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int
zpool_find_import_scan_dir(libpc_handle_t *hdl, pthread_mutex_t *lock,
    avl_tree_t *cache, const char *dir, int order)
{
	int error;
	char path[MAXPATHLEN];
	struct dirent64 *dp;
	DIR *dirp;

	if (realpath(dir, path) == NULL) {
		error = errno;
		if (error == ENOENT)
			return (0);

		zutil_error_aux(hdl, strerror(error));
		(void) zutil_error_fmt(hdl, EZFS_BADPATH, dgettext(
		    TEXT_DOMAIN, "cannot resolve path '%s'"), dir);
		return (error);
	}

	dirp = opendir(path);
	if (dirp == NULL) {
		error = errno;
		zutil_error_aux(hdl, strerror(error));
		(void) zutil_error_fmt(hdl, EZFS_BADPATH,
		    dgettext(TEXT_DOMAIN, "cannot open '%s'"), path);
		return (error);
	}

	while ((dp = readdir64(dirp)) != NULL) {
		const char *name = dp->d_name;
		if (name[0] == '.' &&
		    (name[1] == 0 || (name[1] == '.' && name[2] == 0)))
			continue;

		zpool_find_import_scan_add_slice(hdl, lock, cache, path, name,
		    order);
	}

	(void) closedir(dirp);
	return (0);
}