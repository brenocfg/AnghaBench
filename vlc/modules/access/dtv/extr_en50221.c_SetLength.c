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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int SIZE_INDICATOR ; 

__attribute__((used)) static uint8_t *SetLength( uint8_t *p_data, int i_length )
{
    uint8_t *p = p_data;

    if ( i_length < 128 )
    {
        *p++ = i_length;
    }
    else if ( i_length < 256 )
    {
        *p++ = SIZE_INDICATOR | 0x1;
        *p++ = i_length;
    }
    else if ( i_length < 65536 )
    {
        *p++ = SIZE_INDICATOR | 0x2;
        *p++ = i_length >> 8;
        *p++ = i_length & 0xff;
    }
    else if ( i_length < 16777216 )
    {
        *p++ = SIZE_INDICATOR | 0x3;
        *p++ = i_length >> 16;
        *p++ = (i_length >> 8) & 0xff;
        *p++ = i_length & 0xff;
    }
    else
    {
        *p++ = SIZE_INDICATOR | 0x4;
        *p++ = i_length >> 24;
        *p++ = (i_length >> 16) & 0xff;
        *p++ = (i_length >> 8) & 0xff;
        *p++ = i_length & 0xff;
    }

    return p;
}