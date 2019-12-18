#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  size; int /*<<< orphan*/  private; int /*<<< orphan*/ * kstat; } ;
struct TYPE_5__ {TYPE_3__ tx_assign_histogram; } ;
struct TYPE_6__ {TYPE_1__ spa_stats; } ;
typedef  TYPE_2__ spa_t ;
typedef  TYPE_3__ spa_history_kstat_t ;
typedef  int /*<<< orphan*/  kstat_t ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kstat_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
spa_tx_assign_destroy(spa_t *spa)
{
	spa_history_kstat_t *shk = &spa->spa_stats.tx_assign_histogram;
	kstat_t *ksp;

	ksp = shk->kstat;
	if (ksp)
		kstat_delete(ksp);

	kmem_free(shk->private, shk->size);
	mutex_destroy(&shk->lock);
}