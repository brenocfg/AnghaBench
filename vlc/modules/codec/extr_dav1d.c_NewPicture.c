#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
struct TYPE_23__ {int i_visible_width; int i_visible_height; int i_width; int i_height; int i_sar_num; int i_sar_den; int /*<<< orphan*/  i_chroma; int /*<<< orphan*/  pose; int /*<<< orphan*/  multiview_mode; int /*<<< orphan*/  projection_mode; int /*<<< orphan*/  color_range; int /*<<< orphan*/  space; int /*<<< orphan*/  transfer; int /*<<< orphan*/  primaries; } ;
typedef  TYPE_7__ video_format_t ;
struct TYPE_24__ {TYPE_6__* p; } ;
typedef  TYPE_8__ picture_t ;
struct TYPE_21__ {int /*<<< orphan*/  i_codec; TYPE_7__ video; } ;
struct TYPE_19__ {scalar_t__ primaries; int /*<<< orphan*/  pose; int /*<<< orphan*/  multiview_mode; int /*<<< orphan*/  projection_mode; } ;
struct TYPE_20__ {TYPE_3__ video; } ;
struct TYPE_25__ {TYPE_5__ fmt_out; TYPE_4__ fmt_in; } ;
typedef  TYPE_9__ decoder_t ;
struct TYPE_22__ {scalar_t__ i_pitch; int /*<<< orphan*/  p_pixels; } ;
struct TYPE_18__ {scalar_t__ color_range; int /*<<< orphan*/  mtrx; int /*<<< orphan*/  trc; int /*<<< orphan*/  pri; } ;
struct TYPE_17__ {int w; int h; } ;
struct TYPE_16__ {scalar_t__* stride; TYPE_8__* allocator_data; int /*<<< orphan*/ * data; TYPE_2__* seq_hdr; TYPE_1__ p; } ;
typedef  TYPE_10__ Dav1dPicture ;

/* Variables and functions */
 scalar_t__ COLOR_PRIMARIES_UNDEF ; 
 int /*<<< orphan*/  COLOR_RANGE_FULL ; 
 int /*<<< orphan*/  COLOR_RANGE_LIMITED ; 
 int /*<<< orphan*/  FindVlcChroma (TYPE_10__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_8__* decoder_NewPicture (TYPE_9__*) ; 
 scalar_t__ decoder_UpdateVideoFormat (TYPE_9__*) ; 
 int /*<<< orphan*/  iso_23001_8_cp_to_vlc_primaries (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iso_23001_8_mc_to_vlc_coeffs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iso_23001_8_tc_to_vlc_xfer (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int NewPicture(Dav1dPicture *img, void *cookie)
{
    decoder_t *dec = cookie;

    video_format_t *v = &dec->fmt_out.video;

    v->i_visible_width  = img->p.w;
    v->i_visible_height = img->p.h;
    v->i_width  = (img->p.w + 0x7F) & ~0x7F;
    v->i_height = (img->p.h + 0x7F) & ~0x7F;

    if( !v->i_sar_num || !v->i_sar_den )
    {
        v->i_sar_num = 1;
        v->i_sar_den = 1;
    }

    if(dec->fmt_in.video.primaries == COLOR_PRIMARIES_UNDEF && img->seq_hdr)
    {
        v->primaries = iso_23001_8_cp_to_vlc_primaries(img->seq_hdr->pri);
        v->transfer = iso_23001_8_tc_to_vlc_xfer(img->seq_hdr->trc);
        v->space = iso_23001_8_mc_to_vlc_coeffs(img->seq_hdr->mtrx);
        v->color_range = img->seq_hdr->color_range ? COLOR_RANGE_FULL : COLOR_RANGE_LIMITED;
    }

    v->projection_mode = dec->fmt_in.video.projection_mode;
    v->multiview_mode = dec->fmt_in.video.multiview_mode;
    v->pose = dec->fmt_in.video.pose;
    dec->fmt_out.video.i_chroma = dec->fmt_out.i_codec = FindVlcChroma(img);

    if (decoder_UpdateVideoFormat(dec) == 0)
    {
        picture_t *pic = decoder_NewPicture(dec);
        if (likely(pic != NULL))
        {
            img->data[0] = pic->p[0].p_pixels;
            img->stride[0] = pic->p[0].i_pitch;
            img->data[1] = pic->p[1].p_pixels;
            img->data[2] = pic->p[2].p_pixels;
            assert(pic->p[1].i_pitch == pic->p[2].i_pitch);
            img->stride[1] = pic->p[1].i_pitch;
            img->allocator_data = pic;

            return 0;
        }
    }
    return -1;
}