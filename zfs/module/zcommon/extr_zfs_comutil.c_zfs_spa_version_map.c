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
struct TYPE_2__ {int version_zpl; int version_spa; } ;

/* Variables and functions */
 TYPE_1__* zfs_version_table ; 

int
zfs_spa_version_map(int zpl_version)
{
	int i;
	int version = -1;

	for (i = 0; zfs_version_table[i].version_zpl; i++) {
		if (zfs_version_table[i].version_zpl >= zpl_version)
			return (zfs_version_table[i].version_spa);
	}

	return (version);
}