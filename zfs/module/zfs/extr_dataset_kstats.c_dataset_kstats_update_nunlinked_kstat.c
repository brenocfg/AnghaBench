#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_4__ {int /*<<< orphan*/  das_nunlinked; } ;
struct TYPE_5__ {TYPE_1__ dk_aggsums; int /*<<< orphan*/ * dk_kstats; } ;
typedef  TYPE_2__ dataset_kstats_t ;

/* Variables and functions */
 int /*<<< orphan*/  aggsum_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
dataset_kstats_update_nunlinked_kstat(dataset_kstats_t *dk, int64_t delta)
{
	if (dk->dk_kstats == NULL)
		return;

	aggsum_add(&dk->dk_aggsums.das_nunlinked, delta);
}