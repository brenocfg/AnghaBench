#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_11__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
typedef  float vlc_tick_t ;
typedef  int /*<<< orphan*/  picture_t ;
struct TYPE_19__ {int /*<<< orphan*/  video; } ;
struct TYPE_18__ {int /*<<< orphan*/  video; } ;
struct TYPE_21__ {int /*<<< orphan*/  p_module; int /*<<< orphan*/  (* pf_video_blend ) (TYPE_4__*,TYPE_10__*,TYPE_11__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;TYPE_2__ fmt_in; TYPE_1__ fmt_out; TYPE_5__* p_sys; } ;
typedef  TYPE_4__ filter_t ;
struct TYPE_22__ {int b_done; int i_loops; TYPE_11__* p_blend_image; int /*<<< orphan*/  i_alpha; TYPE_10__* p_base_image; } ;
typedef  TYPE_5__ filter_sys_t ;
struct TYPE_20__ {float i_visible_pitch; float i_visible_lines; } ;
struct TYPE_17__ {TYPE_3__* p; int /*<<< orphan*/  format; } ;
struct TYPE_16__ {int /*<<< orphan*/  format; } ;

/* Variables and functions */
 float CLOCK_FREQ ; 
 size_t Y_PLANE ; 
 int /*<<< orphan*/  module_need (TYPE_4__*,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  module_unneed (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Info (TYPE_4__*,char*,float,float) ; 
 int /*<<< orphan*/  picture_Release (int /*<<< orphan*/ *) ; 
 float secf_from_vlc_tick (float) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,TYPE_10__*,TYPE_11__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* vlc_object_create (TYPE_4__*,int) ; 
 int /*<<< orphan*/  vlc_object_delete (TYPE_4__*) ; 
 float vlc_tick_now () ; 

__attribute__((used)) static picture_t *Filter( filter_t *p_filter, picture_t *p_pic )
{
    filter_sys_t *p_sys = p_filter->p_sys;
    filter_t *p_blend;

    if( p_sys->b_done )
        return p_pic;

    p_blend = vlc_object_create( p_filter, sizeof(filter_t) );
    if( !p_blend )
    {
        picture_Release( p_pic );
        return NULL;
    }
    p_blend->fmt_out.video = p_sys->p_base_image->format;
    p_blend->fmt_in.video = p_sys->p_blend_image->format;
    p_blend->p_module = module_need( p_blend, "video blending", NULL, false );
    if( !p_blend->p_module )
    {
        picture_Release( p_pic );
        vlc_object_delete(p_blend);
        return NULL;
    }

    vlc_tick_t time = vlc_tick_now();
    for( int i_iter = 0; i_iter < p_sys->i_loops; ++i_iter )
    {
        p_blend->pf_video_blend( p_blend,
                                 p_sys->p_base_image, p_sys->p_blend_image,
                                 0, 0, p_sys->i_alpha );
    }
    time = vlc_tick_now() - time;

    msg_Info( p_filter, "Blended %d images in %f sec", p_sys->i_loops,
              secf_from_vlc_tick(time) );
    msg_Info( p_filter, "Speed is: %f images/second, %f pixels/second",
              (float) p_sys->i_loops / time * CLOCK_FREQ,
              (float) p_sys->i_loops / time * CLOCK_FREQ *
                  p_sys->p_blend_image->p[Y_PLANE].i_visible_pitch *
                  p_sys->p_blend_image->p[Y_PLANE].i_visible_lines );

    module_unneed( p_blend, p_blend->p_module );

    vlc_object_delete(p_blend);

    p_sys->b_done = true;
    return p_pic;
}