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
 int /*<<< orphan*/  BEGIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  YY_FATAL_ERROR (char*) ; 
 int /*<<< orphan*/ * yy_start_stack ; 
 scalar_t__ yy_start_stack_ptr ; 

__attribute__((used)) static void yy_pop_state  (void)
{
    	if ( --(yy_start_stack_ptr) < 0 )
		YY_FATAL_ERROR( "start-condition stack underflow" );

	BEGIN((yy_start_stack)[(yy_start_stack_ptr)]);
}