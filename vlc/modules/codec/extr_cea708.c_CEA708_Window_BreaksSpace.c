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
struct TYPE_4__ {scalar_t__ print_direction; scalar_t__ justify; } ;
struct TYPE_5__ {TYPE_1__ style; } ;
typedef  TYPE_2__ cea708_window_t ;

/* Variables and functions */
 scalar_t__ CEA708_WA_DIRECTION_LTR ; 
 scalar_t__ CEA708_WA_DIRECTION_RTL ; 
 scalar_t__ CEA708_WA_JUSTIFY_LEFT ; 
 scalar_t__ CEA708_WA_JUSTIFY_RIGHT ; 

__attribute__((used)) static bool CEA708_Window_BreaksSpace( const cea708_window_t *p_w )
{
    return true;
    if( p_w->style.print_direction == CEA708_WA_DIRECTION_LTR &&
        p_w->style.justify == CEA708_WA_JUSTIFY_LEFT )
        return true;

    if( p_w->style.print_direction == CEA708_WA_DIRECTION_RTL &&
        p_w->style.justify == CEA708_WA_JUSTIFY_RIGHT )
        return true;

    return false;
}