#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__** pp_append; } ;
struct TYPE_6__ {struct TYPE_6__* p_next; TYPE_1__ specifiers; } ;
typedef  TYPE_2__ vlc_css_selector_t ;

/* Variables and functions */

void
vlc_css_selector_AddSpecifier( vlc_css_selector_t *p_sel, vlc_css_selector_t *p_spec )
{
    *p_sel->specifiers.pp_append = p_spec;
    while(p_spec)
    {
        p_sel->specifiers.pp_append = &p_spec->p_next;
        p_spec = p_spec->p_next;
    }
}