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
typedef  scalar_t__ uint8_t ;
typedef  int uint16_t ;

/* Variables and functions */
#define  AOUT_CHANS_FRONT 133 
#define  AOUT_CHANS_MIDDLE 132 
#define  AOUT_CHANS_REAR 131 
#define  AOUT_CHAN_CENTER 130 
#define  AOUT_CHAN_LFE 129 
#define  AOUT_CHAN_REARCENTER 128 

__attribute__((used)) static uint8_t dca_get_LBR_channels( uint16_t nuSpkrActivityMask,
                                     uint16_t *pi_chans )
{
    uint16_t i_physical_channels = 0;
    uint8_t i_channels = 0;

    static const struct
    {
        int phy;
        uint8_t nb;
    } bitmask[16] = {
         /* table 7-10 */
        { AOUT_CHAN_CENTER,     1 },
        { AOUT_CHANS_FRONT,     2 },
        { AOUT_CHANS_MIDDLE,    2 },
        { AOUT_CHAN_LFE,        1 },
        { AOUT_CHAN_REARCENTER, 1 },
        { 0,                    2 },
        { AOUT_CHANS_REAR,      2 },
        { 0,                    1 },
        { 0,                    1 },
        { 0,                    2 },
        { AOUT_CHANS_FRONT,     2 },
        { AOUT_CHANS_MIDDLE,    2 },
        { 0,                    1 },
        { 0,                    2 },
        { 0,                    1 },
        { 0,                    2 },
    };

    for( int i=0 ; nuSpkrActivityMask; nuSpkrActivityMask >>= 1 )
    {
        if( nuSpkrActivityMask & 1 )
        {
            i_physical_channels |= bitmask[i].phy;
            i_channels += bitmask[i].nb;
        }
        ++i;
    }
    *pi_chans = i_physical_channels;
    return i_channels;
}