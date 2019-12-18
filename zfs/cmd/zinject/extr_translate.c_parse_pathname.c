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
struct stat64 {int dummy; } ;
struct extmnttab {char const* mnt_special; int /*<<< orphan*/  mnt_mountp; int /*<<< orphan*/  mnt_fstype; } ;

/* Variables and functions */
 int MAXPATHLEN ; 
 int /*<<< orphan*/  MNTTYPE_ZFS ; 
 int /*<<< orphan*/  compress_slashes (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ getextmntent (char*,struct extmnttab*,struct stat64*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usage () ; 

__attribute__((used)) static int
parse_pathname(const char *inpath, char *dataset, char *relpath,
    struct stat64 *statbuf)
{
	struct extmnttab mp;
	const char *rel;
	char fullpath[MAXPATHLEN];

	compress_slashes(inpath, fullpath);

	if (fullpath[0] != '/') {
		(void) fprintf(stderr, "invalid object '%s': must be full "
		    "path\n", fullpath);
		usage();
		return (-1);
	}

	if (getextmntent(fullpath, &mp, statbuf) != 0) {
		(void) fprintf(stderr, "cannot find mountpoint for '%s'\n",
		    fullpath);
		return (-1);
	}

	if (strcmp(mp.mnt_fstype, MNTTYPE_ZFS) != 0) {
		(void) fprintf(stderr, "invalid path '%s': not a ZFS "
		    "filesystem\n", fullpath);
		return (-1);
	}

	if (strncmp(fullpath, mp.mnt_mountp, strlen(mp.mnt_mountp)) != 0) {
		(void) fprintf(stderr, "invalid path '%s': mountpoint "
		    "doesn't match path\n", fullpath);
		return (-1);
	}

	(void) strcpy(dataset, mp.mnt_special);

	rel = fullpath + strlen(mp.mnt_mountp);
	if (rel[0] == '/')
		rel++;
	(void) strcpy(relpath, rel);

	return (0);
}