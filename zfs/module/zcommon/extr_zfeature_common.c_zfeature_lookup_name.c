#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  fi_uname; int /*<<< orphan*/  fi_zfs_mod_supported; } ;
typedef  TYPE_1__ zfeature_info_t ;
typedef  size_t spa_feature_t ;

/* Variables and functions */
 int ENOENT ; 
 size_t SPA_FEATURES ; 
 TYPE_1__* spa_feature_table ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

int
zfeature_lookup_name(const char *name, spa_feature_t *res)
{
	for (spa_feature_t i = 0; i < SPA_FEATURES; i++) {
		zfeature_info_t *feature = &spa_feature_table[i];
		if (!feature->fi_zfs_mod_supported)
			continue;
		if (strcmp(name, feature->fi_uname) == 0) {
			if (res != NULL)
				*res = i;
			return (0);
		}
	}

	return (ENOENT);
}