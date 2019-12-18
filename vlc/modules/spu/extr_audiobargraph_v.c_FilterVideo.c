#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {int const i_visible_height; int const i_visible_width; } ;
typedef  TYPE_3__ video_format_t ;
struct TYPE_23__ {TYPE_3__ format; } ;
typedef  TYPE_4__ picture_t ;
struct TYPE_20__ {int i_visible_width; int i_visible_height; } ;
struct TYPE_21__ {TYPE_1__ video; } ;
struct TYPE_24__ {TYPE_2__ fmt_out; TYPE_6__* p_sys; } ;
typedef  TYPE_5__ filter_t ;
struct TYPE_26__ {int i_alpha; TYPE_4__* p_pic; } ;
struct TYPE_25__ {int i_pos; int i_pos_y; int i_pos_x; int /*<<< orphan*/  lock; int /*<<< orphan*/  p_blend; TYPE_7__ p_BarGraph; } ;
typedef  TYPE_6__ filter_sys_t ;
typedef  TYPE_7__ BarGraph_t ;

/* Variables and functions */
 int SUBPICTURE_ALIGN_BOTTOM ; 
 int SUBPICTURE_ALIGN_LEFT ; 
 int SUBPICTURE_ALIGN_RIGHT ; 
 int SUBPICTURE_ALIGN_TOP ; 
 scalar_t__ filter_Blend (int /*<<< orphan*/ ,TYPE_4__*,int,int,TYPE_4__ const*,int const) ; 
 scalar_t__ filter_ConfigureBlend (int /*<<< orphan*/ ,int const,int const,TYPE_3__ const*) ; 
 TYPE_4__* filter_NewPicture (TYPE_5__*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  picture_Copy (TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  picture_Release (TYPE_4__*) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static picture_t *FilterVideo(filter_t *p_filter, picture_t *p_src)
{
    filter_sys_t *p_sys = p_filter->p_sys;
    BarGraph_t *p_BarGraph = &(p_sys->p_BarGraph);

    picture_t *p_dst = filter_NewPicture(p_filter);
    if (!p_dst) {
        picture_Release(p_src);
        return NULL;
    }

    picture_Copy(p_dst, p_src);

    /* */
    vlc_mutex_lock(&p_sys->lock);

    /* */
    const picture_t *p_pic = p_BarGraph->p_pic;
    if (!p_pic)
        goto out;

    const video_format_t *p_fmt = &p_pic->format;
    const int i_dst_w = p_filter->fmt_out.video.i_visible_width;
    const int i_dst_h = p_filter->fmt_out.video.i_visible_height;

    if (p_sys->i_pos) {
        if (p_sys->i_pos & SUBPICTURE_ALIGN_BOTTOM)
            p_sys->i_pos_y = i_dst_h - p_fmt->i_visible_height;
        else if (!(p_sys->i_pos & SUBPICTURE_ALIGN_TOP))
            p_sys->i_pos_y = (i_dst_h - p_fmt->i_visible_height) / 2;
        else
            p_sys->i_pos_y = 0;

        if (p_sys->i_pos & SUBPICTURE_ALIGN_RIGHT)
            p_sys->i_pos_x = i_dst_w - p_fmt->i_visible_width;
        else if (!(p_sys->i_pos & SUBPICTURE_ALIGN_LEFT))
            p_sys->i_pos_x = (i_dst_w - p_fmt->i_visible_width) / 2;
        else
            p_sys->i_pos_x = 0;
    }

    /* */
    const int i_alpha = p_BarGraph->i_alpha;
    if (filter_ConfigureBlend(p_sys->p_blend, i_dst_w, i_dst_h, p_fmt) ||
            filter_Blend(p_sys->p_blend, p_dst, p_sys->i_pos_x, p_sys->i_pos_y,
                p_pic, i_alpha))
        msg_Err(p_filter, "failed to blend a picture");

out:
    vlc_mutex_unlock(&p_sys->lock);

    picture_Release(p_src);
    return p_dst;
}