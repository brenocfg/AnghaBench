#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_8__ {int i_channels; } ;
struct TYPE_9__ {TYPE_1__ audio; } ;
struct TYPE_10__ {TYPE_2__ fmt_out; TYPE_4__* p_sys; } ;
typedef  TYPE_3__ decoder_t ;
struct TYPE_11__ {size_t i_samplesperblock; } ;
typedef  TYPE_4__ decoder_sys_t ;
struct TYPE_12__ {int /*<<< orphan*/  i_sample1; int /*<<< orphan*/  i_sample2; int /*<<< orphan*/  i_idelta; void* i_coeff2; void* i_coeff1; } ;
typedef  TYPE_5__ adpcm_ms_channel_t ;

/* Variables and functions */
 void* AdpcmMsExpandNibble (TYPE_5__*,int) ; 
 int /*<<< orphan*/  CLAMP (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GetByte (int) ; 
 int /*<<< orphan*/  GetWord (int /*<<< orphan*/ ) ; 
 void** i_adaptation_coeff1 ; 
 void** i_adaptation_coeff2 ; 

__attribute__((used)) static void DecodeAdpcmMs( decoder_t *p_dec, int16_t *p_sample,
                           uint8_t *p_buffer )
{
    decoder_sys_t *p_sys  = p_dec->p_sys;
    adpcm_ms_channel_t channel[2];
    int b_stereo;
    int i_block_predictor;

    size_t i_total_samples = p_sys->i_samplesperblock;
    if(i_total_samples < 2)
        return;

    b_stereo = p_dec->fmt_out.audio.i_channels == 2 ? 1 : 0;

    GetByte( i_block_predictor );
    CLAMP( i_block_predictor, 0, 6 );
    channel[0].i_coeff1 = i_adaptation_coeff1[i_block_predictor];
    channel[0].i_coeff2 = i_adaptation_coeff2[i_block_predictor];

    if( b_stereo )
    {
        GetByte( i_block_predictor );
        CLAMP( i_block_predictor, 0, 6 );
        channel[1].i_coeff1 = i_adaptation_coeff1[i_block_predictor];
        channel[1].i_coeff2 = i_adaptation_coeff2[i_block_predictor];
    }
    GetWord( channel[0].i_idelta );
    if( b_stereo )
    {
        GetWord( channel[1].i_idelta );
    }

    GetWord( channel[0].i_sample1 );
    if( b_stereo )
    {
        GetWord( channel[1].i_sample1 );
    }

    GetWord( channel[0].i_sample2 );
    if( b_stereo )
    {
        GetWord( channel[1].i_sample2 );
    }

    if( b_stereo )
    {
        *p_sample++ = channel[0].i_sample2;
        *p_sample++ = channel[1].i_sample2;
        *p_sample++ = channel[0].i_sample1;
        *p_sample++ = channel[1].i_sample1;
    }
    else
    {
        *p_sample++ = channel[0].i_sample2;
        *p_sample++ = channel[0].i_sample1;
    }

    for( i_total_samples -= 2; i_total_samples >= 2; i_total_samples -= 2, p_buffer++ )
    {
        *p_sample++ = AdpcmMsExpandNibble( &channel[0], (*p_buffer) >> 4);
        *p_sample++ = AdpcmMsExpandNibble( &channel[b_stereo ? 1 : 0],
                                           (*p_buffer)&0x0f);
    }
}