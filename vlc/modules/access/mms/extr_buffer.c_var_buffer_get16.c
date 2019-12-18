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
typedef  int /*<<< orphan*/  var_buffer_t ;
typedef  int uint16_t ;

/* Variables and functions */
 int var_buffer_get8 (int /*<<< orphan*/ *) ; 

uint16_t var_buffer_get16( var_buffer_t *p_buf )
{
    uint16_t i_b1, i_b2;

    i_b1 = var_buffer_get8( p_buf );
    i_b2 = var_buffer_get8( p_buf );

    return( i_b1 + ( i_b2 << 8 ) );

}