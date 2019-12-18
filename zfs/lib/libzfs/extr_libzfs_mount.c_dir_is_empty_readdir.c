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
struct dirent64 {int /*<<< orphan*/  d_name; } ;
typedef  int /*<<< orphan*/  boolean_t ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  AT_FDCWD ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int O_CLOEXEC ; 
 int O_LARGEFILE ; 
 int O_NDELAY ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopendir (int) ; 
 int openat (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ) ; 
 struct dirent64* readdir64 (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static boolean_t
dir_is_empty_readdir(const char *dirname)
{
	DIR *dirp;
	struct dirent64 *dp;
	int dirfd;

	if ((dirfd = openat(AT_FDCWD, dirname,
	    O_RDONLY | O_NDELAY | O_LARGEFILE | O_CLOEXEC, 0)) < 0) {
		return (B_TRUE);
	}

	if ((dirp = fdopendir(dirfd)) == NULL) {
		(void) close(dirfd);
		return (B_TRUE);
	}

	while ((dp = readdir64(dirp)) != NULL) {

		if (strcmp(dp->d_name, ".") == 0 ||
		    strcmp(dp->d_name, "..") == 0)
			continue;

		(void) closedir(dirp);
		return (B_FALSE);
	}

	(void) closedir(dirp);
	return (B_TRUE);
}