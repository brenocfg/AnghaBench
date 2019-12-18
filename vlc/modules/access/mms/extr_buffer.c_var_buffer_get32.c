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
typedef  int uint32_t ;

/* Variables and functions */
 int var_buffer_get16 (int /*<<< orphan*/ *) ; 

uint32_t var_buffer_get32( var_buffer_t *p_buf )
{
    uint32_t i_w1, i_w2;

    i_w1 = var_buffer_get16( p_buf );
    i_w2 = var_buffer_get16( p_buf );

    return( i_w1 + ( i_w2 << 16 ) );
}