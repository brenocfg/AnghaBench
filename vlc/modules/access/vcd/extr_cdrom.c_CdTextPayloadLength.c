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

/* Variables and functions */
 size_t strnlen (char const*,size_t) ; 

__attribute__((used)) static size_t CdTextPayloadLength( const char *p_buffer, size_t i_buffer,
                                   bool b_doublebytes )
{
    if( b_doublebytes )
    {
        size_t i_len = 0;
        for( size_t i=0; i<i_buffer/2; i++ )
        {
            if(p_buffer[0] == 0 && p_buffer[1] == 0)
                break;
            i_len += 2;
            p_buffer += 2;
        }
        return i_len;
    }
    else return strnlen( p_buffer, i_buffer );
}