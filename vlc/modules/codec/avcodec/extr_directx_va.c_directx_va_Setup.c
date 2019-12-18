#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_va_t ;
struct TYPE_9__ {int i_width; int i_height; int /*<<< orphan*/  i_frame_rate_base; int /*<<< orphan*/  i_frame_rate; } ;
typedef  TYPE_2__ video_format_t ;
typedef  int /*<<< orphan*/  es_format_t ;
typedef  int /*<<< orphan*/  directx_va_mode_t ;
typedef  int /*<<< orphan*/  directx_sys_t ;
struct TYPE_8__ {int /*<<< orphan*/  den; int /*<<< orphan*/  num; } ;
struct TYPE_10__ {int codec_id; int active_thread_type; int coded_width; int coded_height; TYPE_1__ framerate; scalar_t__ thread_count; } ;
typedef  int /*<<< orphan*/  AVPixFmtDescriptor ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int ALIGN (int,int) ; 
#define  AV_CODEC_ID_H264 131 
#define  AV_CODEC_ID_HEVC 130 
#define  AV_CODEC_ID_MPEG2VIDEO 129 
#define  AV_CODEC_ID_VP9 128 
 int FF_THREAD_FRAME ; 
 int /*<<< orphan*/ * FindVideoServiceConversion (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,TYPE_2__*,TYPE_3__ const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*,int,int,int,int) ; 

const directx_va_mode_t *directx_va_Setup(vlc_va_t *va, const directx_sys_t *dx_sys,
                     const AVCodecContext *avctx, const AVPixFmtDescriptor *desc,
                     const es_format_t *fmt, int flag_xbox,
                     video_format_t *fmt_out, unsigned *surfaces)
{
    int surface_alignment = 16;
    unsigned surface_count = 2;

    switch ( avctx->codec_id )
    {
    case AV_CODEC_ID_MPEG2VIDEO:
        /* decoding MPEG-2 requires additional alignment on some Intel GPUs,
           but it causes issues for H.264 on certain AMD GPUs..... */
        surface_alignment = 32;
        surface_count += 2 + 2; /* 2 for deinterlacing which can hold up to 2
                                 * pictures from the decoder for smoothing */
        break;
    case AV_CODEC_ID_HEVC:
        /* the HEVC DXVA2 spec asks for 128 pixel aligned surfaces to ensure
           all coding features have enough room to work with */
           /* On the Xbox 1/S, the decoder cannot do 4K aligned to 128 but is OK with 64 */
        if (flag_xbox)
            surface_alignment = 16;
        else
            surface_alignment = 128;
        surface_count += 16;
        break;
    case AV_CODEC_ID_H264:
        surface_count += 16 + 2;
        break;
    case AV_CODEC_ID_VP9:
        surface_count += 8 + 1;
        break;
    default:
        surface_count += 2;
    }

    if ( avctx->active_thread_type & FF_THREAD_FRAME )
        surface_count += avctx->thread_count;

    if (avctx->coded_width <= 0 || avctx->coded_height <= 0)
        return NULL;

    assert((surface_alignment & (surface_alignment - 1)) == 0); /* power of 2 */
#define ALIGN(x, y) (((x) + ((y) - 1)) & ~((y) - 1))
    int surface_width  = ALIGN(avctx->coded_width,  surface_alignment);
    int surface_height = ALIGN(avctx->coded_height, surface_alignment);

    if (avctx->coded_width != surface_width || avctx->coded_height != surface_height)
        msg_Warn( va, "surface dimensions (%dx%d) differ from avcodec dimensions (%dx%d)",
                  surface_width, surface_height,
                  avctx->coded_width, avctx->coded_height);

    fmt_out->i_width  = surface_width;
    fmt_out->i_height = surface_height;

    /* FIXME transmit a video_format_t by VaSetup directly */
    fmt_out->i_frame_rate      = avctx->framerate.num;
    fmt_out->i_frame_rate_base = avctx->framerate.den;

    /* */
    const directx_va_mode_t *res = FindVideoServiceConversion(va, dx_sys, fmt, fmt_out, avctx, desc);
    if (res == NULL) {
        msg_Err(va, "FindVideoServiceConversion failed");
        return NULL;
    }
    *surfaces = surface_count;
    return res;
}