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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  pi_chan_table; int /*<<< orphan*/  i_chans_to_reorder; } ;
typedef  TYPE_1__ decoder_sys_t ;

/* Variables and functions */
 unsigned int AOUT_CHAN_CENTER ; 
 unsigned int AOUT_CHAN_LEFT ; 
 unsigned int AOUT_CHAN_LFE ; 
 unsigned int AOUT_CHAN_MIDDLELEFT ; 
 unsigned int AOUT_CHAN_MIDDLERIGHT ; 
 unsigned int AOUT_CHAN_REARCENTER ; 
 unsigned int AOUT_CHAN_REARLEFT ; 
 unsigned int AOUT_CHAN_REARRIGHT ; 
 unsigned int AOUT_CHAN_RIGHT ; 
 int GetDWBE (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  aout_CheckChannelReorder (int const*,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int* pi_3channels_in ; 
 int* pi_4channels_in ; 
 int* pi_5channels_in ; 
 int* pi_6channels_in ; 
 int* pi_7channels_in ; 
 int* pi_8channels_in ; 

__attribute__((used)) static int BdHeader( decoder_sys_t *p_sys,
                     unsigned *pi_rate,
                     unsigned *pi_channels,
                     unsigned *pi_channels_padding,
                     unsigned *pi_original_channels,
                     unsigned *pi_bits,
                     const uint8_t *p_header )
{
    const uint32_t h = GetDWBE( p_header );
    const uint32_t *pi_channels_in = NULL;
    switch( ( h & 0xf000) >> 12 )
    {
    case 1:
        *pi_channels = 1;
        *pi_original_channels = AOUT_CHAN_CENTER;
        break;
    case 3:
        *pi_channels = 2;
        *pi_original_channels = AOUT_CHAN_LEFT | AOUT_CHAN_RIGHT;
        break;
    case 4:
        *pi_channels = 3;
        *pi_original_channels = AOUT_CHAN_LEFT | AOUT_CHAN_RIGHT | AOUT_CHAN_CENTER;
        pi_channels_in = pi_3channels_in;
        break;
    case 5:
        *pi_channels = 3;
        *pi_original_channels = AOUT_CHAN_LEFT | AOUT_CHAN_RIGHT | AOUT_CHAN_REARCENTER;
        break;
    case 6:
        *pi_channels = 4;
        *pi_original_channels = AOUT_CHAN_LEFT | AOUT_CHAN_RIGHT | AOUT_CHAN_CENTER |
                                AOUT_CHAN_REARCENTER;
        break;
    case 7:
        *pi_channels = 4;
        *pi_original_channels = AOUT_CHAN_LEFT | AOUT_CHAN_RIGHT |
                                AOUT_CHAN_REARLEFT | AOUT_CHAN_REARRIGHT;
        pi_channels_in = pi_4channels_in;
        break;
    case 8:
        *pi_channels = 5;
        *pi_original_channels = AOUT_CHAN_LEFT | AOUT_CHAN_RIGHT | AOUT_CHAN_CENTER |
                                AOUT_CHAN_REARLEFT | AOUT_CHAN_REARRIGHT;
        pi_channels_in = pi_5channels_in;
        break;
    case 9:
        *pi_channels = 6;
        *pi_original_channels = AOUT_CHAN_LEFT | AOUT_CHAN_RIGHT | AOUT_CHAN_CENTER |
                                AOUT_CHAN_REARLEFT | AOUT_CHAN_REARRIGHT |
                                AOUT_CHAN_LFE;
        pi_channels_in = pi_6channels_in;
        break;
    case 10:
        *pi_channels = 7;
        *pi_original_channels = AOUT_CHAN_LEFT | AOUT_CHAN_RIGHT | AOUT_CHAN_CENTER |
                                AOUT_CHAN_REARLEFT | AOUT_CHAN_REARRIGHT |
                                AOUT_CHAN_MIDDLELEFT | AOUT_CHAN_MIDDLERIGHT;
        pi_channels_in = pi_7channels_in;
        break;
    case 11:
        *pi_channels = 8;
        *pi_original_channels = AOUT_CHAN_LEFT | AOUT_CHAN_RIGHT | AOUT_CHAN_CENTER |
                                AOUT_CHAN_REARLEFT | AOUT_CHAN_REARRIGHT |
                                AOUT_CHAN_MIDDLELEFT | AOUT_CHAN_MIDDLERIGHT |
                                AOUT_CHAN_LFE;
        pi_channels_in = pi_8channels_in;
        break;

    default:
        return -1;
    }
    *pi_channels_padding = *pi_channels & 1;

    switch( (h >> 6) & 0x03 )
    {
    case 1:
        *pi_bits = 16;
        break;
    case 2: /* 20 bits but samples are stored on 24 bits */
    case 3: /* 24 bits */
        *pi_bits = 24;
        break;
    default:
        return -1;
    }
    switch( (h >> 8) & 0x0f )
    {
    case 1:
        *pi_rate = 48000;
        break;
    case 4:
        *pi_rate = 96000;
        break;
    case 5:
        *pi_rate = 192000;
        break;
    default:
        return -1;
    }

    if( pi_channels_in )
    {
        p_sys->i_chans_to_reorder =
            aout_CheckChannelReorder( pi_channels_in, NULL,
                                      *pi_original_channels,
                                      p_sys->pi_chan_table );
    }

    return 0;
}