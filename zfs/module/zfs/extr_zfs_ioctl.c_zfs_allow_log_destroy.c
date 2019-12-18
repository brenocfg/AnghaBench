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
 int /*<<< orphan*/  kmem_strfree (char*) ; 

__attribute__((used)) static void
zfs_allow_log_destroy(void *arg)
{
	char *poolname = arg;

	if (poolname != NULL)
		kmem_strfree(poolname);
}