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
struct TYPE_3__ {int /*<<< orphan*/  spa_root_vdev; int /*<<< orphan*/  spa_label_features; } ;
typedef  TYPE_1__ spa_t ;

/* Variables and functions */
 scalar_t__ nvlist_remove_all (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  vdev_config_dirty (int /*<<< orphan*/ ) ; 

void
spa_deactivate_mos_feature(spa_t *spa, const char *feature)
{
	if (nvlist_remove_all(spa->spa_label_features, feature) == 0)
		vdev_config_dirty(spa->spa_root_vdev);
}