#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ zfs_prop_t ;
struct TYPE_2__ {int /*<<< orphan*/ * z_perm; } ;

/* Variables and functions */
 scalar_t__ ZPROP_INVAL ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ *) ; 
 TYPE_1__* zfs_deleg_perm_tab ; 
 scalar_t__ zfs_name_to_prop (char const*) ; 
 scalar_t__ zfs_prop_delegatable (scalar_t__) ; 
 char const* zfs_prop_to_name (scalar_t__) ; 

const char *
zfs_deleg_canonicalize_perm(const char *perm)
{
	int i;
	zfs_prop_t prop;

	for (i = 0; zfs_deleg_perm_tab[i].z_perm != NULL; i++) {
		if (strcmp(perm, zfs_deleg_perm_tab[i].z_perm) == 0)
			return (perm);
	}

	prop = zfs_name_to_prop(perm);
	if (prop != ZPROP_INVAL && zfs_prop_delegatable(prop))
		return (zfs_prop_to_name(prop));
	return (NULL);

}