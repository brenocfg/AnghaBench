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
typedef  int uint64_t ;
typedef  int int64_t ;

/* Variables and functions */
 int GetQWLE (int*) ; 

unsigned const char * Read7BitsVariableLE( unsigned const char *p_begin,
                                           unsigned const char *p_end,
                                           uint64_t *pi_value )
{
    int i_shift = 0;
    int64_t i_read = 0;
    *pi_value = 0;

    while ( p_begin < p_end )
    {
        i_read = *p_begin & 0x7F; /* High bit is start of integer */
        *pi_value = *pi_value | ( i_read << i_shift );
        i_shift += 7;
        if ( (*p_begin++ & 0x80) == 0x80 ) break; /* see prev */
    }

    *pi_value = GetQWLE( pi_value );
    return p_begin;
}