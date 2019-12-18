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
typedef  int /*<<< orphan*/  vlc_viewpoint_t ;
struct TYPE_3__ {int /*<<< orphan*/  count; int /*<<< orphan*/  tab; } ;
typedef  TYPE_1__ aout_filters_t ;

/* Variables and functions */
 int /*<<< orphan*/  aout_FiltersPipelineChangeViewpoint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

void aout_FiltersChangeViewpoint (aout_filters_t *filters,
                                  const vlc_viewpoint_t *vp)
{
    aout_FiltersPipelineChangeViewpoint (filters->tab, filters->count, vp);
}