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
 int /*<<< orphan*/  check_output_buffer_space (size_t) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ output_buffer ; 
 unsigned int output_buffer_pos ; 

void align_output( unsigned int align )
{
    size_t size = align - (output_buffer_pos % align);

    if (size == align) return;
    check_output_buffer_space( size );
    memset( output_buffer + output_buffer_pos, 0, size );
    output_buffer_pos += size;
}