#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * vdev_fru; int /*<<< orphan*/ * vdev_path; TYPE_1__* vdev_ops; } ;
typedef  TYPE_2__ vdev_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_5__ {int /*<<< orphan*/  vdev_op_leaf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ENOTSUP ; 
 int /*<<< orphan*/  SCL_ALL ; 
 TYPE_2__* spa_lookup_by_guid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 void* spa_strdup (char const*) ; 
 int /*<<< orphan*/  spa_strfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_vdev_state_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int spa_vdev_state_exit (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_writeable (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ *) ; 

int
spa_vdev_set_common(spa_t *spa, uint64_t guid, const char *value,
    boolean_t ispath)
{
	vdev_t *vd;
	boolean_t sync = B_FALSE;

	ASSERT(spa_writeable(spa));

	spa_vdev_state_enter(spa, SCL_ALL);

	if ((vd = spa_lookup_by_guid(spa, guid, B_TRUE)) == NULL)
		return (spa_vdev_state_exit(spa, NULL, ENOENT));

	if (!vd->vdev_ops->vdev_op_leaf)
		return (spa_vdev_state_exit(spa, NULL, ENOTSUP));

	if (ispath) {
		if (strcmp(value, vd->vdev_path) != 0) {
			spa_strfree(vd->vdev_path);
			vd->vdev_path = spa_strdup(value);
			sync = B_TRUE;
		}
	} else {
		if (vd->vdev_fru == NULL) {
			vd->vdev_fru = spa_strdup(value);
			sync = B_TRUE;
		} else if (strcmp(value, vd->vdev_fru) != 0) {
			spa_strfree(vd->vdev_fru);
			vd->vdev_fru = spa_strdup(value);
			sync = B_TRUE;
		}
	}

	return (spa_vdev_state_exit(spa, sync ? vd : NULL, 0));
}