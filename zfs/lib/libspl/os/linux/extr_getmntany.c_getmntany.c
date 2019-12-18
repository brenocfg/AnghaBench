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
struct mnttab {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ DIFF (int /*<<< orphan*/ ) ; 
 int _sol_getmntent (int /*<<< orphan*/ *,struct mnttab*) ; 
 int /*<<< orphan*/  mnt_fstype ; 
 int /*<<< orphan*/  mnt_mntopts ; 
 int /*<<< orphan*/  mnt_mountp ; 
 int /*<<< orphan*/  mnt_special ; 

int
getmntany(FILE *fp, struct mnttab *mgetp, struct mnttab *mrefp)
{
	int ret;

	while (
	    ((ret = _sol_getmntent(fp, mgetp)) == 0) && (
	    DIFF(mnt_special) || DIFF(mnt_mountp) ||
	    DIFF(mnt_fstype) || DIFF(mnt_mntopts))) { }

	return (ret);
}