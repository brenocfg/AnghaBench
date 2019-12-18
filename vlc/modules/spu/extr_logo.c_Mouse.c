#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {scalar_t__ i_x; scalar_t__ i_y; } ;
typedef  TYPE_3__ vlc_mouse_t ;
struct TYPE_23__ {int i_visible_width; int i_visible_height; } ;
typedef  TYPE_4__ video_format_t ;
struct TYPE_24__ {TYPE_4__ format; } ;
typedef  TYPE_5__ picture_t ;
struct TYPE_25__ {TYPE_5__* p_pic; } ;
typedef  TYPE_6__ logo_t ;
struct TYPE_20__ {scalar_t__ i_height; scalar_t__ i_width; } ;
struct TYPE_21__ {TYPE_1__ video; } ;
struct TYPE_26__ {TYPE_2__ fmt_in; TYPE_8__* p_sys; } ;
typedef  TYPE_7__ filter_t ;
struct TYPE_27__ {scalar_t__ i_pos_x; scalar_t__ i_pos_y; int b_mouse_grab; int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;
typedef  TYPE_8__ filter_sys_t ;

/* Variables and functions */
 TYPE_6__* LogoListCurrent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MOUSE_BUTTON_LEFT ; 
 void* VLC_CLIP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  vlc_mouse_GetMotion (int*,int*,TYPE_3__ const*,TYPE_3__ const*) ; 
 scalar_t__ vlc_mouse_HasPressed (TYPE_3__ const*,TYPE_3__ const*,int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_mouse_HasReleased (TYPE_3__ const*,TYPE_3__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int Mouse( filter_t *p_filter, vlc_mouse_t *p_mouse,
                  const vlc_mouse_t *p_old, const vlc_mouse_t *p_new )
{
    filter_sys_t *p_sys = p_filter->p_sys;

    vlc_mutex_lock( &p_sys->lock );
    logo_t *p_logo = LogoListCurrent( &p_sys->list );
    const picture_t *p_pic = p_logo->p_pic;

    if( p_pic )
    {
        const video_format_t *p_fmt = &p_pic->format;
        const int i_logo_w = p_fmt->i_visible_width;
        const int i_logo_h = p_fmt->i_visible_height;

        /* Check if we are over the logo */
        const bool b_over = p_new->i_x >= p_sys->i_pos_x &&
                            p_new->i_x <  p_sys->i_pos_x + i_logo_w &&
                            p_new->i_y >= p_sys->i_pos_y &&
                            p_new->i_y <  p_sys->i_pos_y + i_logo_h;

        if( b_over && vlc_mouse_HasPressed( p_old, p_new, MOUSE_BUTTON_LEFT ) )
            p_sys->b_mouse_grab = true;
        else if( vlc_mouse_HasReleased( p_old, p_new, MOUSE_BUTTON_LEFT ) )
            p_sys->b_mouse_grab = false;

        if( p_sys->b_mouse_grab )
        {
            int i_dx, i_dy;
            vlc_mouse_GetMotion( &i_dx, &i_dy, p_old, p_new );
            p_sys->i_pos_x = VLC_CLIP( p_sys->i_pos_x + i_dx, 0,
                                    (int)p_filter->fmt_in.video.i_width  - i_logo_w );
            p_sys->i_pos_y = VLC_CLIP( p_sys->i_pos_y + i_dy, 0,
                                    (int)p_filter->fmt_in.video.i_height - i_logo_h );
        }

        if( p_sys->b_mouse_grab || b_over )
        {
            vlc_mutex_unlock( &p_sys->lock );
            return VLC_EGENERIC;
        }
    }
    vlc_mutex_unlock( &p_sys->lock );

    *p_mouse = *p_new;
    return VLC_SUCCESS;
}