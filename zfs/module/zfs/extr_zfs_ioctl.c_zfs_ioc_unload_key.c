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
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int spa_keystore_unload_wkey (char const*) ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 

__attribute__((used)) static int
zfs_ioc_unload_key(const char *dsname, nvlist_t *innvl, nvlist_t *outnvl)
{
	int ret = 0;

	if (strchr(dsname, '@') != NULL || strchr(dsname, '%') != NULL) {
		ret = (SET_ERROR(EINVAL));
		goto out;
	}

	ret = spa_keystore_unload_wkey(dsname);
	if (ret != 0)
		goto out;

out:
	return (ret);
}