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
struct stat64 {int /*<<< orphan*/  st_dev; } ;
struct mnttab {int dummy; } ;
struct extmnttab {int /*<<< orphan*/  mnt_minor; int /*<<< orphan*/  mnt_major; int /*<<< orphan*/  mnt_mountp; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int _sol_getmntent (int /*<<< orphan*/ *,struct mnttab*) ; 
 int /*<<< orphan*/  major (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  minor (int /*<<< orphan*/ ) ; 
 scalar_t__ stat64 (int /*<<< orphan*/ ,struct stat64*) ; 

__attribute__((used)) static int
getextmntent_impl(FILE *fp, struct extmnttab *mp, int len)
{
	int ret;
	struct stat64 st;

	ret = _sol_getmntent(fp, (struct mnttab *)mp);
	if (ret == 0) {
		if (stat64(mp->mnt_mountp, &st) != 0) {
			mp->mnt_major = 0;
			mp->mnt_minor = 0;
			return (ret);
		}
		mp->mnt_major = major(st.st_dev);
		mp->mnt_minor = minor(st.st_dev);
	}

	return (ret);
}