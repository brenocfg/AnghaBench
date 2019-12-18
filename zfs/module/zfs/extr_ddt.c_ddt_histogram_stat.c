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
typedef  int /*<<< orphan*/  ddt_stat_t ;
struct TYPE_3__ {int /*<<< orphan*/ * ddh_stat; } ;
typedef  TYPE_1__ ddt_histogram_t ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ddt_stat_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
ddt_histogram_stat(ddt_stat_t *dds, const ddt_histogram_t *ddh)
{
	bzero(dds, sizeof (*dds));

	for (int h = 0; h < 64; h++)
		ddt_stat_add(dds, &ddh->ddh_stat[h], 0);
}