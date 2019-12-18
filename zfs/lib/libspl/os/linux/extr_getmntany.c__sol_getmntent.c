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
struct mnttab {int /*<<< orphan*/  mnt_mntopts; int /*<<< orphan*/  mnt_fstype; int /*<<< orphan*/  mnt_mountp; int /*<<< orphan*/  mnt_special; } ;
struct mntent {int /*<<< orphan*/  mnt_opts; int /*<<< orphan*/  mnt_type; int /*<<< orphan*/  mnt_dir; int /*<<< orphan*/  mnt_fsname; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  BUFSIZE ; 
 int MNT_TOOLONG ; 
 int /*<<< orphan*/  buf ; 
 scalar_t__ feof (int /*<<< orphan*/ *) ; 
 struct mntent* getmntent_r (int /*<<< orphan*/ *,struct mntent*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
_sol_getmntent(FILE *fp, struct mnttab *mgetp)
{
	struct mntent mntbuf;
	struct mntent *ret;

	ret = getmntent_r(fp, &mntbuf, buf, BUFSIZE);

	if (ret != NULL) {
		mgetp->mnt_special = mntbuf.mnt_fsname;
		mgetp->mnt_mountp = mntbuf.mnt_dir;
		mgetp->mnt_fstype = mntbuf.mnt_type;
		mgetp->mnt_mntopts = mntbuf.mnt_opts;
		return (0);
	}

	if (feof(fp))
		return (-1);

	return (MNT_TOOLONG);
}