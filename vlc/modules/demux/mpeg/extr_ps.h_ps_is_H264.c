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
 int /*<<< orphan*/  memcmp (int const*,int const*,int) ; 

__attribute__((used)) static inline bool ps_is_H264( const uint8_t *p_data, size_t i_data )
{
    const uint8_t startcode[3] = { 0, 0, 1 };
    int i_flags = 0;

    if( i_data < 9 ||
       (!memcmp( p_data, startcode, 3 ) &&
        !memcmp( &p_data[1], startcode, 3 )) )
        return false;

    /* Shitty H264 probing. We need a centralized way do to this */
    while( i_data > 5 )
    {
        if( !memcmp( p_data, startcode, 3 ) )
        {
            if(p_data[3] == 0x67)
                i_flags ^= 0x01;
            else if(p_data[3] == 0x68)
                i_flags ^= 0x02;
            else if( p_data[3] & 0x80 )
                return false;
            else if( (p_data[3] & 0x1F) > 23 || (p_data[3] & 0x1F) < 1 )
                return false;
            else if( (p_data[3] & 0x1F) < 6 )
                return (i_flags == 0x03);
        }
        p_data++;
        i_data--;
    }

    return false;
}