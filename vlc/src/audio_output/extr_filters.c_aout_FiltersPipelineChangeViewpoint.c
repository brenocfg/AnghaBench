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
typedef  int /*<<< orphan*/  vlc_viewpoint_t ;
typedef  int /*<<< orphan*/  filter_t ;

/* Variables and functions */
 int /*<<< orphan*/  filter_ChangeViewpoint (int /*<<< orphan*/ * const,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void aout_FiltersPipelineChangeViewpoint(filter_t *const *filters,
                                                unsigned count,
                                                const vlc_viewpoint_t *vp)
{
    for (unsigned i = 0; i < count; i++)
        filter_ChangeViewpoint (filters[i], vp);
}