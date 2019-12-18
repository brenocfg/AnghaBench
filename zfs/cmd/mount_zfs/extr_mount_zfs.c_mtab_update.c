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
struct mntent {char* mnt_fsname; char* mnt_dir; char* mnt_type; char* mnt_opts; scalar_t__ mnt_passno; scalar_t__ mnt_freq; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MOUNT_FILEIO ; 
 int MOUNT_SUCCESS ; 
 int addmntent (int /*<<< orphan*/ *,struct mntent*) ; 
 int /*<<< orphan*/  endmntent (int /*<<< orphan*/ *) ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int) ; 
 char* gettext (char*) ; 
 int /*<<< orphan*/ * setmntent (char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
mtab_update(char *dataset, char *mntpoint, char *type, char *mntopts)
{
	struct mntent mnt;
	FILE *fp;
	int error;

	mnt.mnt_fsname = dataset;
	mnt.mnt_dir = mntpoint;
	mnt.mnt_type = type;
	mnt.mnt_opts = mntopts ? mntopts : "";
	mnt.mnt_freq = 0;
	mnt.mnt_passno = 0;

	fp = setmntent("/etc/mtab", "a+");
	if (!fp) {
		(void) fprintf(stderr, gettext(
		    "filesystem '%s' was mounted, but /etc/mtab "
		    "could not be opened due to error %d\n"),
		    dataset, errno);
		return (MOUNT_FILEIO);
	}

	error = addmntent(fp, &mnt);
	if (error) {
		(void) fprintf(stderr, gettext(
		    "filesystem '%s' was mounted, but /etc/mtab "
		    "could not be updated due to error %d\n"),
		    dataset, errno);
		return (MOUNT_FILEIO);
	}

	(void) endmntent(fp);

	return (MOUNT_SUCCESS);
}