#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct stat64 {scalar_t__ st_ino; int /*<<< orphan*/  member_0; } ;
struct TYPE_5__ {scalar_t__ shares; int /*<<< orphan*/  errbuf; TYPE_1__* zhp; int /*<<< orphan*/  dsmnt; } ;
typedef  TYPE_2__ differ_info_t ;
struct TYPE_4__ {int /*<<< orphan*/  zfs_hdl; } ;

/* Variables and functions */
 int /*<<< orphan*/  EZFS_DIFF ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int /*<<< orphan*/  ZDIFF_SHARESDIR ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 scalar_t__ stat64 (char*,struct stat64*) ; 
 int /*<<< orphan*/  strlcat (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 int zfs_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
find_shares_object(differ_info_t *di)
{
	char fullpath[MAXPATHLEN];
	struct stat64 sb = { 0 };

	(void) strlcpy(fullpath, di->dsmnt, MAXPATHLEN);
	(void) strlcat(fullpath, ZDIFF_SHARESDIR, MAXPATHLEN);

	if (stat64(fullpath, &sb) != 0) {
		(void) snprintf(di->errbuf, sizeof (di->errbuf),
		    dgettext(TEXT_DOMAIN, "Cannot stat %s"), fullpath);
		return (zfs_error(di->zhp->zfs_hdl, EZFS_DIFF, di->errbuf));
	}

	di->shares = (uint64_t)sb.st_ino;
	return (0);
}