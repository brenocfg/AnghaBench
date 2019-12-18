#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  ddt_stat_t ;
typedef  int /*<<< orphan*/  ddt_histogram_t ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  ddt_get_dedup_histogram (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ddt_histogram_stat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * kmem_zalloc (int,int /*<<< orphan*/ ) ; 

void
ddt_get_dedup_stats(spa_t *spa, ddt_stat_t *dds_total)
{
	ddt_histogram_t *ddh_total;

	ddh_total = kmem_zalloc(sizeof (ddt_histogram_t), KM_SLEEP);
	ddt_get_dedup_histogram(spa, ddh_total);
	ddt_histogram_stat(dds_total, ddh_total);
	kmem_free(ddh_total, sizeof (ddt_histogram_t));
}