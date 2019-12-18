#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_fourcc_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_14__ {scalar_t__ i_visible_height; scalar_t__ i_visible_width; int /*<<< orphan*/  i_chroma; } ;
struct TYPE_16__ {int i_planes; TYPE_3__* p; TYPE_2__ format; } ;
typedef  TYPE_4__ picture_t ;
struct TYPE_17__ {TYPE_6__* p_sys; } ;
typedef  TYPE_5__ decoder_t ;
struct TYPE_18__ {TYPE_1__* p_context; } ;
typedef  TYPE_6__ decoder_sys_t ;
struct TYPE_19__ {int width; int height; size_t* linesize; int /*<<< orphan*/ ** data; int /*<<< orphan*/  format; } ;
struct TYPE_15__ {size_t i_pitch; int i_visible_lines; int /*<<< orphan*/ * p_pixels; } ;
struct TYPE_13__ {int /*<<< orphan*/  pix_fmt; } ;
typedef  TYPE_7__ AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  FindVlcChroma (int /*<<< orphan*/ ) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 size_t __MIN (size_t,size_t) ; 
 char* av_get_pix_fmt_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chroma_compatible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  msg_Err (TYPE_5__*,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_5__*,char*) ; 

__attribute__((used)) static int lavc_CopyPicture(decoder_t *dec, picture_t *pic, AVFrame *frame)
{
    decoder_sys_t *sys = dec->p_sys;

    vlc_fourcc_t fourcc = FindVlcChroma(frame->format);
    if (!fourcc)
    {
        const char *name = av_get_pix_fmt_name(frame->format);

        msg_Err(dec, "Unsupported decoded output format %d (%s)",
                sys->p_context->pix_fmt, (name != NULL) ? name : "unknown");
        return VLC_EGENERIC;
    } else if (!chroma_compatible(fourcc, pic->format.i_chroma)
     /* ensure we never read more than dst lines/pixels from src */
     || frame->width != (int) pic->format.i_visible_width
     || frame->height < (int) pic->format.i_visible_height)
    {
        msg_Warn(dec, "dropping frame because the vout changed");
        return VLC_EGENERIC;
    }

    for (int plane = 0; plane < pic->i_planes; plane++)
    {
        const uint8_t *src = frame->data[plane];
        uint8_t *dst = pic->p[plane].p_pixels;
        size_t src_stride = frame->linesize[plane];
        size_t dst_stride = pic->p[plane].i_pitch;
        size_t size = __MIN(src_stride, dst_stride);

        for (int line = 0; line < pic->p[plane].i_visible_lines; line++)
        {
            memcpy(dst, src, size);
            src += src_stride;
            dst += dst_stride;
        }
    }
    return VLC_SUCCESS;
}