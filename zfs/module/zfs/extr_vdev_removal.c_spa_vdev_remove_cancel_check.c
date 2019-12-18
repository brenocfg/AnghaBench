#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * spa_vdev_removal; } ;
typedef  TYPE_1__ spa_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_4__ {TYPE_1__* dp_spa; } ;

/* Variables and functions */
 int ENOTACTIVE ; 
 TYPE_2__* dmu_tx_pool (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
spa_vdev_remove_cancel_check(void *arg, dmu_tx_t *tx)
{
	spa_t *spa = dmu_tx_pool(tx)->dp_spa;

	if (spa->spa_vdev_removal == NULL)
		return (ENOTACTIVE);
	return (0);
}