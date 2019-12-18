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
 int /*<<< orphan*/  var_buffer_add16 (int /*<<< orphan*/ *,int) ; 

void var_buffer_add32( var_buffer_t *p_buf, uint32_t i_dword )
{
    var_buffer_add16( p_buf, i_dword&0xffff );
    var_buffer_add16( p_buf, ( i_dword >> 16 )&0xffff );
}