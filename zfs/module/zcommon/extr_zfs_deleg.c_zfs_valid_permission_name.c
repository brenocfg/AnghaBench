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
 int permset_namecheck (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_deleg_canonicalize_perm (char const*) ; 

__attribute__((used)) static int
zfs_valid_permission_name(const char *perm)
{
	if (zfs_deleg_canonicalize_perm(perm))
		return (0);

	return (permset_namecheck(perm, NULL, NULL));
}