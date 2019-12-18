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

__attribute__((used)) static const uint8_t *FindReferenceCode( uint8_t i_code,
                                         const uint8_t *p_parser,
                                         const uint8_t *p_end )
{
    while ( p_parser <= p_end - 5 )
    {
        if ( p_parser[0] == 0xff && p_parser[1] == 0x3 && p_parser[2] == 0x0
              && p_parser[3] == 0x0 && p_parser[4] == i_code )
            return p_parser;
        p_parser += 5;
    }

    return NULL;
}