#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t i_step_index; int i_predictor; } ;
typedef  TYPE_1__ adpcm_ima_wav_channel_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLAMP (int,int,int) ; 
 scalar_t__* i_index_table ; 
 int* i_step_table ; 

__attribute__((used)) static int AdpcmImaWavExpandNibble(adpcm_ima_wav_channel_t *p_channel,
                                   int i_nibble )
{
    int i_diff;

    i_diff = i_step_table[p_channel->i_step_index] >> 3;
    if( i_nibble&0x04 ) i_diff += i_step_table[p_channel->i_step_index];
    if( i_nibble&0x02 ) i_diff += i_step_table[p_channel->i_step_index]>>1;
    if( i_nibble&0x01 ) i_diff += i_step_table[p_channel->i_step_index]>>2;
    if( i_nibble&0x08 )
        p_channel->i_predictor -= i_diff;
    else
        p_channel->i_predictor += i_diff;

    CLAMP( p_channel->i_predictor, -32768, 32767 );

    p_channel->i_step_index += i_index_table[i_nibble];

    CLAMP( p_channel->i_step_index, 0, 88 );

    return( p_channel->i_predictor );
}