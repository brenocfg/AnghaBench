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
 int /*<<< orphan*/  var_buffer_add8 (int /*<<< orphan*/ *,int) ; 

void var_buffer_add16( var_buffer_t *p_buf, uint16_t i_word )
{
    var_buffer_add8( p_buf, i_word&0xff );
    var_buffer_add8( p_buf, ( i_word >> 8 )&0xff );
}