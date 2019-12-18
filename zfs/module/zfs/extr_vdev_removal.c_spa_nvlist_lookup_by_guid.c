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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZPOOL_CONFIG_GUID ; 
 scalar_t__ fnvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static nvlist_t *
spa_nvlist_lookup_by_guid(nvlist_t **nvpp, int count, uint64_t target_guid)
{
	for (int i = 0; i < count; i++) {
		uint64_t guid =
		    fnvlist_lookup_uint64(nvpp[i], ZPOOL_CONFIG_GUID);

		if (guid == target_guid)
			return (nvpp[i]);
	}

	return (NULL);
}