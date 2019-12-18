#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint8_t ;

/* Variables and functions */
 unsigned int AOUT_CHAN_CENTER ; 
 unsigned int AOUT_CHAN_LEFT ; 
 unsigned int AOUT_CHAN_LFE ; 
 unsigned int AOUT_CHAN_MIDDLELEFT ; 
 unsigned int AOUT_CHAN_MIDDLERIGHT ; 
 unsigned int AOUT_CHAN_REARLEFT ; 
 unsigned int AOUT_CHAN_REARRIGHT ; 
 unsigned int AOUT_CHAN_RIGHT ; 

__attribute__((used)) static int VobHeader( unsigned *pi_rate,
                      unsigned *pi_channels, unsigned *pi_original_channels,
                      unsigned *pi_bits,
                      const uint8_t *p_header )
{
    const uint8_t i_header = p_header[4];

    switch( (i_header >> 4) & 0x3 )
    {
    case 0:
        *pi_rate = 48000;
        break;
    case 1:
        *pi_rate = 96000;
        break;
    case 2:
        *pi_rate = 44100;
        break;
    case 3:
        *pi_rate = 32000;
        break;
    }

    *pi_channels = (i_header & 0x7) + 1;
    switch( *pi_channels - 1 )
    {
    case 0:
        *pi_original_channels = AOUT_CHAN_CENTER;
        break;
    case 1:
        *pi_original_channels = AOUT_CHAN_LEFT | AOUT_CHAN_RIGHT;
        break;
    case 2:
        /* This is unsure. */
        *pi_original_channels = AOUT_CHAN_LEFT | AOUT_CHAN_RIGHT | AOUT_CHAN_LFE;
        break;
    case 3:
        *pi_original_channels = AOUT_CHAN_LEFT | AOUT_CHAN_RIGHT
                               | AOUT_CHAN_REARLEFT | AOUT_CHAN_REARRIGHT;
        break;
    case 4:
        /* This is unsure. */
        *pi_original_channels = AOUT_CHAN_LEFT | AOUT_CHAN_RIGHT
                               | AOUT_CHAN_REARLEFT | AOUT_CHAN_REARRIGHT
                               | AOUT_CHAN_LFE;
        break;
    case 5:
        *pi_original_channels = AOUT_CHAN_LEFT | AOUT_CHAN_RIGHT
                               | AOUT_CHAN_REARLEFT | AOUT_CHAN_REARRIGHT
                               | AOUT_CHAN_CENTER | AOUT_CHAN_LFE;
        break;
    case 6:
        *pi_original_channels = AOUT_CHAN_LEFT | AOUT_CHAN_RIGHT
                               | AOUT_CHAN_REARLEFT | AOUT_CHAN_REARRIGHT
                               | AOUT_CHAN_CENTER | AOUT_CHAN_MIDDLELEFT
                               | AOUT_CHAN_MIDDLERIGHT;
        break;
    case 7:
        *pi_original_channels = AOUT_CHAN_LEFT | AOUT_CHAN_RIGHT
                               | AOUT_CHAN_REARLEFT | AOUT_CHAN_REARRIGHT
                               | AOUT_CHAN_CENTER | AOUT_CHAN_MIDDLELEFT
                               | AOUT_CHAN_MIDDLERIGHT | AOUT_CHAN_LFE;
        break;
    }

    switch( (i_header >> 6) & 0x3 )
    {
    case 2:
        *pi_bits = 24;
        break;
    case 1:
        *pi_bits = 20;
        break;
    case 0:
    default:
        *pi_bits = 16;
        break;
    }

    /* Check frame sync and drop it. */
    if( p_header[5] != 0x80 )
        return -1;
    return 0;
}