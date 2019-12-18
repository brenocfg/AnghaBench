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
typedef  scalar_t__ uint64_t ;
struct TYPE_2__ {scalar_t__ os_redundant_metadata; } ;
typedef  TYPE_1__ objset_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ ZFS_REDUNDANT_METADATA_ALL ; 
 scalar_t__ ZFS_REDUNDANT_METADATA_MOST ; 

__attribute__((used)) static void
redundant_metadata_changed_cb(void *arg, uint64_t newval)
{
	objset_t *os = arg;

	/*
	 * Inheritance and range checking should have been done by now.
	 */
	ASSERT(newval == ZFS_REDUNDANT_METADATA_ALL ||
	    newval == ZFS_REDUNDANT_METADATA_MOST);

	os->os_redundant_metadata = newval;
}