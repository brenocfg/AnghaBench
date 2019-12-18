#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {scalar_t__ pts; int poc; int sliceType; int /*<<< orphan*/ * stride; int /*<<< orphan*/ * planes; } ;
typedef  TYPE_4__ x265_picture ;
struct TYPE_24__ {int /*<<< orphan*/  payload; scalar_t__ sizeBytes; } ;
typedef  TYPE_5__ x265_nal ;
typedef  size_t uint32_t ;
struct TYPE_25__ {scalar_t__ date; int i_planes; TYPE_1__* p; } ;
typedef  TYPE_6__ picture_t ;
struct TYPE_21__ {int /*<<< orphan*/  i_frame_rate; int /*<<< orphan*/  i_frame_rate_base; } ;
struct TYPE_22__ {TYPE_2__ video; } ;
struct TYPE_26__ {TYPE_3__ fmt_in; TYPE_8__* p_sys; } ;
typedef  TYPE_7__ encoder_t ;
struct TYPE_27__ {scalar_t__ initial_date; float start; scalar_t__ frame_count; int /*<<< orphan*/  h; int /*<<< orphan*/  param; } ;
typedef  TYPE_8__ encoder_sys_t ;
struct TYPE_28__ {int i_length; scalar_t__ i_pts; scalar_t__ i_dts; int /*<<< orphan*/  i_buffer; int /*<<< orphan*/  i_flags; int /*<<< orphan*/  p_buffer; } ;
typedef  TYPE_9__ block_t ;
struct TYPE_20__ {int /*<<< orphan*/  i_pitch; int /*<<< orphan*/  p_pixels; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_FLAG_TYPE_B ; 
 int /*<<< orphan*/  BLOCK_FLAG_TYPE_I ; 
 int /*<<< orphan*/  BLOCK_FLAG_TYPE_P ; 
 float CLOCK_FREQ ; 
 scalar_t__ VLC_TICK_INVALID ; 
#define  X265_TYPE_B 132 
#define  X265_TYPE_BREF 131 
#define  X265_TYPE_I 130 
#define  X265_TYPE_IDR 129 
#define  X265_TYPE_P 128 
 TYPE_9__* block_Alloc (int) ; 
 scalar_t__ likely (TYPE_6__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_7__*,char*,int /*<<< orphan*/ ,scalar_t__,float) ; 
 scalar_t__ unlikely (int) ; 
 int vlc_tick_from_samples (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float vlc_tick_now () ; 
 int /*<<< orphan*/  x265_encoder_encode (int /*<<< orphan*/ ,TYPE_5__**,size_t*,TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  x265_picture_init (int /*<<< orphan*/ *,TYPE_4__*) ; 

__attribute__((used)) static block_t *Encode(encoder_t *p_enc, picture_t *p_pict)
{
    encoder_sys_t *p_sys = p_enc->p_sys;
    x265_picture pic;

    x265_picture_init(&p_sys->param, &pic);

    if (likely(p_pict)) {
        pic.pts = p_pict->date;
        if (unlikely(p_sys->initial_date == VLC_TICK_INVALID)) {
            p_sys->initial_date = p_pict->date;
#ifndef NDEBUG
            p_sys->start = vlc_tick_now();
#endif
        }

        for (int i = 0; i < p_pict->i_planes; i++) {
            pic.planes[i] = p_pict->p[i].p_pixels;
            pic.stride[i] = p_pict->p[i].i_pitch;
        }
    }

    x265_nal *nal;
    uint32_t i_nal = 0;
    x265_encoder_encode(p_sys->h, &nal, &i_nal,
            likely(p_pict) ? &pic : NULL, &pic);

    if (!i_nal)
        return NULL;

    int i_out = 0;
    for (uint32_t i = 0; i < i_nal; i++)
        i_out += nal[i].sizeBytes;

    block_t *p_block = block_Alloc(i_out);
    if (!p_block)
        return NULL;

    /* all payloads are sequentially laid out in memory */
    memcpy(p_block->p_buffer, nal[0].payload, i_out);

    /* This isn't really valid for streams with B-frames */
    p_block->i_length = vlc_tick_from_samples(
                p_enc->fmt_in.video.i_frame_rate_base,
                p_enc->fmt_in.video.i_frame_rate );

    p_block->i_pts = p_sys->initial_date + pic.poc * p_block->i_length;
    p_block->i_dts = p_sys->initial_date + p_sys->frame_count++ * p_block->i_length;

    switch (pic.sliceType)
    {
    case X265_TYPE_I:
    case X265_TYPE_IDR:
        p_block->i_flags |= BLOCK_FLAG_TYPE_I;
        break;
    case X265_TYPE_P:
        p_block->i_flags |= BLOCK_FLAG_TYPE_P;
        break;
    case X265_TYPE_B:
    case X265_TYPE_BREF:
        p_block->i_flags |= BLOCK_FLAG_TYPE_B;
        break;
    }

#ifndef NDEBUG
    msg_Dbg(p_enc, "%zu bytes (frame %u, %.2ffps)", p_block->i_buffer,
        p_sys->frame_count, (float)p_sys->frame_count * CLOCK_FREQ / (vlc_tick_now() - p_sys->start));
#endif

    return p_block;
}