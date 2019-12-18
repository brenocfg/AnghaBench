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
struct mntent {int /*<<< orphan*/  mnt_fsname; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  MOUNTED ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  endmntent (int /*<<< orphan*/ *) ; 
 struct mntent* getmntent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * setmntent (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
check_mount (char *device_name)
{
#ifndef _WIN32
  FILE *f;
  struct mntent *mnt;

  if ((f = setmntent (MOUNTED, "r")) == NULL)
    return;
  while ((mnt = getmntent (f)) != NULL)
    if (strcmp (device_name, mnt->mnt_fsname) == 0)
      die ("%s contains a mounted file system.");
  endmntent (f);
#endif
}