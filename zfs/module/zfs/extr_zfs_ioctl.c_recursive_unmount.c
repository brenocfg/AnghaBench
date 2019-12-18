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

/* Variables and functions */
 char* kmem_asprintf (char*,char const*,char const*) ; 
 int /*<<< orphan*/  kmem_strfree (char*) ; 
 int /*<<< orphan*/  zfs_unmount_snap (char*) ; 

__attribute__((used)) static int
recursive_unmount(const char *fsname, void *arg)
{
	const char *snapname = arg;
	char *fullname;

	fullname = kmem_asprintf("%s@%s", fsname, snapname);
	zfs_unmount_snap(fullname);
	kmem_strfree(fullname);

	return (0);
}