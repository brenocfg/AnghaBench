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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ZPOOL_WAIT_ACTIVITY ; 
 int /*<<< orphan*/  ZPOOL_WAIT_TAG ; 
 int /*<<< orphan*/  ZPOOL_WAIT_WAITED ; 
 int /*<<< orphan*/  fnvlist_add_boolean_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_lookup_int32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int spa_wait (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int spa_wait_tag (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zfs_ioc_wait(const char *name, nvlist_t *innvl, nvlist_t *outnvl)
{
	int32_t activity;
	uint64_t tag;
	boolean_t waited;
	int error;

	if (nvlist_lookup_int32(innvl, ZPOOL_WAIT_ACTIVITY, &activity) != 0)
		return (EINVAL);

	if (nvlist_lookup_uint64(innvl, ZPOOL_WAIT_TAG, &tag) == 0)
		error = spa_wait_tag(name, activity, tag, &waited);
	else
		error = spa_wait(name, activity, &waited);

	if (error == 0)
		fnvlist_add_boolean_value(outnvl, ZPOOL_WAIT_WAITED, waited);

	return (error);
}