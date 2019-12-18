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
 int max (int,int) ; 
 int /*<<< orphan*/  output_buffer ; 
 int output_buffer_pos ; 
 int output_buffer_size ; 
 int /*<<< orphan*/  xrealloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void check_output_buffer_space( size_t size )
{
    if (output_buffer_pos + size >= output_buffer_size)
    {
        output_buffer_size = max( output_buffer_size * 2, output_buffer_pos + size );
        output_buffer = xrealloc( output_buffer, output_buffer_size );
    }
}