#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long long uint64_t ;
struct TYPE_10__ {int size; scalar_t__ private; } ;
struct TYPE_7__ {TYPE_4__ tx_assign_histogram; } ;
struct TYPE_9__ {TYPE_1__ spa_stats; } ;
typedef  TYPE_3__ spa_t ;
typedef  TYPE_4__ spa_history_kstat_t ;
struct TYPE_8__ {int /*<<< orphan*/  ui64; } ;
struct TYPE_11__ {TYPE_2__ value; } ;
typedef  TYPE_5__ kstat_named_t ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc_64 (int /*<<< orphan*/ *) ; 

void
spa_tx_assign_add_nsecs(spa_t *spa, uint64_t nsecs)
{
	spa_history_kstat_t *shk = &spa->spa_stats.tx_assign_histogram;
	uint64_t idx = 0;

	while (((1ULL << idx) < nsecs) && (idx < shk->size - 1))
		idx++;

	atomic_inc_64(&((kstat_named_t *)shk->private)[idx].value.ui64);
}