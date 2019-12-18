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
typedef  int /*<<< orphan*/  substext_updater_region_t ;

/* Variables and functions */
 int /*<<< orphan*/  SubpictureUpdaterSysRegionInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int) ; 

__attribute__((used)) static inline substext_updater_region_t *SubpictureUpdaterSysRegionNew( )
{
    substext_updater_region_t *p_region = malloc(sizeof(*p_region));
    if(p_region)
        SubpictureUpdaterSysRegionInit(p_region);
    return p_region;
}