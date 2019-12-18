#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_mouse_t ;
struct TYPE_6__ {scalar_t__ (* pf_video_mouse ) (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ filter_t ;
struct TYPE_7__ {TYPE_3__* last; } ;
typedef  TYPE_2__ filter_chain_t ;
struct TYPE_8__ {int /*<<< orphan*/ * mouse; TYPE_1__ filter; struct TYPE_8__* prev; } ;
typedef  TYPE_3__ chained_filter_t ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 scalar_t__ stub1 (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int filter_chain_MouseFilter( filter_chain_t *p_chain, vlc_mouse_t *p_dst, const vlc_mouse_t *p_src )
{
    vlc_mouse_t current = *p_src;

    for( chained_filter_t *f = p_chain->last; f != NULL; f = f->prev )
    {
        filter_t *p_filter = &f->filter;
        vlc_mouse_t *p_mouse = f->mouse;

        if( p_filter->pf_video_mouse && p_mouse )
        {
            vlc_mouse_t old = *p_mouse;
            vlc_mouse_t filtered;

            *p_mouse = current;
            if( p_filter->pf_video_mouse( p_filter, &filtered, &old, &current ) )
                return VLC_EGENERIC;
            current = filtered;
        }
    }

    *p_dst = current;
    return VLC_SUCCESS;
}