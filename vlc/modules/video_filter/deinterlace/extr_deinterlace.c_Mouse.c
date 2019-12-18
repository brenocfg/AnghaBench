#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int i_y; } ;
typedef  TYPE_3__ vlc_mouse_t ;
struct TYPE_14__ {TYPE_5__* p_sys; } ;
typedef  TYPE_4__ filter_t ;
struct TYPE_11__ {scalar_t__ b_half_height; } ;
struct TYPE_12__ {TYPE_1__ settings; } ;
struct TYPE_15__ {TYPE_2__ context; } ;
typedef  TYPE_5__ filter_sys_t ;

/* Variables and functions */
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_UNUSED (TYPE_3__ const*) ; 

int Mouse( filter_t *p_filter,
           vlc_mouse_t *p_mouse,
           const vlc_mouse_t *p_old, const vlc_mouse_t *p_new )
{
    VLC_UNUSED(p_old);
    *p_mouse = *p_new;
    filter_sys_t *p_sys = p_filter->p_sys;
    if( p_sys->context.settings.b_half_height )
        p_mouse->i_y *= 2;
    return VLC_SUCCESS;
}