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
 unsigned int GetDWBE (int const*) ; 

__attribute__((used)) static unsigned int GetF80BE( const uint8_t p[10] )
{
    unsigned int i_mantissa = GetDWBE( &p[2] );
    int          i_exp = 30 - p[1];
    unsigned int i_last = 0;

    while( i_exp-- > 0 )
    {
        i_last = i_mantissa;
        i_mantissa >>= 1;
    }
    if( i_last&0x01 )
    {
        i_mantissa++;
    }
    return i_mantissa;
}