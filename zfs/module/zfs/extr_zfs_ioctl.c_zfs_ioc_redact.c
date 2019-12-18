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
 int /*<<< orphan*/  ENXIO ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int dmu_redact_snap (char const*,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ fnvlist_num_pairs (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_lookup_nvlist (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,char*,char**) ; 

__attribute__((used)) static int
zfs_ioc_redact(const char *snapname, nvlist_t *innvl, nvlist_t *outnvl)
{
	nvlist_t *redactnvl = NULL;
	char *redactbook = NULL;

	if (nvlist_lookup_nvlist(innvl, "snapnv", &redactnvl) != 0)
		return (SET_ERROR(EINVAL));
	if (fnvlist_num_pairs(redactnvl) == 0)
		return (SET_ERROR(ENXIO));
	if (nvlist_lookup_string(innvl, "bookname", &redactbook) != 0)
		return (SET_ERROR(EINVAL));

	return (dmu_redact_snap(snapname, redactnvl, redactbook));
}