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

/* Variables and functions */
 int /*<<< orphan*/  MAX_SERDLEN ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,unsigned long long,unsigned long long,char const*) ; 

__attribute__((used)) static void
zfs_serd_name(char *buf, uint64_t pool_guid, uint64_t vdev_guid,
    const char *type)
{
	(void) snprintf(buf, MAX_SERDLEN, "zfs_%llx_%llx_%s",
	    (long long unsigned int)pool_guid,
	    (long long unsigned int)vdev_guid, type);
}