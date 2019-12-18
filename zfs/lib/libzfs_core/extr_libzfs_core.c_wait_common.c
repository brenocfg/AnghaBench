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
typedef  int /*<<< orphan*/  zpool_wait_activity_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZFS_IOC_WAIT ; 
 int /*<<< orphan*/  ZPOOL_WAIT_ACTIVITY ; 
 int /*<<< orphan*/  ZPOOL_WAIT_TAG ; 
 int /*<<< orphan*/  ZPOOL_WAIT_WAITED ; 
 int /*<<< orphan*/  fnvlist_add_int32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnvlist_add_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  fnvlist_free (int /*<<< orphan*/ *) ; 
 scalar_t__ fnvlist_lookup_boolean_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int lzc_ioctl (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int
wait_common(const char *pool, zpool_wait_activity_t activity, boolean_t use_tag,
    uint64_t tag, boolean_t *waited)
{
	nvlist_t *args = fnvlist_alloc();
	nvlist_t *result = NULL;

	fnvlist_add_int32(args, ZPOOL_WAIT_ACTIVITY, activity);
	if (use_tag)
		fnvlist_add_uint64(args, ZPOOL_WAIT_TAG, tag);

	int error = lzc_ioctl(ZFS_IOC_WAIT, pool, args, &result);

	if (error == 0 && waited != NULL)
		*waited = fnvlist_lookup_boolean_value(result,
		    ZPOOL_WAIT_WAITED);

	fnvlist_free(args);
	fnvlist_free(result);

	return (error);
}