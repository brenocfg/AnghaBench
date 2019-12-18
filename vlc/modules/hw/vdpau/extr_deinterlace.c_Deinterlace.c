#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {scalar_t__ structure; int /*<<< orphan*/  context; } ;
typedef  TYPE_3__ vlc_vdp_video_field_t ;
typedef  int vlc_tick_t ;
struct TYPE_21__ {int date; int b_top_field_first; int i_nb_fields; int b_progressive; struct TYPE_21__* p_next; int /*<<< orphan*/ * context; int /*<<< orphan*/  format; } ;
typedef  TYPE_4__ picture_t ;
struct TYPE_18__ {scalar_t__ i_frame_rate; int /*<<< orphan*/  i_frame_rate_base; } ;
struct TYPE_19__ {TYPE_1__ video; } ;
struct TYPE_22__ {TYPE_2__ fmt_in; TYPE_6__* p_sys; } ;
typedef  TYPE_5__ filter_t ;
struct TYPE_23__ {int last_pts; } ;
typedef  TYPE_6__ filter_sys_t ;

/* Variables and functions */
 void* VDP_VIDEO_MIXER_PICTURE_STRUCTURE_BOTTOM_FIELD ; 
 scalar_t__ VDP_VIDEO_MIXER_PICTURE_STRUCTURE_FRAME ; 
 void* VDP_VIDEO_MIXER_PICTURE_STRUCTURE_TOP_FIELD ; 
 int VLC_TICK_INVALID ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_4__* filter_NewPicture (TYPE_5__*) ; 
 int /*<<< orphan*/  picture_CopyProperties (TYPE_4__*,TYPE_4__*) ; 
 TYPE_4__* picture_NewFromFormat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  picture_Release (TYPE_4__*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int vlc_tick_from_samples (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_3__* vlc_vdp_video_copy (TYPE_3__*) ; 

__attribute__((used)) static picture_t *Deinterlace(filter_t *filter, picture_t *src)
{
    filter_sys_t *sys = filter->p_sys;
    vlc_tick_t last_pts = sys->last_pts;

    sys->last_pts = src->date;

    vlc_vdp_video_field_t *f1 = (vlc_vdp_video_field_t *)src->context;
    if (unlikely(f1 == NULL))
        return src;
    if (f1->structure != VDP_VIDEO_MIXER_PICTURE_STRUCTURE_FRAME)
        return src; /* cannot deinterlace twice */

#ifdef VOUT_CORE_GETS_A_CLUE
    picture_t *dst = filter_NewPicture(filter);
#else
    picture_t *dst = picture_NewFromFormat(&src->format);
#endif
    if (dst == NULL)
        return src; /* cannot deinterlace without copying fields */

    vlc_vdp_video_field_t *f2 = vlc_vdp_video_copy(f1); // shallow copy
    if (unlikely(f2 == NULL))
    {
        picture_Release(dst);
        return src;
    }

    picture_CopyProperties(dst, src);
    dst->context = &f2->context;

    if (last_pts != VLC_TICK_INVALID)
        dst->date = (3 * src->date - last_pts) / 2;
    else
    if (filter->fmt_in.video.i_frame_rate != 0)
        dst->date = src->date + vlc_tick_from_samples(filter->fmt_in.video.i_frame_rate_base
                            ,filter->fmt_in.video.i_frame_rate);
    dst->b_top_field_first = !src->b_top_field_first;
    dst->i_nb_fields = 1;
    src->i_nb_fields = 1;

    assert(src->p_next == NULL);
    src->p_next = dst;

    if (src->b_progressive || src->b_top_field_first)
    {
        f1->structure = VDP_VIDEO_MIXER_PICTURE_STRUCTURE_TOP_FIELD;
        f2->structure = VDP_VIDEO_MIXER_PICTURE_STRUCTURE_BOTTOM_FIELD;
    }
    else
    {
        f1->structure = VDP_VIDEO_MIXER_PICTURE_STRUCTURE_BOTTOM_FIELD;
        f2->structure = VDP_VIDEO_MIXER_PICTURE_STRUCTURE_TOP_FIELD;
    }

    src->b_progressive = true;
    dst->b_progressive = true;
    return src;
}