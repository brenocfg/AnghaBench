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
 int /*<<< orphan*/  output_buffer ; 
 scalar_t__ output_buffer_pos ; 
 int output_buffer_size ; 
 int /*<<< orphan*/  xmalloc (int) ; 

void init_output_buffer(void)
{
    output_buffer_size = 1024;
    output_buffer_pos = 0;
    output_buffer = xmalloc( output_buffer_size );
}