#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * z_os; } ;
typedef  TYPE_1__ zfsvfs_t ;
typedef  int /*<<< orphan*/  objset_t ;

/* Variables and functions */
 int /*<<< orphan*/  EILSEQ ; 
 int /*<<< orphan*/  ENAMETOOLONG ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_objset_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int strlen (char const*) ; 
 scalar_t__ zfs_component_namecheck (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zfsctl_snapshot_name(zfsvfs_t *zfsvfs, const char *snap_name, int len,
    char *full_name)
{
	objset_t *os = zfsvfs->z_os;

	if (zfs_component_namecheck(snap_name, NULL, NULL) != 0)
		return (SET_ERROR(EILSEQ));

	dmu_objset_name(os, full_name);
	if ((strlen(full_name) + 1 + strlen(snap_name)) >= len)
		return (SET_ERROR(ENAMETOOLONG));

	(void) strcat(full_name, "@");
	(void) strcat(full_name, snap_name);

	return (0);
}