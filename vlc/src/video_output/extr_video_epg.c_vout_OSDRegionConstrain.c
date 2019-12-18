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
struct TYPE_3__ {int i_max_width; int i_max_height; } ;
typedef  TYPE_1__ subpicture_region_t ;

/* Variables and functions */

__attribute__((used)) static void vout_OSDRegionConstrain(subpicture_region_t *p_region, int w, int h)
{
    if( p_region )
    {
        p_region->i_max_width = w;
        p_region->i_max_height = h;
    }
}