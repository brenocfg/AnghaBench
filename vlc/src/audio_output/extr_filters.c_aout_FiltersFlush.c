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
struct TYPE_3__ {int count; int /*<<< orphan*/ * resampler; int /*<<< orphan*/ ** tab; } ;
typedef  TYPE_1__ aout_filters_t ;

/* Variables and functions */
 int /*<<< orphan*/  aout_FiltersPipelineFlush (int /*<<< orphan*/ **,int) ; 

void aout_FiltersFlush (aout_filters_t *filters)
{
    aout_FiltersPipelineFlush (filters->tab, filters->count);

    if (filters->resampler != NULL)
        aout_FiltersPipelineFlush (&filters->resampler, 1);
}