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
struct TYPE_4__ {struct TYPE_4__* p_next; } ;
typedef  TYPE_1__ substext_updater_region_t ;

/* Variables and functions */

__attribute__((used)) static inline void SubpictureUpdaterSysRegionAdd(substext_updater_region_t *p_prev,
                                                 substext_updater_region_t *p_new)
{
    substext_updater_region_t **pp_next = &p_prev->p_next;
    for(; *pp_next; pp_next = &(*pp_next)->p_next);
    *pp_next = p_new;
}