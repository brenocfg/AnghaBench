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
typedef  int /*<<< orphan*/  zed_strings_t ;
struct zed_conf {char* zedlet_dir; int /*<<< orphan*/ * zedlets; scalar_t__ do_verbose; int /*<<< orphan*/  do_force; } ;
struct stat {int st_mode; scalar_t__ st_uid; } ;
struct dirent {char* d_name; } ;
typedef  int /*<<< orphan*/  pathname ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int EINVAL ; 
 int ENAMETOOLONG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  LOG_NOTICE ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  S_ISREG (int) ; 
 int S_IWGRP ; 
 int S_IWOTH ; 
 int S_IXUSR ; 
 scalar_t__ closedir (int /*<<< orphan*/ *) ; 
 int errno ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int snprintf (char*,int,char*,char*,char*) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int /*<<< orphan*/  zed_log_msg (int /*<<< orphan*/ ,char*,char*,...) ; 
 scalar_t__ zed_strings_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * zed_strings_create () ; 
 int /*<<< orphan*/  zed_strings_destroy (int /*<<< orphan*/ *) ; 

int
zed_conf_scan_dir(struct zed_conf *zcp)
{
	zed_strings_t *zedlets;
	DIR *dirp;
	struct dirent *direntp;
	char pathname[PATH_MAX];
	struct stat st;
	int n;

	if (!zcp) {
		errno = EINVAL;
		zed_log_msg(LOG_ERR, "Failed to scan zedlet dir: %s",
		    strerror(errno));
		return (-1);
	}
	zedlets = zed_strings_create();
	if (!zedlets) {
		errno = ENOMEM;
		zed_log_msg(LOG_WARNING, "Failed to scan dir \"%s\": %s",
		    zcp->zedlet_dir, strerror(errno));
		return (-1);
	}
	dirp = opendir(zcp->zedlet_dir);
	if (!dirp) {
		int errno_bak = errno;
		zed_log_msg(LOG_WARNING, "Failed to open dir \"%s\": %s",
		    zcp->zedlet_dir, strerror(errno));
		zed_strings_destroy(zedlets);
		errno = errno_bak;
		return (-1);
	}
	while ((direntp = readdir(dirp))) {
		if (direntp->d_name[0] == '.')
			continue;

		n = snprintf(pathname, sizeof (pathname),
		    "%s/%s", zcp->zedlet_dir, direntp->d_name);
		if ((n < 0) || (n >= sizeof (pathname))) {
			zed_log_msg(LOG_WARNING, "Failed to stat \"%s\": %s",
			    direntp->d_name, strerror(ENAMETOOLONG));
			continue;
		}
		if (stat(pathname, &st) < 0) {
			zed_log_msg(LOG_WARNING, "Failed to stat \"%s\": %s",
			    pathname, strerror(errno));
			continue;
		}
		if (!S_ISREG(st.st_mode)) {
			zed_log_msg(LOG_INFO,
			    "Ignoring \"%s\": not a regular file",
			    direntp->d_name);
			continue;
		}
		if ((st.st_uid != 0) && !zcp->do_force) {
			zed_log_msg(LOG_NOTICE,
			    "Ignoring \"%s\": not owned by root",
			    direntp->d_name);
			continue;
		}
		if (!(st.st_mode & S_IXUSR)) {
			zed_log_msg(LOG_INFO,
			    "Ignoring \"%s\": not executable by user",
			    direntp->d_name);
			continue;
		}
		if ((st.st_mode & S_IWGRP) && !zcp->do_force) {
			zed_log_msg(LOG_NOTICE,
			    "Ignoring \"%s\": writable by group",
			    direntp->d_name);
			continue;
		}
		if ((st.st_mode & S_IWOTH) && !zcp->do_force) {
			zed_log_msg(LOG_NOTICE,
			    "Ignoring \"%s\": writable by other",
			    direntp->d_name);
			continue;
		}
		if (zed_strings_add(zedlets, NULL, direntp->d_name) < 0) {
			zed_log_msg(LOG_WARNING,
			    "Failed to register \"%s\": %s",
			    direntp->d_name, strerror(errno));
			continue;
		}
		if (zcp->do_verbose)
			zed_log_msg(LOG_INFO,
			    "Registered zedlet \"%s\"", direntp->d_name);
	}
	if (closedir(dirp) < 0) {
		int errno_bak = errno;
		zed_log_msg(LOG_WARNING, "Failed to close dir \"%s\": %s",
		    zcp->zedlet_dir, strerror(errno));
		zed_strings_destroy(zedlets);
		errno = errno_bak;
		return (-1);
	}
	if (zcp->zedlets)
		zed_strings_destroy(zcp->zedlets);

	zcp->zedlets = zedlets;
	return (0);
}