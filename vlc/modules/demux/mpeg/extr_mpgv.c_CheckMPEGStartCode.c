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
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 

__attribute__((used)) static int CheckMPEGStartCode( const uint8_t *p_peek )
{
    switch( p_peek[3] )
    {
        case 0x00:
            if( (p_peek[5] & 0x38) == 0x00 )
                return VLC_EGENERIC;
            break;
        case 0xB0:
        case 0xB1:
        case 0xB6:
            return VLC_EGENERIC;
        default:
            if( p_peek[3] > 0xB9 )
                return VLC_EGENERIC;
            break;
    }
    return VLC_SUCCESS;
}