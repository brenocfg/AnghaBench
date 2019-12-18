#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int count; scalar_t__ private; } ;
struct TYPE_8__ {TYPE_4__ tx_assign_histogram; } ;
struct TYPE_10__ {TYPE_1__ spa_stats; } ;
typedef  TYPE_3__ spa_t ;
typedef  TYPE_4__ spa_history_kstat_t ;
struct TYPE_12__ {int ks_ndata; int ks_data_size; TYPE_3__* ks_private; } ;
typedef  TYPE_5__ kstat_t ;
struct TYPE_9__ {scalar_t__ ui64; } ;
struct TYPE_13__ {TYPE_2__ value; } ;
typedef  TYPE_6__ kstat_named_t ;

/* Variables and functions */
 int KSTAT_WRITE ; 

__attribute__((used)) static int
spa_tx_assign_update(kstat_t *ksp, int rw)
{
	spa_t *spa = ksp->ks_private;
	spa_history_kstat_t *shk = &spa->spa_stats.tx_assign_histogram;
	int i;

	if (rw == KSTAT_WRITE) {
		for (i = 0; i < shk->count; i++)
			((kstat_named_t *)shk->private)[i].value.ui64 = 0;
	}

	for (i = shk->count; i > 0; i--)
		if (((kstat_named_t *)shk->private)[i-1].value.ui64 != 0)
			break;

	ksp->ks_ndata = i;
	ksp->ks_data_size = i * sizeof (kstat_named_t);

	return (0);
}