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
typedef  void* int16_t ;
struct TYPE_8__ {int i_channels; } ;
struct TYPE_9__ {TYPE_1__ audio; } ;
struct TYPE_10__ {TYPE_2__ fmt_out; TYPE_4__* p_sys; } ;
typedef  TYPE_3__ decoder_t ;
struct TYPE_11__ {int i_block; } ;
typedef  TYPE_4__ decoder_sys_t ;
struct TYPE_12__ {int /*<<< orphan*/  i_step_index; int /*<<< orphan*/  i_predictor; } ;
typedef  TYPE_5__ adpcm_ima_wav_channel_t ;

/* Variables and functions */
 void* AdpcmImaWavExpandNibble (TYPE_5__*,int) ; 
 int /*<<< orphan*/  CLAMP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GetByte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWord (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void DecodeAdpcmImaWav( decoder_t *p_dec, int16_t *p_sample,
                               uint8_t *p_buffer )
{
    decoder_sys_t *p_sys  = p_dec->p_sys;
    adpcm_ima_wav_channel_t channel[2];
    int                     i_nibbles;
    int                     b_stereo;

    b_stereo = p_dec->fmt_out.audio.i_channels == 2 ? 1 : 0;

    GetWord( channel[0].i_predictor );
    GetByte( channel[0].i_step_index );
    CLAMP( channel[0].i_step_index, 0, 88 );
    p_buffer++;

    if( b_stereo )
    {
        GetWord( channel[1].i_predictor );
        GetByte( channel[1].i_step_index );
        CLAMP( channel[1].i_step_index, 0, 88 );
        p_buffer++;
    }

    if( b_stereo )
    {
        for( i_nibbles = 2 * (p_sys->i_block - 8);
             i_nibbles > 0;
             i_nibbles -= 16 )
        {
            int i;

            for( i = 0; i < 4; i++ )
            {
                p_sample[i * 4] =
                    AdpcmImaWavExpandNibble(&channel[0],p_buffer[i]&0x0f);
                p_sample[i * 4 + 2] =
                    AdpcmImaWavExpandNibble(&channel[0],p_buffer[i] >> 4);
            }
            p_buffer += 4;

            for( i = 0; i < 4; i++ )
            {
                p_sample[i * 4 + 1] =
                    AdpcmImaWavExpandNibble(&channel[1],p_buffer[i]&0x0f);
                p_sample[i * 4 + 3] =
                    AdpcmImaWavExpandNibble(&channel[1],p_buffer[i] >> 4);
            }
            p_buffer += 4;
            p_sample += 16;

        }


    }
    else
    {
        for( i_nibbles = 2 * (p_sys->i_block - 4);
             i_nibbles > 0;
             i_nibbles -= 2, p_buffer++ )
        {
            *p_sample++ =AdpcmImaWavExpandNibble( &channel[0], (*p_buffer)&0x0f );
            *p_sample++ =AdpcmImaWavExpandNibble( &channel[0], (*p_buffer) >> 4 );
        }
    }
}