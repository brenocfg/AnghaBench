#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tick_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_21__ {int /*<<< orphan*/  i_rate; } ;
struct TYPE_22__ {TYPE_3__ audio; } ;
struct TYPE_19__ {int /*<<< orphan*/  i_channels; } ;
struct TYPE_20__ {int /*<<< orphan*/  i_codec; TYPE_1__ audio; } ;
struct TYPE_23__ {TYPE_4__ fmt_out; TYPE_2__ fmt_in; TYPE_6__* p_sys; } ;
typedef  TYPE_5__ encoder_t ;
struct TYPE_24__ {size_t samples_per_frame; int /*<<< orphan*/  s; } ;
typedef  TYPE_6__ encoder_sys_t ;
struct TYPE_25__ {int i_buffer; unsigned int i_nb_samples; int /*<<< orphan*/  i_pts; int /*<<< orphan*/  i_dts; scalar_t__ i_length; int /*<<< orphan*/  p_buffer; } ;
typedef  TYPE_7__ block_t ;

/* Variables and functions */
 TYPE_7__* GetPCM (TYPE_5__*,TYPE_7__*) ; 
 int SHINE_MAX_SAMPLES ; 
 int /*<<< orphan*/  VLC_UNUSED (TYPE_5__*) ; 
 int /*<<< orphan*/  aout_Deinterleave (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_7__* block_Alloc (int) ; 
 int /*<<< orphan*/  block_ChainAppend (TYPE_7__**,TYPE_7__*) ; 
 int /*<<< orphan*/  block_Release (TYPE_7__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char*,int) ; 
 unsigned char* shine_encode_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*) ; 
 scalar_t__ vlc_tick_from_samples (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static block_t *EncodeFrame( encoder_t *p_enc, block_t *p_block )
{
    if (!p_block) /* TODO: flush */
        return NULL;

    encoder_sys_t *p_sys = p_enc->p_sys;
    block_t *p_pcm_block;
    block_t *p_chain = NULL;
    unsigned int i_samples = p_block->i_buffer >> 2 /* s16l stereo */;
    vlc_tick_t start_date = p_block->i_pts;
    start_date -= vlc_tick_from_samples(i_samples, p_enc->fmt_out.audio.i_rate);

    VLC_UNUSED(p_enc);

    do {
        p_pcm_block = GetPCM( p_enc, p_block );
        if( !p_pcm_block )
            break;

        p_block = NULL; /* we don't need it anymore */
        int16_t pcm_planar_buf[SHINE_MAX_SAMPLES * 2];
        int16_t *pcm_planar_buf_chans[2] = {
            &pcm_planar_buf[0],
            &pcm_planar_buf[p_sys->samples_per_frame],
        };
        aout_Deinterleave( pcm_planar_buf, p_pcm_block->p_buffer,
                p_sys->samples_per_frame, p_enc->fmt_in.audio.i_channels, p_enc->fmt_in.i_codec);

        int written;
        unsigned char *buf = shine_encode_buffer(p_sys->s, pcm_planar_buf_chans, &written);
        block_Release( p_pcm_block );

        if (written <= 0)
            break;

        block_t *p_mp3_block = block_Alloc( written );
        if( !p_mp3_block )
            break;

        memcpy( p_mp3_block->p_buffer, buf, written );

        /* date management */
        p_mp3_block->i_length = vlc_tick_from_samples(p_sys->samples_per_frame,
            p_enc->fmt_out.audio.i_rate);

        start_date += p_mp3_block->i_length;
        p_mp3_block->i_dts = p_mp3_block->i_pts = start_date;

        p_mp3_block->i_nb_samples = p_sys->samples_per_frame;

        block_ChainAppend( &p_chain, p_mp3_block );

    } while( p_pcm_block );

    return p_chain;
}