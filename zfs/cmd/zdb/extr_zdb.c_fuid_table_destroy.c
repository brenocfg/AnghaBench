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
 scalar_t__ B_FALSE ; 
 int /*<<< orphan*/  domain_tree ; 
 scalar_t__ fuid_table_loaded ; 
 int /*<<< orphan*/  idx_tree ; 
 int /*<<< orphan*/  zfs_fuid_table_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
fuid_table_destroy(void)
{
	if (fuid_table_loaded) {
		zfs_fuid_table_destroy(&idx_tree, &domain_tree);
		fuid_table_loaded = B_FALSE;
	}
}