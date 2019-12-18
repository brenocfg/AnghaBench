#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * p_pic; } ;
typedef  TYPE_1__ ttml_image_updater_region_t ;
typedef  int /*<<< orphan*/  picture_t ;

/* Variables and functions */
 TYPE_1__* calloc (int,int) ; 

__attribute__((used)) static ttml_image_updater_region_t *TTML_ImageUpdaterRegionNew(picture_t *p_pic)
{
    ttml_image_updater_region_t *p_region = calloc(1, sizeof(*p_region));
    if(p_region)
        p_region->p_pic = p_pic;
    return p_region;
}