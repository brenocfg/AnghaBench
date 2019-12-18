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

/* Variables and functions */
 int /*<<< orphan*/  ZPOOL_CONFIG_FAULTED ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_OFFLINE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_REMOVED ; 
 scalar_t__ nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
vdev_is_online(nvlist_t *nv)
{
	uint64_t ival;

	if (nvlist_lookup_uint64(nv, ZPOOL_CONFIG_OFFLINE, &ival) == 0 ||
	    nvlist_lookup_uint64(nv, ZPOOL_CONFIG_FAULTED, &ival) == 0 ||
	    nvlist_lookup_uint64(nv, ZPOOL_CONFIG_REMOVED, &ival) == 0)
		return (0);

	return (1);
}