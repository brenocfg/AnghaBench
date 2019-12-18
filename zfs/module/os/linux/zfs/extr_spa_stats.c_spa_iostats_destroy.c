#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  lock; TYPE_4__* kstat; } ;
struct TYPE_7__ {TYPE_3__ iostats; } ;
struct TYPE_8__ {TYPE_1__ spa_stats; } ;
typedef  TYPE_2__ spa_t ;
typedef  int /*<<< orphan*/  spa_iostats_t ;
typedef  TYPE_3__ spa_history_kstat_t ;
struct TYPE_10__ {int /*<<< orphan*/  ks_data; } ;
typedef  TYPE_4__ kstat_t ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kstat_delete (TYPE_4__*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
spa_iostats_destroy(spa_t *spa)
{
	spa_history_kstat_t *shk = &spa->spa_stats.iostats;
	kstat_t *ksp = shk->kstat;
	if (ksp) {
		kmem_free(ksp->ks_data, sizeof (spa_iostats_t));
		kstat_delete(ksp);
	}

	mutex_destroy(&shk->lock);
}