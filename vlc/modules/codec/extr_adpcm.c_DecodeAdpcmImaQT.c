#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ int16_t ;
struct TYPE_7__ {int i_channels; } ;
struct TYPE_8__ {TYPE_1__ audio; } ;
struct TYPE_9__ {TYPE_2__ fmt_out; } ;
typedef  TYPE_3__ decoder_t ;
struct TYPE_10__ {int i_step_index; scalar_t__ i_predictor; } ;
typedef  TYPE_4__ adpcm_ima_wav_channel_t ;

/* Variables and functions */
 scalar_t__ AdpcmImaWavExpandNibble (TYPE_4__*,int) ; 
 int /*<<< orphan*/  CLAMP (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void DecodeAdpcmImaQT( decoder_t *p_dec, int16_t *p_sample,
                              uint8_t *p_buffer )
{
    adpcm_ima_wav_channel_t channel[2];
    int                     i_nibbles;
    int                     i_ch;
    int                     i_step;

    i_step = p_dec->fmt_out.audio.i_channels;

    for( i_ch = 0; i_ch < p_dec->fmt_out.audio.i_channels; i_ch++ )
    {
        /* load preambule */
        channel[i_ch].i_predictor  = (int16_t)((( ( p_buffer[0] << 1 )|(  p_buffer[1] >> 7 ) ))<<7);
        channel[i_ch].i_step_index = p_buffer[1]&0x7f;

        CLAMP( channel[i_ch].i_step_index, 0, 88 );
        p_buffer += 2;

        for( i_nibbles = 0; i_nibbles < 64; i_nibbles +=2 )
        {
            *p_sample = AdpcmImaWavExpandNibble( &channel[i_ch], (*p_buffer)&0x0f);
            p_sample += i_step;

            *p_sample = AdpcmImaWavExpandNibble( &channel[i_ch], (*p_buffer >> 4)&0x0f);
            p_sample += i_step;

            p_buffer++;
        }

        /* Next channel */
        p_sample += 1 - 64 * i_step;
    }
}