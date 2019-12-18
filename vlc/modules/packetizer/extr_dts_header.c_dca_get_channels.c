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
typedef  int uint16_t ;

/* Variables and functions */
 int AOUT_CHANMODE_DUALMONO ; 
 int AOUT_CHANS_3_0 ; 
 int AOUT_CHANS_4_0 ; 
 int AOUT_CHANS_4_CENTER_REAR ; 
 int AOUT_CHANS_5_0 ; 
 int AOUT_CHANS_6_0 ; 
 int AOUT_CHANS_7_0 ; 
 int AOUT_CHANS_CENTER ; 
 int AOUT_CHANS_FRONT ; 
 int AOUT_CHANS_REAR ; 
 int AOUT_CHAN_CENTER ; 
 int AOUT_CHAN_LFE ; 
 int AOUT_CHAN_REARCENTER ; 

__attribute__((used)) static uint16_t dca_get_channels( uint8_t i_amode, bool b_lfe,
                                  uint16_t *p_chan_mode )
{
    /* See ETSI TS 102 114, table 5-4
     * 00: A
     * 01: A + B (dual mono)
     * 02: L + R (stereo)
     * 03: (L+R) + (L-R) (sum and difference)
     * 04: LT + RT (left and right total)
     * 05: C + L + R
     * 06: L + R + S
     * 07: C + L + R + S
     * 08: L + R + SL + SR
     * 09: C + L + R + SL + SR
     * 0A: CL + CR + L + R + SL + SR
     * 0B: C + L + R + LR + RR + OV
     * 0C: CF + CR + LF + RF + LR + RR
     * 0D: CL + C + CR + L + R + SL + SR
     * 0E: CL + CR + L + R + SL1 + SL2 + SR1 + SR2
     * 0F: CL + C + CR + L + R + SL + S + SR
     * 10-3F: user defined */

    uint16_t i_physical_channels;

    switch( i_amode )
    {
        case 0x0:
            i_physical_channels = AOUT_CHAN_CENTER;
            break;
        case 0x1:
            i_physical_channels = AOUT_CHANS_FRONT;
            *p_chan_mode = AOUT_CHANMODE_DUALMONO;
            break;
        case 0x2:
        case 0x3:
        case 0x4:
            i_physical_channels = AOUT_CHANS_FRONT;
            break;
        case 0x5:
            i_physical_channels = AOUT_CHANS_3_0;
            break;
        case 0x6:
            i_physical_channels = AOUT_CHANS_FRONT | AOUT_CHAN_REARCENTER;
            break;
        case 0x7:
            i_physical_channels = AOUT_CHANS_4_CENTER_REAR;
            break;
        case 0x8:
            i_physical_channels = AOUT_CHANS_4_0;
            break;
        case 0x9:
            i_physical_channels = AOUT_CHANS_5_0;
            break;
        case 0xA:
        case 0xB:
            i_physical_channels = AOUT_CHANS_6_0;
            break;
        case 0xC:
            i_physical_channels = AOUT_CHANS_CENTER | AOUT_CHANS_FRONT
                                | AOUT_CHANS_REAR;
            break;
        case 0xD:
            i_physical_channels = AOUT_CHANS_7_0;
            break;
        case 0xE:
        case 0xF:
            /* FIXME: AOUT_CHANS_8_0 */
            i_physical_channels = AOUT_CHANS_7_0;
            break;
        default:
            return 0;
    }
    if (b_lfe)
        i_physical_channels |= AOUT_CHAN_LFE;

    return i_physical_channels;
}