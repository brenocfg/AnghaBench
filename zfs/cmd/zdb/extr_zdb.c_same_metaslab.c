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
struct TYPE_3__ {int vdev_ms_shift; } ;
typedef  TYPE_1__ vdev_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int boolean_t ;

/* Variables and functions */
 TYPE_1__* vdev_lookup_top (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static boolean_t
same_metaslab(spa_t *spa, uint64_t vdev, uint64_t off1, uint64_t off2)
{
	vdev_t *vd = vdev_lookup_top(spa, vdev);
	uint64_t ms_shift = vd->vdev_ms_shift;

	return ((off1 >> ms_shift) == (off2 >> ms_shift));
}