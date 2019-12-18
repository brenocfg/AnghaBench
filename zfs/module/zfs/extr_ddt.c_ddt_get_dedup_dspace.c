#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long long uint64_t ;
struct TYPE_7__ {unsigned long long spa_dedup_dspace; } ;
typedef  TYPE_1__ spa_t ;
struct TYPE_8__ {unsigned long long dds_ref_dsize; unsigned long long dds_dsize; } ;
typedef  TYPE_2__ ddt_stat_t ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (TYPE_2__*,int) ; 
 int /*<<< orphan*/  ddt_get_dedup_stats (TYPE_1__*,TYPE_2__*) ; 

uint64_t
ddt_get_dedup_dspace(spa_t *spa)
{
	ddt_stat_t dds_total;

	if (spa->spa_dedup_dspace != ~0ULL)
		return (spa->spa_dedup_dspace);

	bzero(&dds_total, sizeof (ddt_stat_t));

	/* Calculate and cache the stats */
	ddt_get_dedup_stats(spa, &dds_total);
	spa->spa_dedup_dspace = dds_total.dds_ref_dsize - dds_total.dds_dsize;
	return (spa->spa_dedup_dspace);
}