#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_9__ ;
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ vpx_codec_err_t ;
typedef  scalar_t__ vlc_tick_t ;
struct TYPE_27__ {scalar_t__ i_visible_width; scalar_t__ i_visible_height; scalar_t__ i_width; scalar_t__ i_height; int i_sar_num; int i_sar_den; int /*<<< orphan*/  pose; int /*<<< orphan*/  multiview_mode; int /*<<< orphan*/  projection_mode; int /*<<< orphan*/  color_range; int /*<<< orphan*/  space; int /*<<< orphan*/  transfer; int /*<<< orphan*/  primaries; } ;
typedef  TYPE_5__ video_format_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct vpx_image {scalar_t__* user_priv; scalar_t__ d_w; scalar_t__ d_h; size_t cs; scalar_t__ range; int* stride; int /*<<< orphan*/ ** planes; int /*<<< orphan*/  fmt; } ;
struct vpx_codec_ctx {int dummy; } ;
struct TYPE_28__ {int i_planes; int b_progressive; scalar_t__ date; TYPE_4__* p; } ;
typedef  TYPE_6__ picture_t ;
struct TYPE_24__ {scalar_t__ primaries; int /*<<< orphan*/  pose; int /*<<< orphan*/  multiview_mode; int /*<<< orphan*/  projection_mode; } ;
struct TYPE_25__ {TYPE_2__ video; } ;
struct TYPE_23__ {TYPE_5__ video; int /*<<< orphan*/  i_codec; } ;
struct TYPE_29__ {TYPE_3__ fmt_in; TYPE_1__ fmt_out; TYPE_8__* p_sys; } ;
typedef  TYPE_7__ decoder_t ;
struct TYPE_30__ {struct vpx_codec_ctx ctx; } ;
typedef  TYPE_8__ decoder_sys_t ;
struct TYPE_31__ {int i_flags; scalar_t__ i_pts; scalar_t__ i_dts; int /*<<< orphan*/  i_buffer; int /*<<< orphan*/  p_buffer; } ;
typedef  TYPE_9__ block_t ;
struct TYPE_26__ {int i_pitch; int i_visible_lines; int /*<<< orphan*/ * p_pixels; } ;
struct TYPE_22__ {int /*<<< orphan*/  space; int /*<<< orphan*/  transfer; int /*<<< orphan*/  primaries; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_10__*) ; 
 int BLOCK_FLAG_CORRUPTED ; 
 scalar_t__ COLOR_PRIMARIES_UNDEF ; 
 int /*<<< orphan*/  COLOR_RANGE_FULL ; 
 int /*<<< orphan*/  COLOR_RANGE_LIMITED ; 
 int /*<<< orphan*/  FindVlcChroma (struct vpx_image*) ; 
 int VLCDEC_ECRITICAL ; 
 int VLCDEC_SUCCESS ; 
 scalar_t__ VLC_TICK_INVALID ; 
 scalar_t__ VPX_CODEC_OK ; 
 scalar_t__ VPX_CODEC_UNSUP_BITSTREAM ; 
 scalar_t__ VPX_CR_FULL_RANGE ; 
 int /*<<< orphan*/  VPX_ERR (TYPE_7__*,struct vpx_codec_ctx*,char*) ; 
 int __MIN (int,int) ; 
 int /*<<< orphan*/  block_Release (TYPE_9__*) ; 
 TYPE_6__* decoder_NewPicture (TYPE_7__*) ; 
 int /*<<< orphan*/  decoder_QueueVideo (TYPE_7__*,TYPE_6__*) ; 
 scalar_t__ decoder_UpdateVideoFormat (TYPE_7__*) ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 
 scalar_t__* malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msg_Err (TYPE_7__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ vpx_codec_decode (struct vpx_codec_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 struct vpx_image* vpx_codec_get_frame (struct vpx_codec_ctx*,void const**) ; 
 TYPE_10__* vpx_color_mapping_table ; 

__attribute__((used)) static int Decode(decoder_t *dec, block_t *block)
{
    decoder_sys_t *p_sys = dec->p_sys;
    struct vpx_codec_ctx *ctx = &p_sys->ctx;

    if (block == NULL) /* No Drain */
        return VLCDEC_SUCCESS;

    if (block->i_flags & (BLOCK_FLAG_CORRUPTED)) {
        block_Release(block);
        return VLCDEC_SUCCESS;
    }

    /* Associate packet PTS with decoded frame */
    vlc_tick_t *pkt_pts = malloc(sizeof(*pkt_pts));
    if (!pkt_pts) {
        block_Release(block);
        return VLCDEC_SUCCESS;
    }

    *pkt_pts = (block->i_pts != VLC_TICK_INVALID) ? block->i_pts : block->i_dts;

    vpx_codec_err_t err;
    err = vpx_codec_decode(ctx, block->p_buffer, block->i_buffer, pkt_pts, 0);

    block_Release(block);

    if (err != VPX_CODEC_OK) {
        free(pkt_pts);
        VPX_ERR(dec, ctx, "Failed to decode frame");
        if (err == VPX_CODEC_UNSUP_BITSTREAM)
            return VLCDEC_ECRITICAL;
        else
            return VLCDEC_SUCCESS;
    }

    const void *iter = NULL;
    struct vpx_image *img = vpx_codec_get_frame(ctx, &iter);
    if (!img) {
        free(pkt_pts);
        return VLCDEC_SUCCESS;
    }

    /* fetches back the PTS */
    pkt_pts = img->user_priv;
    vlc_tick_t pts = *pkt_pts;
    free(pkt_pts);

    dec->fmt_out.i_codec = FindVlcChroma(img);

    if( dec->fmt_out.i_codec == 0 ) {
        msg_Err(dec, "Unsupported output colorspace %d", img->fmt);
        return VLCDEC_SUCCESS;
    }

    video_format_t *v = &dec->fmt_out.video;

    if (img->d_w != v->i_visible_width || img->d_h != v->i_visible_height) {
        v->i_visible_width = dec->fmt_out.video.i_width = img->d_w;
        v->i_visible_height = dec->fmt_out.video.i_height = img->d_h;
    }

    if( !dec->fmt_out.video.i_sar_num || !dec->fmt_out.video.i_sar_den )
    {
        dec->fmt_out.video.i_sar_num = 1;
        dec->fmt_out.video.i_sar_den = 1;
    }

    if(dec->fmt_in.video.primaries == COLOR_PRIMARIES_UNDEF &&
       img->cs >= 0 && img->cs < ARRAY_SIZE(vpx_color_mapping_table))
    {
        v->primaries = vpx_color_mapping_table[img->cs].primaries;
        v->transfer = vpx_color_mapping_table[img->cs].transfer;
        v->space = vpx_color_mapping_table[img->cs].space;
        v->color_range = img->range == VPX_CR_FULL_RANGE ? COLOR_RANGE_FULL : COLOR_RANGE_LIMITED;
    }

    dec->fmt_out.video.projection_mode = dec->fmt_in.video.projection_mode;
    dec->fmt_out.video.multiview_mode = dec->fmt_in.video.multiview_mode;
    dec->fmt_out.video.pose = dec->fmt_in.video.pose;

    if (decoder_UpdateVideoFormat(dec))
        return VLCDEC_SUCCESS;
    picture_t *pic = decoder_NewPicture(dec);
    if (!pic)
        return VLCDEC_SUCCESS;

    for (int plane = 0; plane < pic->i_planes; plane++ ) {
        uint8_t *src = img->planes[plane];
        uint8_t *dst = pic->p[plane].p_pixels;
        int src_stride = img->stride[plane];
        int dst_stride = pic->p[plane].i_pitch;

        int size = __MIN( src_stride, dst_stride );
        for( int line = 0; line < pic->p[plane].i_visible_lines; line++ ) {
            memcpy( dst, src, size );
            src += src_stride;
            dst += dst_stride;
        }
    }

    pic->b_progressive = true; /* codec does not support interlacing */
    pic->date = pts;

    decoder_QueueVideo(dec, pic);
    return VLCDEC_SUCCESS;
}