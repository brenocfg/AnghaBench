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
 int /*<<< orphan*/  check_output_buffer_space (int) ; 
 unsigned char* output_buffer ; 
 int /*<<< orphan*/  output_buffer_pos ; 

void put_byte( unsigned char val )
{
    check_output_buffer_space( 1 );
    output_buffer[output_buffer_pos++] = val;
}